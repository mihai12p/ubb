bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 4
    b dw 3
    c dw 5
    d dw 19

; our code starts here
segment code use32 class=code
    start:
        ; 12. d-(a+b)-(c+c) unde a,b,c,d - word
           
        mov ax, [d] ; ax = d
        
        mov dx, [a] ; dx = a
        add dx, [b] ; dx = dx + b = a + b
        
        sub ax, dx ; ax = d - (a + b)
        
        mov dx, [c] ; dx = c
        add dx, dx ; dx = dx + dx = c + c
        
        sub ax, dx ; ax = d - (a + b) - (c + c)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
