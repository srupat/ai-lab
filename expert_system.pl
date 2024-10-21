% Start the expert system
start :-
    write('COVID-19 Diagnosis Expert System'), nl,
    write('Answer the following questions with "yes." or "no."'), nl, nl,
    diagnosis(Disease),
    write('Based on the symptoms, the diagnosis is: '), write(Disease), nl, nl.

% Possible diagnoses
diagnosis(covid19) :- covid_symptoms, !.
diagnosis(common_cold) :- cold_symptoms, !.
diagnosis(flu) :- flu_symptoms, !.
diagnosis(no_disease) :- write('No significant symptoms of COVID-19 detected.'), nl.

% COVID-19 specific symptoms
covid_symptoms :-
    verify(fever),
    verify(cough),
    verify(shortness_of_breath),
    verify(loss_of_taste_or_smell),
    verify(tiredness).

% Common cold symptoms
cold_symptoms :-
    verify(sneezing),
    verify(runny_nose),
    verify(sore_throat),
    verify(mild_cough).

% Flu symptoms
flu_symptoms :-
    verify(fever),
    verify(cough),
    verify(body_aches),
    verify(sore_throat),
    verify(headache).

% Helper to ask about symptoms
verify(Symptom) :-
    write('Do you have '), write(Symptom), write('? '),
    read(Reply),
    (Reply == yes ; Reply == y).
