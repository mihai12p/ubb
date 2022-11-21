%                       {
%                        [E], n = 0
%insereaza(L1...Ln, E) = E + L1...Ln, E < L1
%                        insereaza(L2...Ln, E), altfel
%                       }
%Lista=Intreg*
%insereaza(L:Lista, E:Intreg, R:Lista)
%Modele de flux: (i, i, o) determinist, (i, i, i) determinist
%L - lista initiala
%E - elementul de inserat
%R - lista finala dupa inserare
insereaza([], E, [E]).
insereaza([H | T], E, [E, H | T]) :- E < H.
insereaza([H | T], E, [H | R1]) :- E >= H,
                                   !,
                                   insereaza(T, E, R1).

%                   {
%                    [], n = 0
%sorteaza(L1...Ln) = insereaza(sorteaza(L2...Ln), L1), altfel
%                   }
%Lista=Intreg*
%sorteaza(L:Lista, R:Lista)
%Modele de flux: (i, o) determinist, (i, i) determinist
%L - lista initiala nesortata
%R - lista finala sortata cu pastrarea duplicatelor
sorteaza([], []).
sorteaza([H | T], R) :- sorteaza(T, R1),
                        insereaza(R1, H, R).
