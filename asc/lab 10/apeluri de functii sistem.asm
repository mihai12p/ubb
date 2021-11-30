;19. Sa se citeasca de la tastatura un octet si un cuvant. Sa se afiseze pe ecran 
; daca bitii octetului citit se regasesc consecutiv printre bitii cuvantului. 
;Exemplu: a = 10 = 0000 1010b
;         b = 256 = 0000 0001 0000 0000b
;         Pe ecran se va afisa NU.

;         a = 10 = 0000 1010b
;         b = 24913 = 0110 0001 0101 0001b
;         Pe ecran se va afisa DA (bitii se regasesc pe pozitiile 4-11).

;         a = 33 = 0010 0001b
;         b = 51311 = 1100 1000 0110 1111b
;         Pe ecran se va afisa DA (bitii se regasesc pe pozitiile 3-10).

bits 32
global start        

import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll
extern printf, scanf, exit

segment data use32 class=data
    octet resb 1
    cuvant resw 1
    scan_format db '%d %d', 0
    no_print_format db '%s', 0
    no db 'NU', 0
    yes_print_format db '%s %d-%d)', 0
    yes db 'DA (bitii se regasesc pe pozitiile', 0
    
segment code use32 class=code
    start:
        ; scanf("%d %d", &octet, &cuvant)
        push dword cuvant
        push dword octet
        push dword scan_format
        call [scanf]
        add esp, 4*3
        
        mov al, [octet]
        mov bx, [cuvant]
        mov ecx, 9 ; adica (cuvant - octet) * 8 + 1
        check:
            cmp al, bl
            je found
            shr bx, 1
        loop check
        
        ; printf("%s", "NU")
        push dword no
        push dword no_print_format
        call [printf]
        add esp, 4*2
        jmp final
        
        ; printf("%s", "DA (bitii se regasesc pe pozitiile x-y))
        found:
            add ecx, 7
            push ecx
            sub ecx, 7
            push ecx
            push dword yes
            push dword yes_print_format
            call [printf]
            add esp, 4*4
            
        final:
        
        ; exit(0)
        push dword 0
        call [exit]
