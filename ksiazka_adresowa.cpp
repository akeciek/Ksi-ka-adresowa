#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

struct Osoba
{
    int id;
    string imie, nazwisko, numer_telefonu, email, adres;
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
    {
        return false;
    }
}

void wpisanie_do_struktury (vector<Osoba>& adresaci)
{
    string linia;
    fstream plik;
    string nazwa = "KsiazkaAdresowaw3.txt";
    Osoba osoba;
    int id;
    int nr_lini = 0;

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
                        osoba.imie = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 2)
                        osoba.nazwisko = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 3)
                        osoba.numer_telefonu = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 4)
                        osoba.email = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    else if (ilosc_znaku_rozdzielajacego == 5)
                        osoba.adres = linia.substr(pozycja_ostatniego_znaku, i - pozycja_ostatniego_znaku);
                    ilosc_znaku_rozdzielajacego = ilosc_znaku_rozdzielajacego + 1;
                    pozycja_ostatniego_znaku = i + 1;
                }
            }
            adresaci.push_back(osoba);
            nr_lini++;
        }
        plik.close();
        return;
    }
    else
    {
        return;
    }
}

void zapis_do_pliku_po_edycji (vector<Osoba> adresaci)
{
    fstream plik;

    plik.open("KsiazkaAdresowaw3.txt", ios::out);
    for (unsigned int j = 0; j < adresaci.size(); j++)
    {
        plik << adresaci[j].id;
        plik << "|";
        plik << adresaci[j].imie;
        plik << "|";
        plik << adresaci[j].nazwisko;
        plik << "|";
        plik << adresaci[j].numer_telefonu;
        plik << "|";
        plik << adresaci[j].email;
        plik << "|";
        plik << adresaci[j].adres;
        plik << "|";
        plik << endl;
    }
    plik.close();
}

void dodaj_osobe(vector<Osoba>& adresaci)
{
    string imie, nazwisko, numer_telefonu, email, adres;
    int id = 0;
    fstream plik;
    string nazwa = "KsiazkaAdresowaw3.txt";

    cout << "Podaj imie: ";
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
        if (adresaci.empty())
        {
            id = 1;
            adresaci.push_back({id, imie, nazwisko, numer_telefonu, email, adres});
            zapis_do_pliku_po_edycji(adresaci);
        }
        else
        {
            id = adresaci.back().id + 1;
            adresaci.push_back({id, imie, nazwisko, numer_telefonu, email, adres});
            zapis_do_pliku_po_edycji(adresaci);
        }
    }
    else
    {
        id = 1;
        adresaci.push_back({id, imie, nazwisko, numer_telefonu, email, adres});
        zapis_do_pliku_po_edycji(adresaci);
    }

    cout << endl << "Osoba zostala dodana" << endl;
    system("pause");
    return;
}

void wyszukaj_po_imieniu(vector<Osoba>& adresaci)
{
    string imie;
    int ilosc_przeszukanych_osob = 0;

    cout << "Podaj imie osoby jaka ma byæ wyszukana: ";
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
        cout << "Nie ma osoby o takim imieniu na liscie kontaktowej" << endl;

    system("pause");
}

void wyszukaj_po_nazwisku(vector<Osoba>& adresaci)
{
    string nazwisko;
    int ilosc_przeszukanych_osob = 0;

    cout << "Podaj nazwisko osoby jaka ma byæ wyszukana: ";
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
        cout << "Nie ma osoby o takim nazwisku na liscie kontaktowej" << endl;

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

    cout << "Prosze wprowadz numer id adresata, ktory chcesz usunac: ";
    cin >> numer;
    cin.sync();
    cout << "Czy jestes pewien, ze chcesz usnac ta osobe o numerze id: " << numer << " Jesli tak wcisnij klawisz t: ";
    cin >> znak;
    cin.sync();

    if (znak == 't')
    {
        for (int i = 0; i < adresaci.size(); i++)
        {
            if (adresaci[i].id == numer)
            {
                nr_lini = i + 1;
                it = adresaci.begin() + nr_lini - 1;
                adresaci.erase(it);
                zapis_do_pliku_po_edycji(adresaci);
                cout << "Kontakt o numerze ID " << numer << " zostal usuniety" << endl;
                system("pause");
                return;
            }
        }
        cout << "Nie ma osoby o takim ID na liscie kontaktowej" << endl;
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

    cout << "Prosze wprowadz numer id adresata, ktory chcesz edytowac: ";
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
        cout << "Nie ma osoby o takim numerze ID w liscie kontaktowej" << endl;
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

    cout << "Prosze wprowadz numer elementu z ksiazki adresowej, ktory chcesz edytowac: ";
    wybor = wczytaj_znak();

    switch (wybor)
    {
    case '1':
    {
        cout << "Podaj jakie imie zapisac dla kontaktu o ID " << numer << ": ";
        imie = wczytaj_linie();
        adresaci[nr_lini - 1].imie = imie;
        zapis_do_pliku_po_edycji(adresaci);
        cout << "zmiana zapisana" << endl;
        system("pause");
        break;
    }
    case '2':
    {
        cout << "Podaj jakie nazwisko zapisac dla kontaktu o ID " << numer << ": ";
        nazwisko = wczytaj_linie();
        adresaci[nr_lini - 1].nazwisko = nazwisko;
        zapis_do_pliku_po_edycji(adresaci);
        cout << "zmiana zapisana" << endl;
        system("pause");
        break;
    }
    case '3':
    {
        cout << "Podaj jaki numer telefonu zapisac dla kontaktu o ID " << numer << ": ";
        numer_telefonu = wczytaj_linie();
        adresaci[nr_lini - 1].numer_telefonu = numer_telefonu;
        zapis_do_pliku_po_edycji(adresaci);
        cout << "zmiana zapisana" << endl;
        system("pause");
        break;
    }
    case '4':
    {
        cout << "Podaj jaki email zapisac dla kontaktu o ID " << numer << ": ";
        email = wczytaj_linie();
        adresaci[nr_lini - 1].email = email;
        zapis_do_pliku_po_edycji(adresaci);
        cout << "zmiana zapisana" << endl;
        system("pause");
        break;
    }
    case '5':
    {
        cout << "Podaj jaki adres zapisac dla kontaktu o ID " << numer << ": ";
        adres = wczytaj_linie();
        adresaci[nr_lini - 1].adres = adres;
        zapis_do_pliku_po_edycji(adresaci);
        cout << "zmiana zapisana" << endl;
        system("pause");
        break;
    }
    case '6':
    {
        break;
    }
    }
}

int main()
{
    vector<Osoba> adresaci;
    char wybor;

    wpisanie_do_struktury(adresaci);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "5. Usun adresata" <<endl;
        cout << "6. Edytuj adresata" <<endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Wprowadz numer opcji, ktora chcesz wybrac: ";
        wybor = wczytaj_znak();

        switch (wybor)
        {
        case '1':
        {
            dodaj_osobe(adresaci);
            break;
        }
        case '2':
        {
            if (adresaci.size() == 0)
            {
                cout << "Ksiazka adresowa jest pusta." << endl;
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
                cout << "Ksiazka adresowa jest pusta." << endl;
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
                cout << "Ksiazka adresowa jest pusta." << endl;
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
                cout << "Nie ma osob w ksiazce kontaktowej. Nie ma co usunac." << endl;
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
                cout << "Nie ma osob w ksiazce kontaktowej. Nie ma co edytowac." << endl;
                system("pause");
            }
            else
                edytuj_adresata(adresaci);
            break;
        }
        case '9':
        {
            exit(0);
        }
        }
    }
    return 0;
}
