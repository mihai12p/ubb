;                           { fals, n = 0
;selecteazaN(L1...Ln, N, P) = L1, N = P
;                             selecteazaN(L2...Ln, N, P+1), altfel }
;L - lista initiala
;N - n din enunt
;P - numarul elementului curent
(defun selecteazaN(L N P)
    (cond
        ((null L)
            NIL
        )
        ((equal N P)
            (car L)
        )
        (T
            (selecteazaN (cdr L) N (+ P 1))
        )
    )
)

;selecteazaNW(L1...Ln, N) = selecteazaN(L1...Ln, N, 1)
;L - lista initiala
;N - n din enunt
(defun selecteazaNW(L N)
    (selecteazaN L N 1)
)