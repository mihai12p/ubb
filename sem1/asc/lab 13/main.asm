bits 32

global _stocheaza

segment data use32 class=data public

segment code use32 class=code public
    _stocheaza:
        push ebp
        mov ebp, esp ; cream cadrul de stiva

        pushad ; salvam valorile registriilor pe stiva

        ; CADRUL DE STIVA
        ; [ebp + 0] = valoarea ebp pentru apelant
        ; [ebp + 4] = adresa de retur
        ; [ebp + 8] = lungimea subsirului nostru
        ; [ebp + 12] = adresa de inceput a subsirului nostru
        ; [ebp + 16] = adresa elementului i din sirNumere

        mov ecx, [ebp + 8]
        jecxz final

        cld
        mov esi, [ebp + 12]
        
        dec ecx ; nu avem nevoie de ultimul caracter 'b'
        mov ebx, 0
        .repeat:
            lodsb

            cmp al, '1' ; daca bitul nostru (al) este 1 atunci CF <- 0, altfel CF <- 1
            cmc ; complementam valoarea din CF astfel incat CF = al

            rcl ebx, 1 ; rotim la stanga cu CF
        loop .repeat

        mov edi, [ebp + 16] ; edi <- &(sirNumere[i])
        mov [edi], ebx ; sirNumere[i] <- numarul dorit

    final:
        popad ; restauram valorile registriilor

        mov esp, ebp
        pop ebp ; restauram stiva

        ret