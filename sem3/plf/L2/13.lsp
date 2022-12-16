;                    { fals, n = 0
;contine(L1...Ln, E) = T, L1 = E 
;                      T, contine(L2, E)
;                      contine(L3, E), altfel }
;L - subarborele in care se cauta nodul E
;E - nodul de cautat
(defun contine(L E)
    (cond
        ((null L)
            nil
        )
        ((equal (car L) E))
        ((contine (cadr L) E))
        ((contine (caddr L) E))
    )
)

;                 { fals, n = 0
;                   (E), L1 = E
;cale(L1...Ln, E) = (L1 + cale(L2, E)), contine(L2, E)
;                   (L1 + cale(L3, E)), contine(L3, E)
;                   fals, altfel }
;L - arborele reprezentat sub forma de lista in V2
;E - nodul dat din enunt
(defun cale(L E)
    (cond
        ((null L)
            nil
        )
        ((equal (car L) E)
            (list E)
        )
        (((lambda (s d)
            (cond
                ((contine s E)
                    (cons (car L) (cale s E))
                )
                ((contine d E)
                    (cons (car L) (cale d E))
                )
                (T
                    nil
                )
            )    
        ) (cadr L) (caddr L)))
    )
)