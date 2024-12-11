//Jade Kelovesi
//Harjoitustyö, Hotellihuoneen varaus ohjelma, Paratiisi Tunturi Hotelli
//Odotan saavani numeroksi 4

//Otetaan kirjastoja käyttöö. Vielä ei varmaa mitä kaikkea tarvitsen
#include <iostream>
#include <cmath>
#include <string>
#include <locale>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

const int MAX_HUONEET = 300;
const int MIN_HUONEET = 40;
const int MAX_YHDEN_HENGEN_HUONEET = 130;
const int MAX_KAHDEN_HENGEN_HUONEET = 130;

int arvo_varausnumero() {
    return rand() % 90000 + 10000;  // Varausnumero välillä 10000-99999, arvotaan satunnaisena
}

struct Varaustiedot {//Mitä varaustietoja meillä onkaan tässä
    int varausnumero;
    string nimi;
    int huoneen_numero;
    bool onko_vapaa;
    string huoneen_koko;
    int öiden_määrä;
    double hinta;
    double alennus;//Lasketaan alennus
    double siivousmaksu; //Tein lisäosana siivousmaksu editin
};

vector<Varaustiedot> varaukset;
int yhden_hengen_huoneet = MAX_YHDEN_HENGEN_HUONEET;
int kahden_hengen_huoneet = MAX_KAHDEN_HENGEN_HUONEET;

bool tarkista_huone_vapaa(int huone_numero) {
    for (const auto& varaus : varaukset) {
        if (varaus.huoneen_numero == huone_numero && !varaus.onko_vapaa) {
            return false;  // Huone ei ole vapaa
        }
    }
    return true;  // Huone on vapaa
}

double laske_hinta(string huonetyyppi, int oiden_maara, double alennus, double& siivousmaksu) {
    double hinta_per_yo = (huonetyyppi == "1hh") ? 100 : 150;
    double alennettu_hinta = hinta_per_yo * (1 - alennus);
    double kokonaishinta = alennettu_hinta * oiden_maara;

    // Lisätään siivousmaksu, jos yöpyminen on alle 3 yötä
    if (oiden_maara < 3) {
        if (huonetyyppi == "1hh") {
            siivousmaksu = 30;  // 1hh huoneelle siivousmaksu
        }
        else if (huonetyyppi == "2hh") {
            siivousmaksu = 50;  // 2hh huoneelle siivousmaksu
        }
        kokonaishinta += siivousmaksu;  // Lisätään siivousmaksu kokonaishintaan
    }
    else {
        siivousmaksu = 0;  // Ei siivousmaksua, jos yöt ovat 3 tai enemmän
    }

    return kokonaishinta;
}

void varaa_huone() {
    if (yhden_hengen_huoneet + kahden_hengen_huoneet == 0) {
        cout << "Ei vapaita huoneita!" << endl;
        system("cls");
        return;
    }

    cout << "\tMillä nimellä haluat tehdä varauksen?\t\t";
    string nimi;
    cin.ignore();
    getline(cin, nimi);

    cout << "\n\tValitse huonetyyppi (1hh tai 2hh):\t\t ";
    string huonetyyppi;
    cin >> huonetyyppi;

    if (huonetyyppi != "1hh" && huonetyyppi != "2hh") {
        cout << "\nVirheellinen huonetyyppi! Meiltä löytyy vain maksimissaan \nkahden hengen huoneita.";
        cout << " Kokeile uudestaan. Muistithan myös \n3kirjoittaa numeron perään hh ? \n" << endl;
        return;//Ohjeistuksia mahdollisten virheiden varalta
    }

    cout << "\n\tAnna yöt, enintään 10 yötä: \t\t\t";
    int oiden_maara;
    cin >> oiden_maara;

    system("cls");

    if (oiden_maara < 1 || oiden_maara > 10) {
        cout << "\nVirheellinen öiden määrä! Et voi valitettavasti varata kuin korkeintaan 10 yötä kerrallaan.\n" << endl;
        return;
    }

    int huone_numero = 0;
    bool huone_vapaa = false;

    // Etsitään vapaa huone
    if (huonetyyppi == "1hh" && yhden_hengen_huoneet > 0) {
        huone_vapaa = true;
        huone_numero = rand() % MAX_YHDEN_HENGEN_HUONEET + 1;
        if (!tarkista_huone_vapaa(huone_numero)) {
            huone_vapaa = false;
        }
    }
    else if (huonetyyppi == "2hh" && kahden_hengen_huoneet > 0) {
        huone_vapaa = true;
        huone_numero = rand() % MAX_KAHDEN_HENGEN_HUONEET + MAX_YHDEN_HENGEN_HUONEET + 1;
        if (!tarkista_huone_vapaa(huone_numero)) {
            huone_vapaa = false;
        }
    }

    if (!huone_vapaa) {
        cout << "Ei vapaita huoneita valitulle tyypille!" << endl;
        return;
    }

    // Alennus (0%, 10%, 20%) arpominen
    double alennus = (rand() % 3) * 0.10;  // Alennus 0%, 10%, 20%


    // Lasketaan kokonaishinta alennuksella ja mahdollisella siivousmaksulla

    double siivousmaksu = 0;
    double kokonaishinta = laske_hinta(huonetyyppi, oiden_maara, alennus, siivousmaksu);

    int varausnumero = arvo_varausnumero();
    varaukset.push_back({ varausnumero, nimi, huone_numero, false, huonetyyppi, oiden_maara, kokonaishinta, alennus });

    system("cls");

    cout << "\t\n\nVaraus onnistui!" << endl;
    cout << "\tVarausnumero:    " << varausnumero << endl;
    cout << "\tHuonetyyppi:     " << huonetyyppi << endl;
    cout << "\tHuoneen numero:  " << huone_numero << endl;
    cout << "\tÖiden määrä;     " << oiden_maara << endl;
    cout << "\tVaraajan nimi:   " << nimi << endl;
    cout << "\tKokonais hinta:  " << kokonaishinta << " euroa" << endl;
    //Varaus varmistus ja varaustiedot
    // Näytetään alennus vain, jos sitä on annettu
    if (alennus > 0) {
        cout << "\tSait alennuksen! Alennus: " << (alennus * 100) << "%\n\n" << endl;
    }

    // Näytetään siivousmaksu, jos se on lisätty
    if (siivousmaksu > 0) {
        cout << "\tSiivousmaksu: " << siivousmaksu << " euroa\n\n" << endl;
    }

    // Ilmainen siivous jos yöt ovat 3 tai enemmän
    if (oiden_maara >= 3) {
        cout << "\tOnneksi olkoon, ansaitset myös ilmaisen loppusiivouksen!\n\n" << endl;
    }
    cout << "Poistu takaisin valikkoon painamalla 'x' ja enter.\n";
    char valinta2;
    do {
        cin >> valinta2;
        if (valinta2 == 'x' || valinta2 == 'X') {
            system("cls");
            break;

        }
    } while (valinta2 != 'x' && valinta2 != 'X');
}

void hae_varaus() {
    cout << "\tAnna hakuehto (varausnumero tai varaajan nimi): ";
    string haku;
    cin.ignore();
    getline(cin, haku);

    bool loytyi = false;
    for (const auto& varaus : varaukset) {
        if (to_string(varaus.varausnumero) == haku || varaus.nimi == haku) {
            loytyi = true;

            cout << "\t\nVaraus löytyi!" << endl;
            cout << "\tVarausnumero:   " << varaus.varausnumero << endl;
            cout << "\tVaraajan nimi:  " << varaus.nimi << endl;
            cout << "\tHuoneen numero: " << varaus.huoneen_numero << endl;
            cout << "\tHuonetyyppi:    " << varaus.huoneen_koko << endl;
            cout << "\tÖiden määrä:    " << varaus.öiden_määrä << endl;
            cout << "Kokonais hinta: " << varaus.hinta << " euroa\n\n" << endl;

            // Näytetään alennus vain, jos sitä on annettu
            if (varaus.alennus > 0) {
                cout << "\tSisältää alennuksen: \t\t" << (varaus.alennus * 100) << "%\n" << endl;
            }

        }   cout << "Poistu takaisin valikkoon painamalla 'x' ja enter.\n";

        char valinta2;
        do {
            cin >> valinta2;
            if (valinta2 == 'x' || valinta2 == 'X') {
                system("cls");
                break;
            }
        } while (valinta2 != 'x' && valinta2 != 'X');
    }
    if (!loytyi) {
        cout << "\tVarauksia ei löytynyt." << endl;
    }

}

void selaa_ehtoja() {//Tein ylimääräisen esittely ja hinnastosivun. Ajattelin, että tää melkein näyttäisikin oikealta ammattimaiselta ohjelmalta.
    cout << "\n\nTervetuloa Paratiisi Tunturin hotelliin, jossa viihdyt varmasti useiden eri aktiviteettien parissa.\nTarjolla on mm. kiipeilyä, poroajeluita sekä nopeita kielikursseja.";
    cout << "\nHotellimme lomat ovat suunnattu pariskunnille tai ystävyksille ja siksi tarjoamme vain korkeintaan\nkahden hengen majoituksia. Tämä johtuu yksin omaan siitä, että";
    cout << "\nkenellä tahansa on mahdollisuus päästä irtiottoon arjesta kauemmaksi kotoa ja saada pientä välimatkaa\nmuihin kanssa eläviin. Toivomme saavamme palautetta vierailustanne.";
    cout << "\nHuonesiivous kuuluu hotelliyöpymisen hintaa, jos viivytte vähintään 3 yötä.\n";

    cout << "Alla näette hinnastomme ja palvelumme. Huom! Aktiviteettipalvelut varataan puhelimitse tai paikan päällä.\n\n";
    cout << "\tHinnasto\n";
    cout << "\t\tYöpyminen\n";
    cout << "\t\t\tYhden hengen huoneessa (1hh) \t\t 100e/per yö\n";
    cout << "\t\t\tKahden hengen huoneessa (2hh) \t\t 150e/per yö\n\n";
    cout << "\t\tSiivouspalvelut\n";
    cout << "\t\t\t 1hh Huoneet\t\t 30e\n";
    cout << "\t\t\t 2hh Huoneet\t\t 50e\n";
    cout << "\t\t\tYöpyessäsi enemmän kuin 3 yötä siivouspalvelu kuuluu hintaan!\n\n";

    cout << "\tTervetuloa meille!\n\n";
    cout << "Poistu takaisin valikkoon painamalla 'x' ja enter.\n";
    char valinta;
    do {
        cin >> valinta;
        if (valinta == 'x' || valinta == 'X') {
            system("cls");
            break;
        }
    } while (valinta != 'x' && valinta != 'X');
}

void tulosta_valikko() {//Valikko tai ns. menu josta aloitetaan
    cout << "\n\nTervetuloa Paratiisi Tunturin Hotellihuoneen varaukseen!\n";
    cout << "\nValitse alla olevista palveluista:\n\n";
    cout << "\t/1. Varaa huone" << endl;
    cout << "\t/2. Hae varaus" << endl;
    cout << "\t/3. Selaa hotellin tietoja ja hinnastoa" << endl;
    cout << "\t/4. Poistu" << endl;
}

int main() {
    srand(time(0));  // Alustetaan satunnaislukugeneraattori
    setlocale(LC_ALL, "FI_fi");  // Varmistetaan, että Ä ja Ö näkyvät oikein

    int valinta;
    do {
        tulosta_valikko();
        cout << "\n\n\tValitse toiminto numerona ja paina enter: ";
        cin >> valinta;
        cout << "\n";
        //Menun neljä vaihtoehtoa joihin voidaan siirtyä
        switch (valinta) {
        case 1:
            varaa_huone();
            break;
            system("cls");
        case 2:
            hae_varaus();
            break;
            system("cls");
        case 3:
            selaa_ehtoja();
            break;
        case 4:
            cout << "Ohjelma sulkeutuu. Paina mitä vaan nappia." << endl;
            break;
        default:
            cout << "Virheellinen valinta! Valitse valikon tarjoamista numeroista." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.clear();
        }


    } while (valinta != 4);
    system("cls");

    return 0;
}
