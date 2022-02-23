;16. Se dau octetul A si cuvantul B. Sa se obtina dublucuvantul C:
;    bitii 0-7 ai lui C au valoarea 1
;    bitii 8-11 ai lui C coincid cu bitii 4-7 ai lui A
;    bitii 12-19 coincid cu bitii 2-9 ai lui B
;    bitii 20-23 coincid cu bitii 0-3 ai lui A
;    bitii 24-31 coincid cu octetului high din cuvantul B

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A db 11010011b
    B dw 1111000011101010b
    C resd 1 ; expected output: 11110000 00110011 10101101 11111111b = F0 33 AD FFh
    
; our code starts here
segment code use32 class=code
    start:
        mov ebx, 0
        mov eax, 0
        
        or bl, 11111111b ; bitii 0-7 din ebx vor avea valoarea 1
        
        mov al, [A] ; al si implicit ax = A
        push eax ; punem eax pe stiva deoarece vom avea nevoie si mai tarziu de aceeasi configuratie de biti
        and al, 11110000b ; izolam bitii 4-7 ai lui A
        mov cl, 4
        shl ax, cl ; vom avea in ax pe pozitiile 8-11 bitii 4-7 din A
        or ebx, eax ; bitii 8-11 din ebx iau valoarea bitilor 4-7 ai lui A
        
        movzx eax, word [B] ; eax = B
        and ax, 0000001111111100b ; izolam bitii 2-9 ai lui B
        mov cl, 10
        shl eax, cl ; pe pozitiile 12-19 avem bitii 2-9 ai lui B
        or ebx, eax ; bitii 12-19 iau valoarea bitilor 2-9 ai lui B
        
        pop eax ; ax = A
        and al, 00001111b ; izolam bitii 0-3 ai lui A
        mov cl, 20
        shl eax, cl ; pe pozitiile 20-23 vom avea bitii 0-3 ai lui A
        or ebx, eax ; bitii 20-23 iau valoarea bitilor 0-3 ai lui A
        
        movzx eax, word [B] ; eax = B
        and ax, 1111111100000000b ; izolam bitii aferenti octetului high din cuvantul B
        mov cl, 16
        shl eax, cl ; pe pozitiile 24-31 avem bitii din octetul high ai cuvantului B
        or ebx, eax ; bitii 24-31 iau valoarea bitilor 8-15 din cuvantul B
        
        mov [C], ebx ; punem rezultatul in dword-ul C
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
