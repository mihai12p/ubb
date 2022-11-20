%	         {
%                  0, n = 0
%cmmmcL(L1...Ln) = L1, n = 1
%                  cmmmcL(cmmmc(L1, L2)...Ln)
%	         }
%Lista=Intreg*
%cmmmcL(L:Lista, R:Intreg)
%Modele de flux: (i, i) determinist, (i, o) determinist
%L - lista initiala
%R - cmmmc al numerelor din L
cmmmcL([], 0).
cmmmcL([H], H) :- !.
cmmmcL([H1, H2 | T], R) :- cmmmc(H1, H2, R1),
                           cmmmcL([R1 | T], R).

%             {
%cmmdc(A, B) = A * B / cmmdc(A, B)
%             }
%cmmdc(A:Intreg, B:Intreg, R:Intreg)
%Modele de flux: (i, i, o), (i, i, i)
%A - primul numar
%B - al doilea numar
%D - cel mai mic multiplu comun al celor doua numere
cmmmc(A, B, R) :- cmmdc(A, B, C),
                  R is A * B / C.

%             {
%              A, B = 0
%cmmdc(A, B) = cmmdc(B, A % B), altfel
%             }
%cmmdc(A:Intreg, B:Intreg, R:Intreg)
%Modele de flux: (i, i, o), (i, i, i)
%A - primul numar
%B - al doilea numar
%D - cel mai mare divizor comun al celor doua numere
cmmdc(A, 0, A) :- !.
cmmdc(A, B, R) :- X is A mod B,
                  cmmdc(B, X, R).
