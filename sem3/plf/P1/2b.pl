%                               {
%                                [], n = 0
%adauga1248(L1...Ln, P, PC, V) = L1 + adauga1248(V, L2...Ln), P = PC
%                                L1 + adauga1248(L2...Ln), altfel
%                               }
%Lista=Intreg*
%adauga1248(L:Lista, P:Intreg, V:Intreg, R:Lista)
%Modele de flux: (i, i, i, i) determinist, (i, i, i, o) determinist
%L - lista initiala
%P - pozitia curenta
%V - numarul de adaugat
%R - lista finala dupa adaugare de elemente
adauga1248([], _, _, _, []).
adauga1248([H | T], P, V, PC, [H, V | R]) :- P =:= PC,
                                             !,
                                             P1 is PC * 2,
                                             PC1 is PC + 1,
                                             adauga1248(T, P1, V, PC1, R).
adauga1248([H | T], P, V, PC, [H | R]) :- PC1 is PC + 1,
                                          adauga1248(T, P, V, PC1, R).
adauga1248W(L, V, R) :- adauga1248(L, 1, V, 1, R).
