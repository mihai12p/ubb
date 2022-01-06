; 29. Se citesc de la tastatura trei numere a, m si n (a: word, 0 <= m, n <= 15, m > n). 
; Sa se izoleze bitii de la m-n ai lui a si sa se afiseze numarul intreg reprezentat de acesti bitii in baza 10. 

bits 32

global start        

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a resw 1
    m resb 1
    n resb 1
    format_citire db '%d %d %d', 0
    format_afisare db '%d', 0

segment code use32 class=code
    start:
        ; scanf("%d %d %d", &a, &m, &n)
        push dword n
        push dword m
        push dword a
        push dword format_citire
        call [scanf]
        add esp, 4*4
        
        mov ax, [a]
        mov cl, 15
        sub cl, [m]
        shl ax, cl
        mov cl, [m]
        add cl, [n]
        dec cl
        shr ax, cl
        
        ; printf("%d", eax)
        push dword eax
        push format_afisare
        call [printf]
        add esp, 4*2
    
        ; exit(0)
        push    dword 0
        call    [exit]
