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
    d db 4
    
; our code starts here
segment code use32 class=code
    start:
        ; 12. 2-(c+d)+(a+b-c) unde a,b,c,d - byte
        
        mov al, [c] ; al = c
        add al, [d] ; al = c + d
        
        mov dl, 2 ; dl = 2
        sub dl, al ; dl = dl - al = 2 - (c + d)
        
        mov al, [a] ; al = a
        add al, [b] ; al = a + b
        sub al, [c] ; al = a + b - c
        
        add al, dl ; al = al + dl = (a + b - c) + 2 - (c + d)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
