bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 3
    b db 7
    c dw 2
    d db 4
    e dd 5
    x dq 6

; our code starts here
segment code use32 class=code
    start:
        ; 16. x/2+100*(a+b)-3/(c+d)+e*e; a,c-word; b,d-byte; e-doubleword; x-qword (fara semn)
        
        mov eax, dword [x + 0] ; eax = partea low din quadword-ul x
        mov edx, dword [x + 4] ; edx:eax = x
        mov ebx, 2
        div ebx ;  eax = x / 2; edx = x % 2
        mov bx, [a]
        movzx cx, byte [b]
        add bx, cx ; bx = a + b
        mov ecx, eax ; ecx = x / 2
        mov eax, 0
        mov ax, 100
        mul bx ; dx:ax = ax * bx = 100 * (a + b)
        push dx
        push ax
        pop ebx
        add ebx, ecx ; ebx = x / 2 + 100 * (a + b)
        mov ecx, 0
        movzx cx, byte [d]
        add cx, [c] ; cx = c + d
        mov dx, 0
        mov ax, 3; dx:ax = 3
        div cx ; ax = 3 / (c + d); dx = 3 % (c + d)
        mov cx, ax ; cx = 3 / (c + d)
        movzx eax, cx
        sub ebx, eax ; ebx = x / 2 + 100 * (a + b) - 3 / (c + d)
        mov eax, [e]
        mul dword [e] ; edx:eax = e * e
        add eax, ebx
        adc edx, 0 ; edx:eax = x / 2 + 100 * (a + b) - 3 / (c + d) + e * e
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
