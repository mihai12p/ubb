%                                {
%                                 [E], L = []
%inserareNAux(E, l1...ln, N, P) = [E + L], N = P
%                                 inserareNAux(E, l2...ln, N, P + 1),
%                                 altfel
%                                }
%Lista=Element*
%inserareNAux(E:Element, L:Lista, N:Intreg, P:Intreg, R:Lista)
%Modele de flux: (i, i, i, i, o), (i, i, i, i, i)
%E - elementul pe care il inseram in lista
%L - lista initiala
%N - pozitia pe care vrem sa inseram elementul
%P - pozitia elementului curent
%R - lista finala dupa inserare
inserareNAux(E, [], _, _, [E]).
inserareNAux(E, L, N, P, [E | L]) :- N is P.
inserareNAux(E, [H | T], N, P, R) :- inserareNAux(E, T, N, P + 1, R1),
                                     R = [H | R1].

%                          {
%inserareN(E, l1...ln, N) = inserareNAux(E, l1...ln, N, 1)
%                          }
%Lista=Element*
%inserareN(E:Element, L:Lista, N:Intreg, R:Lista) - determinist
%Modele de flux: (i, i, i, o), (i, i, i, i)
%E - elementul pe care il inseram in lista
%L - lista initiala
%N - pozitia pe care vrem sa inseram elementul
%R - lista finala dupa inserare
inserareN(E, L, N, R) :- inserareNAux(E, L, N, 1, R),
                         !.
