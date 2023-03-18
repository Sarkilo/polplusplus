#include <iostream>
#include <string>
#include "leksykon.cpp"
#include <list>
#include <stdlib.h>

using namespace std;

int main()
{

    string wejscie_konsoli;
    string ostatnia_komenda;
    extern list<Token::Typ> lista_elementow_w_leksykonie;

    //konsola 
    while(true)
    {

        //sczytywanie wejscia konsoli
        cout<<"pol++>";
        getline(cin, wejscie_konsoli);

        //wyjscie
        if (wejscie_konsoli == "")
        {
            continue;
        }
        else if (wejscie_konsoli == "wyjdz")
        {
            break;
        }
        else if (wejscie_konsoli.rfind("pomocy", 5) == 0)
        {
            const char* wiadomosc_pomocy =
            "Prototyp pol++\n"
            "\n"
            "Te komendy są zdefiniowane wewnętrznie.  Wpisz 'pomocy' by zobaczyć tę listę.\n"
            "\n"
            "echo [tekst]\n"
            "leksykon [tekst]\n"
            "wyczysc\n";
            cout << wiadomosc_pomocy;
        }
        else if (wejscie_konsoli.rfind("echo ", 4) == 0)
        {
            cout<<wejscie_konsoli.substr(5,wejscie_konsoli.length()) + "\n";
        }
        else if (wejscie_konsoli.rfind("leksykon ", 9) == 0)
        {
            char* wejscie_konsoli_char = const_cast<char*>(wejscie_konsoli.c_str());
            leksykowanie(wejscie_konsoli_char);
        }
        else if (wejscie_konsoli.rfind("wyczysc", 4) == 0)
        {
            system("clear");
        }
        else
        {
            cout << "pol++: Nieznana komenda" << "\n"; 
        }
        ostatnia_komenda = wejscie_konsoli; 
    }

    return 0;

}
//TODO list
//dodac liste ostatnich komend pod strzalka w gore i w dol na podstawie tekstu ktory sie wyswietla po kliknieciu strzalki
//dodac liste w ktorej jest zapisane jaki identyfikator jest na konkretnym miejscu w wejscie_konsoli

