
	Jocuri de carti

1)Creaam pachetul de carti printr-o lista simplu inlantuita cum este cerut
in enunt.

2) Amestecare:
I)Inversare: parcurgem lista in mod recursiv, iar de la sfarsit catre inceputul
listei inversam legaturile dintre noduri

II)N_Piles: parcurgem lista, impartind-o in cele N pachete cerute, retinandu-se
pentru fiecare pachet referinta catre primul nod. Ulterior, "legam" pacghetele
intre ele(ultimul nod al pachetului precedent cu primul nod al pachetului curent)
in ordinea ceruta

III)Intercalare: impartim pachetul in doua parti si introducem dupa fiecare carte din primul
pachet cate o carte din al doilea pachet

IV)Mongean: 
	Luam pachetul initial si adaugam cate o carte atat la inceput, cat si 
la sfarst, retinand o referinta catre inceputul listei, cat si catre sfarsit.

3)Razboi: 
	Impartim pachetul in doua parti egale si facem urmatorii pasi pana cand
unul dintre jucatori castiga sau se ajunge la runda 100:
se alege cartea de la inceputul pachetului al fiecaruia dintre jucatori si se compara.
Daca cartea unuia este mai mare, ambele carti sunt luate de acest jucator. Altfel,
cream doua stive in care introducem cartile "intoarse" de catre jucatori(in numar de
min(min(nr_cărți_jucător1, valoare_carte_război), min(nr_cărți_jucător2,
valoare_carte_război))), le comparam pe ultimele puse in stiva si jucatorul
care are cartea cu o valoare mai mare, ia ambele pachete.

	In cazul in care se ajunge la runda 100 fara ca niciun jucator sa castige,
folosim un vector de frecventa prin camera numaram cartile de fiecare tip, in ordine 
inversa valorii, pana cand unul dintre jucatorii are mai multe carti de acel tip
fata de celalalt jucator, acesta fiind castigatorul jocului

4) Rolling Stone
	Impartim cartile fiecarui jucator dupa ce au fost amestecate conform cerintei.
Cream o lista circulara in care retinem culorile in ordinea s->h->c->d si cate 
carti de culoarea respectiva are fiecare jucator.
	La fiecare runda noua, jucatorul curent incepe cu o culoare in functie de
disponibilitate in ordinea data de lista circulara, scadem din numarul de carti
de culoarea jucata de la jucator, si trecem la urmatorul. Pana cand unul dintre
jucatori termina toate cartile din mana, verificam daca are culoare cartilor
date deja jos: daca are, se adauga la pachetul "round" - cartile jucate; 
daca nu are, introducem cartile deja jucate la pachetul din mana, trecem
la urmatoarea culoare si la o runda noua, ramanand la acelasi jucator(
el incepe la runda urmatoare).

5)	Scarabeii Egipteni
	Amestecam cartile si le impartim fiecarui jucator dupa ce au fost
amestecate conform cerintei.
	Cream o lista dublu inlantuita circulara in care retinem jucatorii->
cartile pe care le au in mana, numarul asociat ordinii(0->3 sau -1 daca a 
iesit din joc).
	Jucam jocul pana cand ramane un singur jucator. Cream pentru fiecare
runda o stiva in care adaugam cartea jucata de fiecare jucator pe rand.
Daca "pe masa" se afla o carte cu numar sau o carte speciala(8), cartea
jucata va influenta doar daca se schimba directia(in cazul lui 8),
sau daca avem un potential castigator(se da un scarabeu). Daca este un 8,
se procedeaza analog.
	Daca este un scarabeu "pe masa", updatam castigatorul(winner) daca
este jucat un alt scarabeu, anulam efectul ultimului scarabeu daca se 
da o carte speciala(winner se reinitializeaza) sau eliberam stiva cand se
da o carte cu numar peste un scarabeu, deci jucatorul care a dat scarabeul
castiga runda si i se adauga in pachet cartile din stiva.
	De fiecare data, verificam daca jucatorul curent mai are carti in mana
si daca mai poate castiga in aceasta instanta pentru a putea updata numarul
de jucatori.
La final, se verifica ce jucator are cartile, acela fiind castigatorul
