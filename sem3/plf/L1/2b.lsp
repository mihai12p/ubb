;                           { fals, n = 0
;verificaMembru(L1...Ln, A) = verificaMembru(L1, A), L1 lista
;                             T, L1 atom si L1 = A
;                             verificaMembru(L2...Ln, A), altfel }
;L - lista initiala
;A - atomul de verificat
(defun verificaMembru(L A)
    (cond
        ((null L)
            NIL
        )
        ((and (listp (car L)) (verificaMembru (car L) A) )
        )
        ((and (atom (car L)) (equal (car L) A) )
        )
        (T
            (verificaMembru (cdr L) A)
        )
    )
)