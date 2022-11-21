%                    1. -1, L1 >= 0,
%candidat(L1...Ln) = 2.  1, L1 <= 0,
%                    3.  0, abs(L1) = 1
%Lista=Intreg*
%candidat(L:Lista, R:Intreg)
%Modele de flux: (i, o) nedeterminist, (i, i) determinist
%L - lista cu solutii partiale la un moment dat
%R - urmatorul element candidat
candidat([H | _], -1) :- H >= 0.
candidat([H | _],  1) :- H =< 0.
candidat([H | _],  0) :- abs(H) =:= 1.

%                1. [0], P = ultima pozitie
%solutie(N, P) = 2. candidat(solutie(N, P+1)), P < ultima pozitie
%Lista=Intreg*
%solutie(N:Intreg, P:Intreg, R:Lista)
%Modele de flux: (i, i, o) nedeterminist, (i, i, i) determinist
%N - n din enunt
%P - pozitia elementului curent
%R - subsirul de lungime 2n+1 generat
solutie(N, P, [0]) :- P =:= 2*N+1.
solutie(N, P, R) :- P < 2*N+1,
                    P1 is P+1,
                    solutie(N, P1, R1),
                    candidat(R1, X),
                    R = [X | R1].

%                     {
%incepeBine(L1...Ln) = true, L1 = 0
%                      false, altfel
%                     }
%Lista=Intreg*
%incepeBine(L:Lista)
%Modele de flux: (i) determinist
%L - subsirul generat
incepeBine([H | _]) :- H =:= 0.

%solutieW(N) = 1. solutie(N, 1), daca incepeBine(solutie(N, 1))
%Lista=Intreg*
%solutieW(N:Intreg, R:Lista)
%Modele de flux: (i, o) nedeterminist, (i, i) determinist
%N - n din enunt
%R - subsirul de lungime 2n+1 generat
solutieW(N, R) :- solutie(N, 1, R),
                  incepeBine(R).

%toateSolutiile(N) = 1. reuniune(solutieW(N))
%Lista=Intreg*
%toateSolutiile(N:Intreg, R:Lista)
%Modele de flux: (i, o) nedeterminist, (i, i) determinist
%N - n din enunt
%R - subsirurile de lungime 2n+1 generate
toateSolutiile(N, R) :- findall(A, solutieW(N, A), R).
