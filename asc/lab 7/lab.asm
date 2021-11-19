;18. Se dau 2 siruri de octeti A si B. 
;    Sa se construiasca sirul R care sa contina doar elementele impare si pozitive din cele 2 siruri. 

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A db 'a', 'b', 'c', 'd', -1, -2, -3, 1, 2, -4, 3, 3
    len_A equ $-A
    B db 'z', 68, 95, -12, -9, 65
    len_B equ $-B
    R resb len_A + len_B ; in final, R ar trebui sa contina 'a', 'c', 1, 3, 3, 95, 65
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, len_A ; ecx = nr. de octeti ai sirului A
        mov esi, 0
        mov edi, 0
        jecxz final
        
        repeat_A:
            mov al, [A + esi]
            test al, 1 ; ZF = 0 daca al e impar => ZF = 1 daca al e par
            jz par ; daca ZF = 1 sarim la par, altfel verificam daca al e pozitiv
                cmp al, 0
                jl negativ ; daca al < 0 atunci e al e negativ si sarim la negativ, atlfel il adaugam in noul sir R
                    mov [R + edi], al
                    inc edi
                negativ:
            par:
            inc esi
        loop repeat_A
        
        final:
            mov ecx, len_B ; ecx = nr. de octeti ai sirului B
            mov esi, 0
            jecxz finalDeTot
            
            repeat_B:
                mov al, [B + esi]
                test al, 1 ; ZF = 0 daca al e impar => ZF = 1 daca al e par
                jz parB ; daca ZF = 1 sarim la par, altfel verificam daca al e pozitiv
                    cmp al, 0
                    jl negativB ; daca al < 0 atunci e al e negativ si sarim la negativ, atlfel il adaugam in noul sir R
                        mov [R + edi], al
                        inc edi
                    negativB:
                parB:
                inc esi
            loop repeat_B
            
            finalDeTot:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
