Jade Kelovesi
C++ perusteet
Hotellin varaus harjoitustyö
Tavoittelen numeroa 3


Ohjelma on luotu hotellihuoneiden varaamiseen, joka toimii kuvitteellisen Paratiisi Tunturi Hotellin alustavana varausjärjestelmänä.
Ohjelmassa on mahdollisuus varata huoneita, tarkastella varauksia sekä hinnastoa.

Ohjelmassa on säädetty huonenumerot välille 40-300, joista ensimmäiset 130 eli huoneet 40-170 ovat yhden 
hengen huoneita (1hh) ja loput 170-300 ovat kahden hengen huoneita. Jos varaaja yrittää varata muunlaisen 
huoneen, ohjelma kertoo varaajalle, ettei muunlaisia huoneita ole saatavilla. Huone varataan syöttämällä nimi, huonetyyppi tai koko
sekä yövyttävien öiden määrä. huone valitaan ohjelman puolesta satunnaisesti. Varaus sisältää arvotun mahdollisen
alennuksen, joka on 10% tai 20%. Myös ilman alennusta saattaa varaaja jäädä. Ohjelma tarkistaa onko huone vapaa ja onko sellaista mahdollist varata.

Varauksia voi tarkastella syöttämällä ohjelmaan varaajan nimen tai varausnumeron. Jos varausta ei löydy, ohjelma ilmoittaa myös siitä.
Ohjelmassa on myös mahdollista tarkkailla hinnastoa, sekä tarkastella palveluita omalta sivultaan.

Menusta löytyy 4 osiota, joista voi varata, tarkistaa varauksensa sekä katsella hinnastoa. Tein hinnaston ylimääräisenä toteutuksena. 
Ohjelman saa myös suljettua valikosta. Valikosta pääsee eri sivuille valitsemalla numeron. valikon kautta 
avatut sivut avaavat alareunaan näkymän, jota kautta ohjelma pyytää painamaan x ja enter, jos haluaa takaisin valikkoon.
Halusin lisätä myös siivouspalvelun hinnastoon, joka on ilmainen, jos henkilö yöpyy 3 tai enemmän yötä hotellissa.

Ohjelma käyttää myös satunnaislukugeneraattoria varausnumeron luomiseksi. Ohjelma on muutenkin luotu hyvin satunnaistietojen pohjalta.

Kehitystä olisi ollut osaamisen puolesta voinut jatkaa pidemmälle. Kärsivällisyyttä tähän ei kuitenkaan pidemmän päälle liikaa ollut.
Ohjelmaan olisi voinut luoda talletuksen, joka pitäisi varaustiedot tallessa pidemmällä aika välillä. Haaveena oli myös lisätä oma varaus
järjestelmä mahdollisille hotelliaktiviteeteille ja tehdä näille omat aliohjelmansa. Huoneiden tilaa olisi myös hyvä tarkkailla erillisellä
listalla, joka välttäisi päällekkäisiä varauksia.

