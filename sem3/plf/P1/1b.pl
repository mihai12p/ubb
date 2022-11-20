%                        {
%                         [], n = 0
%adaugaDupaPar(L1...Ln) = L1 + adaugaDupaPar(1, L2...Ln), L1 par
%                         L1 + adaugaDupaPar(L2...Ln), altfel
%                        }
%Lista=Intreg*
%adaugaDupaPar(L:Lista, R:Lista)
%Modele de flux: (i, i) determinist, (i, o) determinist
%L - lista initiala
%R - lista finala dupa adaugare de elemente
adaugaDupaPar([], []).
adaugaDupaPar([H | T], [H, 1 | R]) :- H mod 2 =:= 0,
                                      !,
                                      adaugaDupaPar(T, R).
adaugaDupaPar([H | T], [H | R]) :- adaugaDupaPar(T, R).
