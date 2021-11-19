;19. Dandu-se doua siruri de octeti sa se calculeze toate pozitiile unde al doilea sir apare ca subsir in primul sir. 

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir db 'a', 'a', 'b', 'c', 'e', 'a', 'b', 'c', 'd', 'e', 'a', 'b', 'c', 'd', 'e', 'a', 'b', 'a', 'b', 'c'
    len_sir equ $-sir
    subsir db 'a', 'b', 'c'
    len_subsir equ $-subsir
    poz resb len_sir ; in final, R ar trebui sa contina 01h, 05h, 0Ah, 11h
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, len_sir - len_subsir + 1
        mov esi, 0
        mov edi, 0
        jecxz final
        
        repeta:
            mov ebp, 0
            push esi ; punem pozitia curenta pe stiva
            verificam:
                mov al, [sir + esi]
                mov bl, [subsir + ebp]
                cmp al, bl
                jne maiDeparteInSir ; daca 2 caractere nu coincid atunci sarim la repeta3
                inc esi ; daca coincid atunci crestem cei 2 indecsi pentru a verifica si urmatorul caracter
                inc ebp
                cmp ebp, len_subsir ; verificam daca am verificat toate caracterele din cel de-al 2-lea sir
                jl verificam ; daca nu le-am verificat pe toate inseamna ca mai avem de verificat deci sarim la repeta2
                
                ; aici ajungem doar daca am verificat toate caracterele din subsirul 2 si acestea coincid, de
                pop esi ; luam pozitia initiala de pe stiva de unde a inceput cautarea curenta
                mov [poz + edi], esi ; o salvam
                push esi ; punem pozitia initiala inapoi pe stiva
                inc edi
                
            maiDeparteInSir:        
                pop esi ; luam pozitia de unde am facut verificarile trecute
                inc esi ; o incrementam pentru a trece la urmatorul caracter
        loop repeta
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
