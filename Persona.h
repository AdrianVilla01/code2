#include "Poker.h"
#include <iostream>
#include <Persona.h>
#include <fstream>
#include <istream>
#include <vector>
#include <string>

using namespace std;

void guardarRecords(vector<Persona> & jugadores)
{
    string datos = "";
    ofstream file;
    file.open("players.txt");
    for (unsigned int i = 0; i < jugadores.size() ; i++)
    {
        datos = jugadores[i].getNombre() + "&" + std::to_string(jugadores[i].getRecord()) + "\n";
        file<<datos;
    }
    file.close();

}

bool obtenerJugadores(ifstream & file, Persona& jugador)
{
    string nombre;
    int record;
    char buffer[200];

    file.getline(buffer, 200, '&');
    if (!file.good())
    {
        return false;
    }
    else
    {
        nombre = buffer;

        file.getline(buffer, 200, '\n');
        record = stoi(buffer);

        jugador.setNombre(nombre);
        jugador.setRecord(record);
        return true;
    }
}

void ordenarJugadores(vector<Persona> & jugadores)
{
    string tempString = "";
    int tempInt = 0;
    for(unsigned int i = 0;i < jugadores.size() ; i++)
    {
        for(unsigned int j = 0;j < (jugadores.size() - 1); j++)
        {
            if(jugadores[j].getRecord() < jugadores[j+1].getRecord())
            {

                tempString = jugadores[j].getNombre();
                tempInt = jugadores[j].getRecord();

                jugadores[j].setNombre(jugadores[j+1].getNombre());
                jugadores[j].setRecord(jugadores[j+1].getRecord());

                jugadores[j+1].setNombre(tempString);
                jugadores[j+1].setRecord(tempInt);

            }
        }
    }
}

int main()
{
    vector<Persona> jugadores;
    int jugar = 0;

    ifstream players;
    players.open("players.txt");
    Persona jugador = Persona();
    while(obtenerJugadores(players, jugador))
    {
        jugadores.push_back(jugador);
    }
    players.close();

    cout<<"Desea jugar? Yes[1]/No[0]: ";
    cin>>jugar;
    cin.ignore();
    system("cls");

    if(jugar)
    {
        Poker game = Poker();
        do
        {
            system("cls");

            do
            {
                game.play();
                system("cls");
                cout<<"Desea continuar jugando? Yes[1]/No[0]: ";
                cin>>jugar;
                string valnull = "";
                getline(cin, valnull);
                system("cls");
            }while(jugar && game.getBolsa() > 0);

            system("cls");
            cout<<"Desea volver a jugar? Yes[1]/No[0]: ";
            cin>>jugar;
        }while(jugar);
        jugador.setNombre(game.getName());
        jugador.setRecord(game.getBolsa());
        jugadores.push_back(jugador);
    }


    system("cls");
    cout<<"Records"<<endl<<endl<<endl;

    ordenarJugadores(jugadores);

    for(unsigned int i = 0; i<jugadores.size() ; i++)
    {
        cout<<jugadores[i].getNombre()<<" obtuvo un record de "<<jugadores[i].getRecord()<<endl;
    }

    guardarRecords(jugadores);

}
