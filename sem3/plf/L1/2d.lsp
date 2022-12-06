;                       { T, n = 0
;nuDuplicat(A, L1...Ln) = fals, A = L1
;                         nuDuplicat(A, L2...Ln), altfel }
;A - atomul de cautat
;L - lista initiala
(defun nuDuplicat(A L)
    (cond
        ((null L)
            T
        )
        ((equal A (car L))
            NIL
        )
        (T
            (nuDuplicat A (cdr L))
        )
    )
)

;                        { fals, n = 0
;listaInMultime(L1...Ln) = L1 + listaInMultime(L2...Ln), L1 nu e in multime
;                          listaInMultime(L2...Ln), altfel }
;L - lista initiala
(defun listaInMultime(L)
    (cond
        ((null L)
            NIL
        )
        ((nuDuplicat (car L) (cdr L))
            (cons (car L) (listaInMultime (cdr L)))
        )
        (T
            (listaInMultime (cdr L))
        )
    )
)