;                       { fals, n = 0
;toateSubliste(L1...Ln) = L1 + toateSubliste(L1) + toateSubliste(L2...Ln), L1 lista
;                         toateSubliste(L2...Ln), altfel }
;L - lista initiala intr-o lista
(defun toateSubliste(L)
    (cond
        ((null L)
            NIL
        )
        ((listp (car L))
            (cons (car L) (append (toateSubliste (car L)) (toateSubliste (cdr L))))
        )
        (T
            (toateSubliste (cdr L))
        )
    )
)

;toateSubliste(L1...Ln) = toateSubliste(lista(L1...Ln))
;L - lista initiala
(defun toateSublisteW(L)
    (toateSubliste (list L))
)