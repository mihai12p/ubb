;             { (T), L atom & L = E
;membru(L, E) = fals, L atom & L != E 
;               reuniniune(membru(Li)), altfel, unde Li lista (L1...Ln) }
;               i=1,n
;L - lista in care se cauta atomul E
;E - atomul de verificat daca exista in lista
(defun membru(L E)
    (cond
        ((and (atom L) ((lambda (x)
            (cond
                (x (list T))
                (t NIL)
            )
        ) (equal L E))))
        (T
            (mapcan #'(lambda (x) (membru x E)) L)
        )
    )
)

;membruW(L1...Ln, E) = L1, membru(L1...Ln, E)
;L - lista in care se cauta atomul E
;E - atomul de verificat daca exista in lista
(defun membruW(L E)
    (car (membru L E))
)