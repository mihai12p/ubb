; 15. Se dau un nume de fisier si un text (definite in segmentul de date). 
; Textul contine litere mici, litere mari, cifre si caractere speciale. 
; Sa se inlocuiasca toate caracterele speciale din textul dat cu caracterul 'X'. 
; Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier. 

bits 32

global start        

extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    nume_fisier db 'file.txt', 0
    deschide_fisier db 'w', 0
    format_afisare db '%s', 0
    descriptor resd 1
    text db 'abc123!@#ga25o215@%^)@^#I', 0
    sir_len equ $-text

segment code use32 class=code
    start:
        cld ; DF = 0
        mov ecx, sir_len
        jecxz final
        mov esi, text
        
        repeta:
            lodsb
            cmp al, '!'
            jl urm
            cmp al, '/'
            jg urm
            
            mov ebx, sir_len
            sub ebx, ecx
            mov [text + ebx], byte 'X'
            
            urm:
        loop repeta
        
        ; fopen("file.txt", "w")
        push dword deschide_fisier
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final
        
        mov [descriptor], eax
        
        ; fprintf(fp, "%s", text)
        push dword text
        push dword format_afisare
        push dword [descriptor]
        call [fprintf]
        add esp, 4*3
        
        ; fclose(fp)
        push dword [descriptor]
        call [fclose]
        add esp, 4*1
        
        final:
    
        ; exit(0)
        push    dword 0
        call    [exit]
