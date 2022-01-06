; rand A
; Se citesc de la tastatura mai multe numere (intregi, avand intre 3 si 5 cifre) pana la intalnirea simbolului -1.
; Sa se identifice numarul maxim si numarul minim dintre toate numerele introduse. Sa se printeze aceste 2 rezultate
; in fisierul out.txt (fisierul se presupune ca exista), pe linii separate.
; Sa se calculeze produsul celor 2 valori (min si max). Salvati acest rezultat in memorie, in variabila r.
;       Ex: Daca se introduc nr 333, 444, 111, 101, 55555 atunci se va printa in fisier
;                                                                       101
;                                                                       55555
;                       Iar in R va fi valoarea 5611055

bits 32

global start        

extern exit, fopen, fprintf, fclose, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    fisier db 'out.txt', 0
    mod_fisier db 'w', 0
    format db '%d', 0
    format_fprintf db '%d', 10, 0
    x resd 1
    min dd 999999
    max dd -999999
    handle dd -1
    r resq 1

segment code use32 class=code
    start:
        repeat:
            ; scanf("%d", &x)
            push dword x
            push dword format
            call [scanf]
            add esp, 4*2

            cmp dword [x], -1
            je inter
            
            mov eax, [x]
            cmp dword [min], eax
            jg minim
            maxim:
                mov dword [max], eax
                jmp repeat
            
            minim:
                mov dword [min], eax
        jmp repeat
        
        inter:
            ; fopen("out.txt", "w")
            push dword mod_fisier
            push dword fisier
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0
            je final
            
            mov [handle], eax
            
            ; fprintf(handle, "%d\n", min)
            push dword [min]
            push dword format_fprintf
            push dword [handle]
            call [fprintf]
            add esp, 4*3
            
            ; fprintf(handle, "%d\n", max)
            push dword [max]
            push dword format_fprintf
            push dword [handle]
            call [fprintf]
            add esp, 4*3
                
            mov eax, dword [min]
            imul dword [max] ; edx:eax = rezultat
            mov [r + 4], edx
            mov [r], eax
            
            ; fclose(handle)
            push dword [handle]
            call [fclose]
            add esp, 4*1
        
        final:
    
        ; exit(0)
        push    dword 0
        call    [exit]