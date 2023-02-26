#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

struct Uzytkownik
{
    int id;
    string login, haslo;
};

string wczytaj_linie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytaj_znak()
{
    string wejscie = "";
    char znak  = {0};

    while (true)
    {
        getline(cin, wejscie);
        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

inline bool exists_test1 (const string& name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
        return false;
}

void wpisanie_do_struktury_uzytkownicy(vector<Uzytkownik>& uzytkownicy)
{
    string linia;
    fstream plik;
    string nazwa = "Loginy i hasla.txt";
    Uzytkownik osoba;
    int id;

    if (exists_test1(nazwa) == true)
    {
        plik.open("Loginy i hasla.txt", ios::in);
        while (getline(plik, linia))
        {
            int dlugosc = linia.length();
            int ilosc_znaku_rozdzielajacego = 0;
            int pozycja_ostatniego_znaku = 0;
            for (int i = 0; i < dlugosc; i++)
            {
                if (linia[i] == 124)
                {
                    if (ilosc_znaku_rozdzielajacego == 0)
                    {
                        string nowy_napis = linia.substr(0, i);
                        osoba.id = stoi(nowy_napis);
                    }
                    else if (ilosc_znaku_rozdzielajacego == 1)
                        osoba.login = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 2)
                        osoba.haslo = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    ilosc_znaku_rozdzielajacego = ilosc_znaku_rozdzielajacego + 1;
                    pozycja_ostatniego_znaku = i + 1;
                }
            }
            uzytkownicy.push_back(osoba);
        }
        plik.close();
        return;
    }
    else
        return;
}

void zapis_nowego_adresata(vector<Uzytkownik> uzytkownicy)
{
    fstream plik;

    plik.open("Loginy i hasla.txt", ios::out);
    for (unsigned int j = 0; j < uzytkownicy.size(); j++)
    {
        plik << uzytkownicy[j].id << "|";
        plik << uzytkownicy[j].login << "|";
        plik << uzytkownicy[j].haslo << "|" << endl;
    }
    plik.close();
}

void dodaj_uzytkownika(vector<Uzytkownik>& uzytkownicy)
{
    string login, haslo;
    int id = 0;
    fstream plik;
    string nazwa = "Loginy i hasla.txt";

    cout << endl << "Podaj login: ";
    login= wczytaj_linie();
    cout << "Podaj haslo: ";
    haslo = wczytaj_linie();

    if (exists_test1(nazwa) == true)
    {
        if (uzytkownicy.empty())
        {
            id = 1;
            uzytkownicy.push_back({id, login, haslo});
            zapis_nowego_adresata(uzytkownicy);
        }
        else
        {
            id = uzytkownicy.back().id + 1;
            uzytkownicy.push_back({id, login, haslo});
            zapis_nowego_adresata(uzytkownicy);
        }
    }
    else
    {
        id = 1;
        uzytkownicy.push_back({id, login, haslo});
        zapis_nowego_adresata(uzytkownicy);
    }

    cout << endl << "Utworzono konto" << endl << " " << endl;
    system("pause");
    return;
}

struct Osoba
{
    int id, id_uzytkownika;
    string imie, nazwisko, numer_telefonu, email, adres;
};

void wpisanie_do_struktury_adresaci(vector<Osoba>& adresaci,int ilosc_przeszukanych_osob)
{
    string linia;
    fstream plik;
    string nazwa = "KsiazkaAdresowaw3.txt";
    Osoba osoba;
    int id, id_uzytkownika;

    if (exists_test1(nazwa) == true)
    {
        plik.open("KsiazkaAdresowaw3.txt", ios::in);
        while (getline(plik, linia))
        {
            int dlugosc = linia.length();
            int ilosc_znaku_rozdzielajacego = 0;
            int pozycja_ostatniego_znaku = 0;
            for (int i = 0; i < dlugosc; i++)
            {
                if (linia[i] == 124)
                {
                    if (ilosc_znaku_rozdzielajacego == 0)
                    {
                        string nowy_napis = linia.substr(0, i);
                        osoba.id = stoi(nowy_napis);
                    }
                    else if (ilosc_znaku_rozdzielajacego == 1)
                    {
                        string nowy_napis = linia.substr(pozycja_ostatniego_znaku,  i - pozycja_ostatniego_znaku);
                        osoba.id_uzytkownika = stoi(nowy_napis);
                    }
                    else if (ilosc_znaku_rozdzielajacego == 2)
                        osoba.imie = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 3)
                        osoba.nazwisko = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 4)
                        osoba.numer_telefonu = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 5)
                        osoba.email = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 6)
                        osoba.adres = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    ilosc_znaku_rozdzielajacego = ilosc_znaku_rozdzielajacego + 1;
                    pozycja_ostatniego_znaku = i + 1;
                }
            }
            if (osoba.id_uzytkownika == ilosc_przeszukanych_osob)
                adresaci.push_back(osoba);
        }
        plik.close();
        return;
    }
    else
        return;
}

int ilosc_lini_w_pliku()
{
    string linia;
    int count = 0;
    ifstream plik("KsiazkaAdresowaw3.txt");

    while(getline(plik, linia))
        count++;
    return count;
}

int numer_lini_z_id(string nazwa_pliku, int numer)
{
    int nr_lini, id;
    ifstream plik;
    string linia;
    int numer_lini_w_pliku = 1;
    plik.open(nazwa_pliku, ios::in);
    while (getline(plik, linia))
    {
        int dlugosc = linia.length();
        int ilosc_znaku_rozdzielajacego = 0;
        for (int i = 0; i < dlugosc; i++)
        {
            if (linia[i] == 124)
            {
                if (ilosc_znaku_rozdzielajacego == 0)
                {
                    string nowy_napis = linia.substr(0, i);
                    id = stoi(nowy_napis);
                    if (id == numer)
                        nr_lini = numer_lini_w_pliku;
                    ilosc_znaku_rozdzielajacego = ilosc_znaku_rozdzielajacego + 1;
                }
            }
        }
        ilosc_znaku_rozdzielajacego = 0;
        numer_lini_w_pliku += 1;
    }
    return nr_lini;
}

void zapis_do_pliku_po_edycji (vector<Osoba>& adresaci, int numer_indeksu_adresata, int numer, string czynnosc)
{
    string linia;
    ifstream plik;
    ofstream temp;
    string nazwa_pliku = "KsiazkaAdresowaw3.txt";

    int numer_lini_w_txt=1;

    plik.open(nazwa_pliku);
    temp.open("temp.txt");
    while (getline(plik, linia))
    {
        if ( numer_lini_w_txt != numer_lini_z_id(nazwa_pliku,numer) && czynnosc == "u")
            temp << linia << endl;
        else if ( numer_lini_w_txt != numer_lini_z_id(nazwa_pliku, numer) && czynnosc == "e")
            temp << linia << endl;
        else if (numer_lini_w_txt == numer_lini_z_id(nazwa_pliku, numer) && czynnosc == "e")
        {
            temp << adresaci[numer_indeksu_adresata].id << "|";
            temp << adresaci[numer_indeksu_adresata].id_uzytkownika << "|";
            temp << adresaci[numer_indeksu_adresata].imie << "|";
            temp << adresaci[numer_indeksu_adresata].nazwisko << "|";
            temp << adresaci[numer_indeksu_adresata].numer_telefonu << "|";
            temp << adresaci[numer_indeksu_adresata].email << "|";
            temp << adresaci[numer_indeksu_adresata].adres << "|" << endl;
        }
        numer_lini_w_txt++;
    }
    plik.close();
    temp.close();
    remove("KsiazkaAdresowaw3.txt");
    rename("temp.txt", "KsiazkaAdresowaw3.txt");
}

void dodaj_osobe(vector<Osoba> adresaci)
{
    fstream plik;
    int ilosc_osob_w_wektorze;

    plik.open("KsiazkaAdresowaw3.txt", ios::out | ios::app);
    ilosc_osob_w_wektorze= adresaci.size() - 1;
    plik << adresaci[ilosc_osob_w_wektorze].id << "|";
    plik << adresaci[ilosc_osob_w_wektorze].id_uzytkownika << "|";
    plik << adresaci[ilosc_osob_w_wektorze].imie << "|";
    plik << adresaci[ilosc_osob_w_wektorze].nazwisko << "|";
    plik << adresaci[ilosc_osob_w_wektorze].numer_telefonu << "|";
    plik << adresaci[ilosc_osob_w_wektorze].email << "|";
    plik << adresaci[ilosc_osob_w_wektorze].adres << "|" << endl;
    plik.close();
}

int jaki_plik()
{
    string linia;
    fstream plik;
    string nazwa = "KsiazkaAdresowaw3.txt";
    int id = 1;

    if (exists_test1(nazwa) == true)
    {
        plik.open("KsiazkaAdresowaw3.txt", ios::in);
        while (getline(plik, linia))
        {
            int dlugosc = linia.length();
            int ilosc_znaku_rozdzielajacego = 0;
            for (int i = 0; i < dlugosc; i++)
            {
                if (linia[i] == 124)
                {
                    if (ilosc_znaku_rozdzielajacego == 0)
                    {
                        string nowy_napis = linia.substr(0, i);
                        id = stoi(nowy_napis);
                    }
                }
            }
        }
        plik.close();
        return id;
    }
    else
        return id;
}

bool czy_plik_pusty()
{
    fstream plik;
    bool pusty_plik;
    string linia;
    plik.open("KsiazkaAdresowaw3.txt", ios::in);
    while(!linia.empty())
        pusty_plik = true;
    return pusty_plik;
}

void dodaj_adresata(vector<Osoba>& adresaci, int id_uzytkownika)
{
    string imie, nazwisko, numer_telefonu, email, adres;
    int id = 0;
    fstream plik;
    string nazwa = "KsiazkaAdresowaw3.txt";

    cout << endl << "Podaj imie: ";
    imie = wczytaj_linie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytaj_linie();
    cout << "Podaj numer telefonu: ";
    numer_telefonu = wczytaj_linie();
    cout << "Podaj email: ";
    email = wczytaj_linie();
    cout << "Podaj adres: ";
    adres = wczytaj_linie();

    if (exists_test1(nazwa) == true)
    {
        if (czy_plik_pusty() == true)
        {
            id = 1;
            adresaci.push_back({id, id_uzytkownika, imie, nazwisko, numer_telefonu, email, adres});
            dodaj_osobe(adresaci);
        }
        else
        {

            id = jaki_plik() + 1;
            adresaci.push_back({id, id_uzytkownika, imie, nazwisko, numer_telefonu, email, adres});
            dodaj_osobe(adresaci);
        }
    }
    else
    {
        id = 1;
        adresaci.push_back({id, id_uzytkownika, imie, nazwisko, numer_telefonu, email, adres});
        dodaj_osobe(adresaci);
    }

    cout << endl << "Osoba zostala dodana" << endl;
    cout << " " << endl;
    system("pause");
    return;
}

void wyszukaj_po_imieniu(vector<Osoba>& adresaci)
{
    string imie;
    int ilosc_przeszukanych_osob = 0;

    cout << endl << "Podaj imie osoby jaka ma byc wyszukana: ";
    imie = wczytaj_linie();

    for (int i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].imie == imie)
        {
            cout << endl;
            cout << "ID: " <<  adresaci[i].id << endl;
            cout <<  adresaci[i].imie << " " <<  adresaci[i].nazwisko << endl;
            cout << "Telefon: " << adresaci[i].numer_telefonu << endl;
            cout << "Email: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl;
            cout << endl;
        }
        else
            ilosc_przeszukanych_osob++;
    }

    if (ilosc_przeszukanych_osob == adresaci.size() && adresaci.back().imie != imie)
        cout << endl << "Nie ma osoby o takim imieniu na liscie kontaktowej" << endl << " " << endl;

    system("pause");
}

void wyszukaj_po_nazwisku(vector<Osoba>& adresaci)
{
    string nazwisko;
    int ilosc_przeszukanych_osob = 0;

    cout << endl << "Podaj nazwisko osoby jaka ma byc wyszukana: ";
    nazwisko = wczytaj_linie();

    for (int i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].nazwisko == nazwisko)
        {
            cout << endl;
            cout << "ID: " <<  adresaci[i].id << endl;
            cout <<  adresaci[i].imie << " " <<  adresaci[i].nazwisko << endl;
            cout << "Telefon: " << adresaci[i].numer_telefonu << endl;
            cout << "Email: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].adres << endl;
            cout << endl;
        }
        else
            ilosc_przeszukanych_osob++;
    }

    if (ilosc_przeszukanych_osob == adresaci.size() && adresaci.back().nazwisko != nazwisko)
        cout << endl <<"Nie ma osoby o takim nazwisku na liscie kontaktowej" << endl << " " << endl;

    system("pause");
}

void wyswietl_wszystkie_osoby(vector<Osoba> adresaci)
{
    for (int i = 0; i < adresaci.size(); i++)
    {
        cout << endl;
        cout << "ID: " <<  adresaci[i].id << endl;
        cout <<  adresaci[i].imie << " " <<  adresaci[i].nazwisko << endl;
        cout << "Telefon: " << adresaci[i].numer_telefonu << endl;
        cout << "Email: " << adresaci[i].email << endl;
        cout << "Adres: " << adresaci[i].adres << endl;
        cout << endl;
    }

    system("pause");
}

void usun_osoby(vector<Osoba>& adresaci)
{
    string line;
    int numer;
    int nr_lini = 0;
    char znak;
    fstream plik;
    vector <Osoba>::iterator it;

    cout << endl << "Prosze wprowadz numer id adresata, ktory chcesz usunac: ";
    cin >> numer;
    cin.sync();
    cout << "Czy jestes pewien, ze chcesz usnac ta osobe o numerze id: " << numer << " Jesli tak wcisnij klawisz t: ";
    cin >> znak;
    cin.sync();
    string czynnosc = "u";

    if (znak == 't')
    {
        for (int i = 0; i < adresaci.size(); i++)
        {
            if (adresaci[i].id == numer)
            {
                nr_lini = i + 1;
                it = adresaci.begin() + nr_lini - 1;
                adresaci.erase(it);
                zapis_do_pliku_po_edycji(adresaci, nr_lini, numer, czynnosc);
                cout << "Kontakt o numerze ID " << numer << " zostal usuniety" << endl;
                system("pause");
                return;
            }
        }
        cout << endl << "Nie ma osoby o takim ID na liscie kontaktowej" << endl << " " <<endl;
        system("pause");
        return;
    }
    else
        return;
}

void edytuj_adresata(vector<Osoba>& adresaci)
{
    int wybor, numer;
    int nr_lini = 0;
    int i = 0;
    string imie, nazwisko, numer_telefonu, email, adres;
    string czynnosc = "e";

    cout << endl << "Prosze wprowadz numer id adresata, ktory chcesz edytowac: ";
    cin >> numer;
    cin.ignore();

    for (i; i < adresaci.size(); i++)
    {
        if(adresaci[i].id == numer)
        {
            nr_lini = i + 1;
            break;
        }
    }

    if (adresaci[i].id != numer)
    {
        cout << endl << "Nie ma osoby o takim numerze ID w liscie kontaktowej" << endl << " " << endl;
        system("pause");
        return;
    }
    system("cls");
    cout << "1. imie" << endl;
    cout << "2. nazwisko" << endl;
    cout << "3. numer telefonu" << endl;
    cout << "4. email" << endl;
    cout << "5. adres" <<endl;
    cout << "6. powrot do menu" <<endl;

    cout << endl << "Prosze wprowadz numer elementu z ksiazki adresowej, ktory chcesz edytowac: ";
    wybor = wczytaj_znak();

    switch (wybor)
    {
    case '1':
    {
        cout << endl << "Podaj jakie imie zapisac dla kontaktu o ID " << numer << ": ";
        imie = wczytaj_linie();
        adresaci[nr_lini - 1].imie = imie;
        zapis_do_pliku_po_edycji(adresaci, nr_lini-1, numer, czynnosc);
        cout << "Zmiana zostala zapisana." << endl;
        system("pause");
        break;
    }
    case '2':
    {
        cout << endl << "Podaj jakie nazwisko zapisac dla kontaktu o ID " << numer << ": ";
        nazwisko = wczytaj_linie();
        adresaci[nr_lini - 1].nazwisko = nazwisko;
        zapis_do_pliku_po_edycji(adresaci, nr_lini-1, numer, czynnosc);
        cout << "Zmiana zostala zapisana." << endl;
        system("pause");
        break;
    }
    case '3':
    {
        cout << endl << "Podaj jaki numer telefonu zapisac dla kontaktu o ID " << numer << ": ";
        numer_telefonu = wczytaj_linie();
        adresaci[nr_lini - 1].numer_telefonu = numer_telefonu;
        zapis_do_pliku_po_edycji(adresaci, nr_lini-1, numer, czynnosc);
        cout << "Zmiana zostala zapisana." << endl;
        system("pause");
        break;
    }
    case '4':
    {
        cout << endl << "Podaj jaki email zapisac dla kontaktu o ID " << numer << ": ";
        email = wczytaj_linie();
        adresaci[nr_lini - 1].email = email;
        zapis_do_pliku_po_edycji(adresaci, nr_lini-1, numer, czynnosc);
        cout << "Zmiana zostala zapisana." << endl;
        system("pause");
        break;
    }
    case '5':
    {
        cout << endl << "Podaj jaki adres zapisac dla kontaktu o ID " << numer << ": ";
        adres = wczytaj_linie();
        adresaci[nr_lini - 1].adres = adres;
        zapis_do_pliku_po_edycji(adresaci, nr_lini-1, numer, czynnosc);
        cout << "Zmiana zostala zapisana." << endl;
        system("pause");
        break;
    }
    case '6':
    {
        break;
    }
    }
}

void zapis_do_pliku_po_zmianie_hasla(vector<Uzytkownik>& uzytkownicy, int ilosc_przeszukanych_osob)
{
    string linia;
    ifstream plik;
    ofstream temp;
    plik.open("Loginy i hasla.txt");
    temp.open("temp1.txt");
    int numer_lini_w_txt=1;

    while (getline(plik, linia))
    {
        if (numer_lini_w_txt != ilosc_przeszukanych_osob+1)
            temp << linia << endl;
        else if (numer_lini_w_txt == ilosc_przeszukanych_osob+1)
        {
            temp << uzytkownicy[ilosc_przeszukanych_osob].id << "|";
            temp << uzytkownicy[ilosc_przeszukanych_osob].login << "|";
            temp << uzytkownicy[ilosc_przeszukanych_osob].haslo << "|"<<endl;
        }
        numer_lini_w_txt++;
    }
    plik.close();
    temp.close();
    remove("Loginy i hasla.txt");
    rename("temp1.txt", "Loginy i hasla.txt");
    cout<<"Haslo zostalo zmienione."<<endl;
    system("pause");
}

int ksiazka_adresowa(vector<Uzytkownik>& uzytkownicy, int id_uzytkownika, int ilosc_przeszukanych_osob)
{
    vector<Osoba> adresaci;
    char wybor;

    wpisanie_do_struktury_adresaci(adresaci, id_uzytkownika);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "5. Usun adresata" <<endl;
        cout << "6. Edytuj adresata" <<endl;
        cout << "7. Zmien haslo" <<endl;
        cout << "8. Wyloguj" << endl;
        cout << endl << "Wprowadz numer opcji, ktora chcesz wybrac: ";
        wybor = wczytaj_znak();

        switch (wybor)
        {
        case '1':
        {
            dodaj_adresata(adresaci, id_uzytkownika);
            break;
        }
        case '2':
        {
            if (adresaci.size() == 0)
            {
                cout << endl << "Ksiazka adresowa jest pusta." << endl << " " <<endl;
                system("pause");
            }
            else
                wyszukaj_po_imieniu(adresaci);
            break;
        }
        case '3':
        {
            if (adresaci.size() == 0)
            {
                cout << endl << "Ksiazka adresowa jest pusta." << endl << " " <<endl;
                system("pause");
            }
            else
                wyszukaj_po_nazwisku(adresaci);
            break;
        }
        case '4':
        {
            if (adresaci.size() == 0)
            {
                cout << endl << "Ksiazka adresowa jest pusta." << endl << " " <<endl;
                system("pause");
            }
            else
                wyswietl_wszystkie_osoby(adresaci);
            break;
        }
        case '5':
        {
            if (adresaci.size() == 0)
            {
                cout << endl << "Nie ma osob w ksiazce kontaktowej. Nie ma co usunac." << endl << " " << endl;
                system("pause");
            }
            else
                usun_osoby(adresaci);
            break;
        }
        case '6':
        {
            if (adresaci.size() == 0)
            {
                cout << endl << "Nie ma osob w ksiazce kontaktowej. Nie ma co edytowac." << " " << endl;
                system("pause");
            }
            else
                edytuj_adresata(adresaci);
            break;
        }
        case '7':
        {
            string haslo;
            string nazwa_pliku = "Loginy i hasla.txt";
            cout << "Podaj nowe haslo: ";
            haslo = wczytaj_linie();
            uzytkownicy[ilosc_przeszukanych_osob].haslo = haslo;
            zapis_do_pliku_po_zmianie_hasla(uzytkownicy, ilosc_przeszukanych_osob);
            break;
        }
        case '8':
        {
            return 0;
        }
        }
    }
    return 0;
}

void logowanie(vector<Uzytkownik>& uzytkownicy)
{
    string login, haslo;
    cout << endl << "Podaj swoj login: ";
    login = wczytaj_linie();
    cout <<"Podaj swoje haslo: ";
    haslo = wczytaj_linie();
    int ilosc_przeszukanych_osob = 0;
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].login == login)
            break;
        else
            ilosc_przeszukanych_osob++;
    }

    if (uzytkownicy[ilosc_przeszukanych_osob].login == login && uzytkownicy[ilosc_przeszukanych_osob].haslo == haslo)
        ksiazka_adresowa(uzytkownicy, uzytkownicy[ilosc_przeszukanych_osob].id, ilosc_przeszukanych_osob);
    else
        cout<<"Niepoprawny login lub haslo"<<endl;
    system("pause");
    return;
}

int main()
{
    vector<Uzytkownik> uzytkownicy;
    char wybor;
    string login, haslo;
    string nazwa = "Loginy i hasla.txt";

    wpisanie_do_struktury_uzytkownicy(uzytkownicy);

    while (true)
    {
        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program " << endl;
        cout << endl << "Wprowadz numer opcji, ktora chcesz wybrac: ";
        wybor = wczytaj_znak();

        switch (wybor)
        {
        case '1':
        {
            if (exists_test1(nazwa) == false)
                cout<<"Nie ma zadnego uzytkownika. Zarejestruj sie, aby uzyc aplikacji."<<endl;
            else
                logowanie(uzytkownicy);
            system("pause");
            break;
        }
        case '2':
        {
            dodaj_uzytkownika(uzytkownicy);
            break;
        }
        case '3':
        {
            exit(0);
        }
        }
    }
    return 0;
}
