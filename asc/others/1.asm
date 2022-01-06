; 1. Sa se citeasca de la tastatura doua numere (in baza 10) si sa se calculeze produsul lor. 
; Rezultatul inmultirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date). 
; Extra: rezultatul se afiseaza pe ecran.

bits 32

global start        

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a resd 1
    b resd 1
    rezultat resq 1
    format_citire db '%d %d', 0
    format_afisare db '%d * %d = %lld', 0

segment code use32 class=code
    start:
        ; scanf("%d %d", &a, &b)
        push dword b
        push dword a
        push dword format_citire
        call [scanf]
        add esp, 4*3
        
        mov eax, [a]
        imul dword [b] ; edx:eax = a * b
        mov [rezultat], eax
        mov [rezultat + 4], edx
        
        ; printf("%d * %d = %lld", a, b, rezultat)
        push dword [rezultat + 4]
        push dword [rezultat]
        push dword [b]
        push dword [a]
        push dword format_afisare
        call [printf]
        add esp, 4*5
    
        ; exit(0)
        push    dword 0
        call    [exit]
