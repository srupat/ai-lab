% Facts
parent(john, mary).
parent(mary, susan).
parent(susan, tom).
parent(peter, john).
parent(anna, john).
parent(james, susan).
parent(lucy, tom).

male(john).
male(tom).
male(peter).
male(james).

female(mary).
female(susan).
female(anna).
female(lucy).

% Rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandfather(X, Y) :- grandparent(X, Y), male(X).
grandmother(X, Y) :- grandparent(X, Y), female(X).

sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
brother(X, Y) :- sibling(X, Y), male(X).
sister(X, Y) :- sibling(X, Y), female(X).

uncle(X, Y) :- brother(X, Z), parent(Z, Y).
aunt(X, Y) :- sister(X, Z), parent(Z, Y).
