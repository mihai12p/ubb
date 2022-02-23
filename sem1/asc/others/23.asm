; 23. Se da numele unui fisier si un numar pe cuvant scris in memorie. 
; Sa se scrie cifrele hexazecimale ale acestui numar ca text in fisier, fiecare cifra pe o linie separata. 

bits 32

global start        

extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    fisier db 'file.txt', 0
    mod_fisier db 'w', 0
    format_afisare db '%x', 10, 0
    handle resd 1
    numar dw 1535

segment code use32 class=code
    start:
        ; fopen("file.txt", "w")
        push dword mod_fisier
        push dword fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final
        mov [handle], eax
        
        repeat:
            mov ax, [numar]
            mov cl, 16
            idiv cl ; ah = restul, al = catul
            movsx ebx, ah
            
            cbw
            mov [numar], ax
            
            ; fprintf(handle, "%x\n", ebx)
            push dword ebx
            push dword format_afisare
            push dword [handle]
            call [fprintf]
            add esp, 4*3
            
            cmp word [numar], 0
        jne repeat
        
        ; fclose(handle)
        push dword [handle]
        call [fclose]
        add esp, 4*1
        
        final:
    
        ; exit(0)
        push    dword 0
        call    [exit]
