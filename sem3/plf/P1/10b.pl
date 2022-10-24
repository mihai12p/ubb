%             {
%              A, B = 0
%cmmdc(A, B) = B, A % B = 0
%              cmmdc(B, A % B), altfel
%             }
%cmmdc(A:Intreg, B:Intreg, D:Intreg)
%Modele de flux: (i, i, o), (i, i, i)
%A - primul numar
%B - al doilea numar
%D - cel mai mare divizor comun al celor doua numere
cmmdc(A, 0, A) :- !.
cmmdc(A, B, D) :- R is A mod B,
                  cmmdc(B, R, D).

%                 {
%cmmdcL(l1...ln) = l1, n = 1
%                  cmmdcL(cmmdc(l1, l2)...ln), altfel
%                 }
%Lista=Intreg*
%cmmdcL(L:Lista, D:Intreg)
%Modele de flux: (i, o), (i, i)
%L - lista de numere
%D - cel mai mare divizor comun al numerelor din lista
cmmdcL([H | []], H) :- !.
cmmdcL([H1, H2 | T], D) :- cmmdc(H1, H2, R),
                           cmmdcL([R | T], D).
