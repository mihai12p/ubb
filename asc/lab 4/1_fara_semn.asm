bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 3
    b db 7
    c db 2
    d dw 4
    
; our code starts here
segment code use32 class=code
    start:
        ; 15. (a*2)+2*(b-3)-d-2*c unde a,b,c - byte, d - word (FARA SEMN)
        
        mov al, 2
        mul byte [a] ; ax = a * 2
        mov bx, ax ; bx = a * 2
        mov dl, [b]
        sub dl, 3 ; dl = b - 3
        mov ax, 0
        mov al, 2
        mul dl ; ax = al * dl = 2 * (b - 3)
        add bx, ax ; bx =(a * 2) + 2 * (b - 3)
        sub bx, [d] ; bx =(a * 2) + 2 * (b - 3) - d
        mov ax, 0
        mov al, 2
        mul byte [c] ; ax = 2 * c
        sub bx, ax ; bx =(a * 2) + 2 * (b - 3) - d - 2 * c

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
