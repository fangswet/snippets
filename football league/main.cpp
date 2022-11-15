#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <stdlib.h>

using namespace std;

enum Pozycja
{
    Bramka, Obrona, Pomoc, Atak
};

class Zawodnik
{
private:
    string _imie;
    string _nazwisko;
    Pozycja _pozycja;
    int _numer;

public:
    Zawodnik(string imie, string nazwisko, Pozycja pozycja, int numer)
    {
        this->_imie = imie;
        this->_nazwisko = nazwisko;
        this->_pozycja = pozycja;
        this->_numer = numer;
    }

    string imie()
    {
        return this->_imie;
    }

    string nazwisko()
    {
        return this->_nazwisko;
    }

    string nazwa_pozycji()
    {
        switch (this->_pozycja)
        {
        case Pozycja::Atak:
            return "atak";
        case Pozycja::Obrona:
            return "obrona";
        case Pozycja::Bramka:
            return "bramka";
        case Pozycja::Pomoc:
            return "pomoc";
        }
    }
    
    Pozycja pozycja()
    {
        return this->_pozycja;
    }

    int numer()
    {
        return this->_numer;
    }
};

class Klub
{
private:
    string _nazwa;
    string _kolor;
    Zawodnik* _zawodnicy[5];
    int _liczba_zawodnikow;

public:
    Klub(string nazwa, string kolor)
    {
        this->_nazwa = nazwa;
        this->_kolor = kolor;
        this->_liczba_zawodnikow = 0;
    }

    string nazwa()
    {
        return this->_nazwa;
    }

    string kolor()
    {
        return this->_kolor;
    }
    
    int liczba_zawodnikow()
    {
        return this->_liczba_zawodnikow;
    }
    
    void dodaj_zawodnika(Zawodnik* zawodnik)
    {
        auto i = this->_liczba_zawodnikow >= 5 ? this->_liczba_zawodnikow - 1 : this->_liczba_zawodnikow++;
        this->_zawodnicy[i] = zawodnik;
    }
    
    string zawodnicy()
    {
        auto zawodnicy = string();
        for (int i = 0; i < this->_liczba_zawodnikow; i++)
        {
            auto zawodnik = this->_zawodnicy[i];
            zawodnicy += zawodnik->imie() + " " + zawodnik->nazwisko() + " ";
            zawodnicy += to_string(zawodnik->numer()) + " ";
            zawodnicy += zawodnik->nazwa_pozycji() + "\n";
        }
        
        return zawodnicy;
    }
    
    int znajdz_zawodnika(Zawodnik* zawodnik)
    {
        for (int i = 0; i < this->_liczba_zawodnikow; i++)
        {
            if (zawodnik == this->_zawodnicy[i])
            {
                return i;
            }
        }
        
        return -1;
    }
    
    void usun_zawodnika(Zawodnik* zawodnik)
    {
        auto i = this->znajdz_zawodnika(zawodnik);
        if (i > 0)
        {
            for (; i < this->_liczba_zawodnikow - 1; i++)
            {
                this->_zawodnicy[i] = this->_zawodnicy[i + 1];
            }
            
            this->_liczba_zawodnikow--;
        }
    }
    
    void transferuj_zawodnika(Zawodnik* zawodnik, Klub* klub)
    {
        if (this->znajdz_zawodnika(zawodnik) > 0)
        {
            this->usun_zawodnika(zawodnik);
            klub->usun_zawodnika(zawodnik);
            klub->dodaj_zawodnika(zawodnik); 
        }
    }
    
    Zawodnik* losuj_zawodnika(Pozycja pozycja)
    {
        if (this->_liczba_zawodnikow < 1) return NULL;
        vector<Zawodnik*> zawodnicy = {};
        
        for (int i = 0; i < this->_liczba_zawodnikow; i++)
        {
            if (this->_zawodnicy[i]->pozycja() == pozycja)
            {
                zawodnicy.push_back(this->_zawodnicy[i]);
            }
        }
        
        return zawodnicy.empty() ? this->_zawodnicy[rand() % this->_liczba_zawodnikow] : zawodnicy.at(rand() % zawodnicy.size());
    }
};

class Mecz
{
private:
    Klub* _gospodarz;
    Klub* _gosc;
    int wynik_gospodarz;
    int wynik_gosc;
    int minuta;
public:
    Mecz(Klub* gospodarz, Klub* gosc)
    {
        this->_gospodarz = gospodarz;
        this->_gosc = gosc;
        this->minuta = 1;
        this->wynik_gosc = 0;
        this->wynik_gospodarz = 0;
    }
    
    void graj()
    {
        auto klub = this->_gosc;
        auto zawodnik = klub->losuj_zawodnika(Pozycja::Atak);
        string wiadomosc;
        Pozycja strefa = Pozycja::Pomoc;
        
        auto losuj_zawodnika = [&]()
        {
            Zawodnik* losowy;
            do
            {
                losowy = klub->losuj_zawodnika(strefa);
            }
            while (losowy == zawodnik);
            zawodnik = losowy;
        };
        
        auto wyswietl_zawodnika = [&]()
        {
            return zawodnik->imie() + " " + 
                zawodnik->nazwisko() + " " + 
                to_string(zawodnik->numer()) +  "(" + 
                klub->nazwa() + ")";
        };
        
        auto wynik = [&]()
        {
            return this->_gospodarz->nazwa() + " " + 
                to_string(this->wynik_gospodarz) + " - " +
                to_string(this->wynik_gosc) + " " +
                this->_gosc->nazwa();
        };
    
        auto przejecie = [&]()
        {
            auto z = wyswietl_zawodnika();
            klub = klub == this->_gosc ? this->_gospodarz : this->_gosc;
            if (strefa <= 1) strefa = Pozycja::Atak;
            else if (strefa >= 3) strefa = Pozycja::Obrona;
            losuj_zawodnika();
            wiadomosc += wyswietl_zawodnika() + " przejmuje piłkę od " + z;
        };
    
        auto podanie = [&](Pozycja pozycja, int szansa)
        {
            if (rand() % 100 < szansa)
            {
                wiadomosc = wyswietl_zawodnika();
                strefa = pozycja;
                losuj_zawodnika();
                wiadomosc += " podaje do " + wyswietl_zawodnika(); 
                return true;
            }
            
            przejecie();
            return false;
        };
        
        auto drybling = [&](int szansa)
        {
            if (rand() % 100 < szansa)
            {
                wiadomosc = wyswietl_zawodnika() + " drybluje";
                strefa = strefa == Pozycja::Atak ? strefa : static_cast<Pozycja>(strefa + 1);
                return true;
            }
            
            przejecie();
            return false;
        };
        
        auto strzal = [&](int szansa)
        {
            wiadomosc = wyswietl_zawodnika() + " strzela na bramkę\n";
            if (rand() % 100 < szansa)
            {
                wiadomosc += "gol dla " + klub->nazwa() + "\n";
                klub == this->_gosc ? this->wynik_gosc++ : this->wynik_gospodarz++;
                wiadomosc += wynik();
                strefa = Pozycja::Pomoc;
                return true;
            }
            
            przejecie();
            return false;
        };
        
        if (this->_gospodarz->liczba_zawodnikow() < 2 || this->_gosc->liczba_zawodnikow() < 2)
        {
            cout << "brak zawodników" << endl;
            return;
        }
        
        cout << this->_gospodarz->nazwa() + " vs. " + this->_gosc->nazwa() << endl; 

        for (; minuta <= 90; minuta++)
        {
            wiadomosc = string();
            int los = rand() % 100;
            
            switch (strefa)
            {
                case Pozycja::Bramka:
                    if (los < 60) podanie(Pozycja::Obrona, 80);
                    else if (los < 90) podanie(Pozycja::Pomoc, 50);
                    else podanie(Pozycja::Atak, 20);
                    break;
                case Pozycja::Obrona:
                    if (los < 30) drybling(50);
                    else
                    {
                        los = rand() % 100;
                        if (los < 30) podanie(Pozycja::Bramka, 100);
                        else if (los < 60) podanie(Pozycja::Obrona, 65);
                        else podanie(Pozycja::Pomoc, 50);
                    }
                    break;
                case Pozycja::Pomoc:
                    if (los < 10) strzal(10);
                    else if (los < 50) drybling(50);
                    else 
                    {
                        los = rand() % 100;
                        if (los < 30) podanie(Pozycja::Obrona, 100);
                        else if (los < 60) podanie(Pozycja::Pomoc, 65);
                        else podanie(Pozycja::Atak, 30);
                    }
                    break;
                case Pozycja::Atak:
                    if (los < 50) strzal(30);
                    else if (los < 75) drybling(30);
                    else
                    {
                        los = rand() % 100;
                        if (los < 60) podanie(Pozycja::Atak, 30);
                        else podanie(Pozycja::Pomoc, 50);
                    }
            }
            
            cout << "minuta " << minuta << " " << wiadomosc << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        cout << "gosc: " << this->wynik_gosc << endl;
        cout << "gospodarz: " << this->wynik_gospodarz << endl;
    }
};

class Liga
{
private:
    string _nazwa;
    Klub* _kluby[6];
    int liczba_klubow;

public:
    Liga(string nazwa)
    {
        this->_nazwa = nazwa;
        this->liczba_klubow = 0;
    }

    string nazwa()
    {
        return this->_nazwa;
    }

    string kluby()
    {
        auto kluby = string();

        for (int i = 0; i < this->liczba_klubow; i++)
        {
            auto klub = *this->_kluby[i];
            kluby += "----------\n" + klub.nazwa() + '\n';
            auto zawodnicy = klub.zawodnicy();
            if (zawodnicy != "")
            {
                kluby += "zawodnicy:\n";
                kluby += zawodnicy;
            }
        }

        return kluby;
    }

    void dodaj_klub(Klub* klub)
    {
        auto i = this->liczba_klubow >= 6 ? this->liczba_klubow - 1 : this->liczba_klubow++;
        this->_kluby[i] = klub;
    }
};

int main()
{
    auto l1 = Liga("A");
    auto k1 = Klub("Atletico Madrid", "biały");
    auto z1 = Zawodnik("Kylian", "Mbappé", Pozycja::Atak, 1);
    auto z2 = Zawodnik("Paul", "Pogba", Pozycja::Atak, 10);
    auto z3 = Zawodnik("Mario", "Balotelli", Pozycja::Pomoc, 20);
    auto z4 = Zawodnik("Didier", "Drogba", Pozycja::Atak, 7);
    auto z5 = Zawodnik("Yaya", "Touré", Pozycja::Pomoc, 15);
    auto z6 = Zawodnik("Robert", "Lewandowski", Pozycja::Atak, 7);
    auto k2 = Klub("AC Roma", "czerwony");
    auto k3 = Klub("Lech Poznań", "niebieski");
    auto k4 = Klub("FC Porto", "niebieski");
    auto k5 = Klub("Spartak Moskwa", "czerwony");
    auto k6 = Klub("PSV Eindhoven", "czerwony");
    l1.dodaj_klub(&k1);
    l1.dodaj_klub(&k2);
    l1.dodaj_klub(&k3);
    l1.dodaj_klub(&k4);
    l1.dodaj_klub(&k5);
    l1.dodaj_klub(&k6);
    l1.dodaj_klub(&k6);
    k1.dodaj_zawodnika(&z1);
    k1.dodaj_zawodnika(&z2);
    k1.dodaj_zawodnika(&z3);
    k1.dodaj_zawodnika(&z4);
    k1.dodaj_zawodnika(&z5);
    k1.dodaj_zawodnika(&z5);
    k1.usun_zawodnika(&z2);
    k1.dodaj_zawodnika(&z2);
    k1.transferuj_zawodnika(&z4, &k3);
    k1.transferuj_zawodnika(&z3, &k3);
    k3.dodaj_zawodnika(&z6);
    cout << l1.kluby();
    
    auto mecz = Mecz(&k1, &k3);
    mecz.graj();
    
    cin.get();
    return 0;
}
