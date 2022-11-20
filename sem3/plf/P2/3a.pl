insereaza2(E, [], [E]) :- !.
insereaza2(E, [H | T], [E, H | T]) :- E =< H.
insereaza2(E, [H | T], [H | R]) :- E > H,
                                   insereaza2(E, T, R).

sorteaza2([], []) :- !.
sorteaza2([H | T], R) :- sorteaza2(T, R1),
                         not(in_list(H, R1)),
                         !,
                         insereaza2(H, R1, R).
sorteaza2([_ | T], R) :- sorteaza2(T, R).

in_list(E, [E | _]) :- !.
in_list(E, [_ | T]) :- in_list(E, T).
