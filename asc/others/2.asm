; 2. Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a/b. 
; Catul impartirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date). 
; Valorile se considera cu semn. Extra: rezultatul se afiseaza pe ecran.

bits 32

global start        

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a resq 1
    b resd 1
    catul resd 1
    restul resd 1
    format_citire db '%lld %d', 0
    format_afisare db '%lld / %d = %d rest %d', 0

segment code use32 class=code
    start:
        ; scanf("%lld %d", &a, &b)
        push dword b
        push dword a
        push dword format_citire
        call [scanf]
        add esp, 4*3
        
        mov edx, [a + 4]
        mov eax, [a] ; edx:eax = a
        idiv dword [b] ; eax = catul | edx = restul
        mov [catul], eax
        mov [restul], edx
        
        ; printf("%lld / %d = %d rest %d", a, b, catul, restul)
        push dword [restul]
        push dword [catul]
        push dword [b]
        push dword [a + 4]
        push dword [a]
        push dword format_afisare
        call [printf]
        add esp, 4*6
    
        ; exit(0)
        push    dword 0
        call    [exit]
