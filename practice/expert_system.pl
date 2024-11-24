start :-
    write('Welcome to medical diagnosis expert system'), nl,
    write('Answer the following questions with "yes." or "no."'),nl,
    diagnose(Disease),
    write('You might have the following disease : '), write(Disease).

diagnose(covid) :- covid_symptoms, !.
diagnose(cold) :- cold_symptoms, !.
diagnose(flu) :- flu_symptoms, !.
diagnose(no_disease) :- write('You dont have any disease'), nl.

covid_symptoms :-
    verify(cough),
    verify(cold),
    verify(tastelessness),
    verify(shortness_of_breath).

cold_symptoms :-
    verify(cold),
    verify(fever).

flu_symptoms :-
    verify(fever),
    verify(tiredness).

verify(Symptom) :- 
    write('Do you have '), write(Symptom), write('? '), nl,
    read(Response), nl,
    (Response == 'yes' ; Response == 'y').