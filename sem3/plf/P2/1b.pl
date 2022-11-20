adaugaFinal(E,[],[E]).
adaugaFinal(E,[H|T],[H|T1]):-
	adaugaFinal(E,T,T1).

inverseazaLista([],[]).
inverseazaLista([H|T],L):-
	inverseazaLista(T,L1),
	adaugaFinal(H,L1,L).


suma([],[],1,[1]):-
	!.

suma([],[],_,[]).


suma(L1,[],T,L1):-T=0.

suma([],L2,T,L2):-T=0.



suma([],L2,1,R):-
	suma([1],L2,0,R).



suma(L1,[],1,R):-
	suma([1],L1,0,R).



suma([H1|T1],[H2|T2],T,[Hs|TS]):-
	S is H1+H2+T,
	Tn is S div 10,
	Hs is S mod 10,
	suma(T1,T2,Tn,TS).


suma(L1,L2,FinalR):-
	inverseazaLista(L1,InvL1),
	inverseazaLista(L2,InvL2),
	suma(InvL1,InvL2,0,R),
        inverseazaLista(R,FinalR),
	!.

sumaNrSubliste([],[]).
sumaNrSubliste([H|T],R):-is_list(H),
	sumaNrSubliste(T,R1),
	suma(H,R1,R),
        !.

sumaNrSubliste([_|T],R):-
	sumaNrSubliste(T,R).
