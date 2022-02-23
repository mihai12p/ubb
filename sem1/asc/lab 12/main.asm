; 5. Se cere se se citeasca numerele a, b si c ; sa se calculeze si sa se afiseze a+b-c.

bits 32

global start        

extern exit, scanf, printf, _calc
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
               
segment data use32 class=data public
    a dd 0
    b dd 0
    c dd 0
    cit_a db "Introduceti a: ", 0
    cit_b db "Introduceti b: ", 0
    cit_c db "Introduceti c: ", 0
    format_citire db "%d", 0
    format_afisare db "Rezultatul operatiei este: %d", 0

segment code use32 class=code public
    start:
        ; afisez mesaj a - printf(cit_a)
        push dword cit_a
        call [printf]
        add esp, 4*1
        ; citesc a - scanf("%d", a)
        push dword a
        push dword format_citire
        call [scanf]
        add esp, 4*2
        
        ; afisez mesaj b - printf(cit_b)
        push dword cit_b
        call [printf]
        add esp, 4*1
        ; citesc b - scanf("%d", b)
        push dword b
        push dword format_citire
        call [scanf]
        add esp, 4*2
        
        ; afisez mesaj c - printf(cit_c)
        push dword cit_c
        call [printf]
        add esp, 4*1
        ; citesc c - scanf("%d", c)
        push dword c
        push dword format_citire
        call [scanf]
        add esp, 4*2
        
        ; apelez functia de calcul - _calc(a, b, c)
        push dword [c]
        push dword [b]
        push dword [a]
        call _calc
        add esp, 4*3
        
        ; afisez rezultatul - printf("Rezultatul operatiei este: %d", eax)
        push eax
        push format_afisare
        call [printf]
        add esp, 4*2
        
        push    dword 0
        call    [exit]
