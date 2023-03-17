#include <iostream>
#include <string>
#include "leksykon.cpp"


using namespace std;

int main()
{

    string wejscie_konsoli;
    string ostatnia_komenda;

    //konsola 
    while(1)
    {

        //sczytywanie wejscia konsoli
        cout<<"pol++>";
        getline(cin, wejscie_konsoli);

        //wyjscie
        if (wejscie_konsoli == "wyjdz")
        {
            break;
        }
        if (wejscie_konsoli.rfind("echo ", 4) == 0)
        {
            cout<<wejscie_konsoli.substr(5,wejscie_konsoli.length()) + "\n";
        }
        if (wejscie_konsoli.rfind("leksykon ", 9) == 0)
        {
            char* wejscie_konsoli_char = const_cast<char*>(wejscie_konsoli.c_str());
            leksykowanie(wejscie_konsoli_char);
        }
        ostatnia_komenda = wejscie_konsoli;     
    }

    return 0;

}
//TODO list
//dodac liste ostatnich komend pod strzalka w gore i w dol na podstawie tekstu ktory sie wyswietla po kliknieciu strzalki
//dodac liste w ktorej jest zapisane jaki identyfikator jest na konkretnym miejscu w wejscie_konsoli

