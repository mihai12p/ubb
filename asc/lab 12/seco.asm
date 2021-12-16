bits 32       

global _calc

segment code use32 class=code public
    _calc:
        ; [esp + 0] = adresa de retur
        ; [esp + 4] = a
        ; [esp + 8] = b
        ; [esp + 12] = c
        
        mov eax, [esp + 4]
        add eax, [esp + 8]
        sub eax, [esp + 12]
        
        ret
