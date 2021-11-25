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
        mov esi, sir ; copiem offsetul primului sir in ds:esi
        mov ebx, 0
        cld ; DF = 0 adica parcurgem sirurile de la stanga la dreapta
        jecxz final
        
        repeta:
            mov edi, subsir ; copiem offsetul subsirului in es:edi
            push esi ; punem offsetul sirului curent pe stiva
            verificam:
                cmpsb ; cmp [ds:esi], byte [es:edi]; inc esi; inc edi
                jne maiDeparteInSir ; daca 2 caractere nu coincid atunci sarim la maiDeparteInSir
                cmp edi, subsir+len_subsir ; verificam daca am parcurs toate caracterele din subsir
                jl verificam ; daca nu le-am parcurs pe toate inseamna ca mai avem de parcurs
                
                ; aici ajungem doar daca am parcurs intreg subsirul si acesta se regaseste in sir
                pop esi ; luam offsetul de pe stiva de unde a inceput cautarea curenta
                mov edx, esi
                sub edx, sir ; offset sir curent - offset sir initial = pozitia la care incepe subsir-ul cautat
                mov [poz + ebx], edx ; o salvam
                inc ebx
                push esi ; punem offsetul unde am ramas inapoi pe stiva
                
            maiDeparteInSir:        
                pop esi ; luam offsetul de unde am facut verificarile trecute
                inc esi ; il incrementam pentru a parcurge mai departe
        loop repeta
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
