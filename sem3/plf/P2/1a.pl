%                         {
%adaugaFinal(l1...ln, E) = [E], n = 0
%                          l1 + adaugaFinal(l2...ln), altfel
%                         }
%Lista=Intreg*
%adaugaFinal(L:Lista, E:Intreg, R:Lista)
%Modele de flux: (i, i, o), (i, i, i)
%L - lista initiala
%E - elementul de adaugat
%R - lista finala dupa adaugare
adaugaFinal([], E, [E]).
adaugaFinal([H | T], E, [H | R]) :- adaugaFinal(T, E, R).

%                {
%lungime(l1...ln) = 0, n = 0
%                   1 + lungime(l2...ln), altfel
%                }
%Lista=Intreg*
%lungime(L:Lista, R:Intreg)
%Modele de flux: (i, o), (i, i)
%L - lista initiala
%R - lungimea listei
lungime([], 0).
lungime([_ | T], R) :- lungime(T, R2),
                       R is R2 + 1.

%                          {
%                           [], n = 0
%inverseazaLista(l1...ln) = adaugaFinal(inverseazaLista(l2...ln), l1),
%                           altfel
%                          }
%Lista=Intreg*
%inverseazaLista(L:Lista, R:Lista)
%Modele de flux: (i, o), (i, i)
%L - lista initiala
%R - lista inversata
inverseazaLista([], []).
inverseazaLista([H | T], R) :- inverseazaLista(T, RI),
                               adaugaFinal(RI, H, R).

%                              {
%                               A1...An, m = 0
%                               B1...Bm, n = 0
%suma_liste(A1...An, B1...Bm) = inverseazaLista(suma(inverseazaLista(A1...An),
%                               inverseazaLista(B1...Bm), 0)), n <= m
%                               inverseazaLista(suma(inverseazaLista(B1...Bm),
%                               inverseazaLista(A1...An), 0)), altfel
%                              }
%Lista=Intreg*
%suma_liste(A:Lista, B:Lista, R:Lista)
%Modele de flux: (i, i, o), (i, i, i)
%A - lista 1
%B - lista 2
%C - lista dupa adunarea celor 2 numere sub forma de lista
suma_liste(A, [], A) :- !.
suma_liste([], B, B) :- !.
suma_liste(A, B, R) :- lungime(A, LA),
                       lungime(B, LB),
                       LA =< LB,
                       inverseazaLista(A, RA),
                       inverseazaLista(B, RB),
                       suma(RA, RB, 0, RS),
                       inverseazaLista(RS, R).
suma_liste(A, B, R) :- lungime(A, LA),
                       lungime(B, LB),
                       LA > LB,
                       inverseazaLista(A, RA),
                       inverseazaLista(B, RB),
                       suma(RB, RA, 0, RS),
                       inverseazaLista(RS, R).

%                           {
%                            [], n = 0, m = 0, C = 0
%                            [1], n = 0, m = 0, C = 1
%                            (B1 + C) + suma([], B2...Bm, 0), n = 0, B1
%                             + c < 10
%suma(A1...An, B1...Bm, C) = ((B1 + C) % 10) + suma([], B2...Bm, 1), n =
%                             0, B1 + C > 10
%                            (A1 + B1 + C) + suma(A2...An, B2...Bm, 0),
%                             A1 + B1 + C < 10
%                            ((A1 + B1 + C) % 10) + suma(A2...An,
%                             B2...Bm, 1), A1 + B1 + C > 10
%                           }
%Lista=Intreg*
%suma(A:Lista, B:Lista, C:Intreg, R:Lista)
%Modele de flux: (i, i, i, o), (i, i, i, i)
%A - lista 1
%B - lista 2
%C - valoare transport
%R - lista dupa adunarea celor 2 numere sub forma de lista
suma([], [], 0, []) :- !.
suma([], [], 1, [1]) :- !.
suma([], [HB | TB], C, [HBC | R]) :- HBC is (HB + C) mod 10,
                                     HBC - HB - C =:= 0,
                                     suma([], TB, 0, R).
suma([], [HB | TB], C, [HBC | R]) :- HBC is (HB + C) mod 10,
                                     HBC - HB - C =\= 0,
                                     suma([], TB, 1, R).
suma([HA | TA], [HB | TB], C, [HR | R]) :- HR is (HA + HB + C) mod 10,
                                           HR - HA - HB - C =:= 0,
                                           suma(TA, TB, 0, R).
suma([HA | TA], [HB | TB], C, [HR | R]) :- HR is (HA + HB + C) mod 10,
                                           HR - HA - HB - C =\= 0,
                                           suma(TA, TB, 1, R).

%                 {
%                  [], n = 0
%listaB(l1...ln) = suma_liste(l1, listaB(l2...ln)), is_list(l1) = True
%	           listaB(l2...ln), altfel
%                 }
%Lista=Element*
%listaB(L:Lista, R:Lista)
%Modele de flux: (i, o), (i, i)
%L - lista ce contine numere sub forma de lista
%R - lista dupa adunarea tuturor numerelor sub forma de liste
listaB([], []).
listaB([H | T], R) :- is_list(H),
                      listaB(T, RH),
                      suma_liste(H, RH, R).
listaB([H | T], R) :- number(H),
                      listaB(T, R).




