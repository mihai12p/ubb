bits 32
global start        

import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll
extern fopen, fscanf, fclose, printf, exit

segment data use32 class=data
    file_name db 'input.txt', 0
    read_mode db 'r', 0
    read_text db '%d', 0
    read_text2 db '%x ', 0
    write_text db 'Cifra minima a lui %d (%x) este %d.', 10, 0 ; (10 = ascii pentru linie noua adica \n)
    file_descriptor resd 1
    number resd 1
    mindigit resd 1
    
segment code use32 class=code
    start:
        ; fopen("input.txt", "r")
        push dword read_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final
        
        mov [file_descriptor], eax
        
        ; fscanf(file, "%d", &number)
        push dword number
        push dword read_text
        push dword [file_descriptor]
        call [fscanf]
        add esp, 4*3
        
        mov ecx, [number]
        jecxz final
        _fscanf:
            push ecx
            
            mov dword [mindigit], 10
            
            ; fscanf(file, "%x ", &number)
            push dword number
            push dword read_text2
            push dword [file_descriptor]
            call [fscanf]
            add esp, 4*3
            
            push eax
            push edx
            mov eax, [number]
            _minc:
                push ebx
                mov ebx, 10
                cdq ; edx:eax = number
                div ebx ; edx:eax / ebx -> edx = restul si eax = catul
                cmp edx, dword [mindigit] ; edx = ultima cifra
                jge _maiDeparte
                mov dword [mindigit], edx
                _maiDeparte:
                    pop ebx
                    cmp eax, 0
            jne _minc
            pop edx
            pop eax
            
            push dword [mindigit]
            push dword [number]
            push dword [number]
            push dword write_text
            call [printf]
            add esp, 4*4
            
            pop ecx
        loop _fscanf

        ; fclose(file)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4*1
        
        final:
            ; exit(0)
            push dword 0
            call [exit]
