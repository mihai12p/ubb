bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    d db 6
    e dw 12
    f dw 15
    
; our code starts here
segment code use32 class=code
    start:
        ; 15. f*(e-2)/[3*(d-5)] unde a,b,c,d-byte, e,f,g,h-word (FARA SEMN)

        mov al, [d]
        sub al, 5
        mov bl, 3
        mul bl ; ax = 3 * (d - 5)
        mov bx, ax ; bx = 3 * (d - 5)
        mov ax, [e]
        sub ax, 2
        mul word [f] ; dx:ax = f * (e - 2)
        div bx ; dx - restul si in ax = catul

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
