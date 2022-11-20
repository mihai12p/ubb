%                                    {
%                                     [], n = 0 sau M = N
%                                     M1 + diferentaMultimi(M2...Mn,
%diferentaMultimi(M1...Mn, N1...Nm) =     N1...Nm), M1 nu apartine lui N
%                                     diferentaMultimi(M2...Mn,
%                                         N1...Nm), altfel
%                                    }
%Multime=Element*
%diferentaMultimi(M:Multime, N:Multime, R:Multime)
%Modele de flux: (i, i, o) determinist, (i, i, i) determinist
%M - multimea descazut
%N - multimea scazator
%R - multimea rezultat
diferentaMultimi([], _, []) :- !.
diferentaMultimi(M, M, []).
diferentaMultimi([H | T], N, [H | R1]) :- not(apartine(H, N)),
                                          !,
                                          diferentaMultimi(T, N, R1).
diferentaMultimi([_ | T], N, R) :- diferentaMultimi(T, N, R).

%                      {
%apartine(E, M1...Mn) = true, daca E = M1
%                       apartine(E, M2...Mn), altfel
%                      }
%Multime=Element*
%apartine(E:Element, M:Multime)
%Modele de flux: (i, i) determinist, (i, o) determinist
%E - elementul verificat daca apartine multimii M
%M - multimea in care se cauta elementul E
apartine(E, [E | _]) :- !.
apartine(E, [_ | T]) :- apartine(E, T).
