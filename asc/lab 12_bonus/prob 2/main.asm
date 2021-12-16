bits 32
global start        

import fopen msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll
extern fopen, scanf, fclose, fprintf, exit

segment data use32 class=data
    file_name db 'output.txt', 0
    write_mode db 'w', 0
    read_text db '%d', 0
    write_suma_pare db 'Suma numerelor pare este %x.', 10, 0 ; (10 = ascii pentru linie noua adica \n)
    write_suma_impare db 'Suma numerelor impare este %x.', 10, 0 ; (10 = ascii pentru linie noua adica \n)
    write_diferenta db 'Diferenta dintre cele 2 sume este %x.', 10, 0 ; (10 = ascii pentru linie noua adica \n)
    file_descriptor resd 1
    number resd 1
    sum_pare dd 0
    sum_impare dd 0
    
segment code use32 class=code
    start:
        ; scanf("%d", &number)
        push dword number
        push dword read_text
        call [scanf]
        add esp, 4*2
        
        mov ecx, [number]
        jecxz finalIntermediar
        _scanf:
            push ecx
        
            ; scanf("%d", &number)
            push dword number
            push dword read_text
            call [scanf]
            add esp, 4*2
            
            push eax
            mov eax, [number]
            test eax, 1
            jnz _impar
            add [sum_pare], eax
            jmp _maiDeparte
            _impar:
                add [sum_impare], eax
            
            _maiDeparte:
                pop eax
                pop ecx
        loop _scanf
        
        finalIntermediar:
        
        ; fopen("output.txt", "w")
        push dword write_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final
        
        mov [file_descriptor], eax
        
        ; fprintf(file, "Suma numerelor pare este %x.", sum_pare)
        push dword [sum_pare]
        push dword write_suma_pare
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
       
        ; fprintf(file, "Suma numerelor pare este %x.", sum_pare)
        push dword [sum_impare]
        push dword write_suma_impare
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        mov ebx, [sum_pare]
        sub ebx, [sum_impare]
        ; fprintf(file, "Diferenta dintre cele 2 sume este %x.", sum_pare - sum_impare)
        push dword ebx
        push dword write_diferenta
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
       
        ; fclose(file)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4*1
        
        final:
            ; exit(0)
            push dword 0
            call [exit]
