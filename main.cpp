#include <iostream>
#include <cstdlib>
#include "interfaz.h"
#include <fstream>
#include <stdlib.h>

using namespace std;


int main(int argc, char** argv) {
    int principal;
    while(principal!=4){
        cout<<"Garden Of Avalon!"<<endl<<"Bienvenido a los laberintos de Avalon, ¿Que gustaría hacer este dia?"<<endl<<"1. Jugar"<<endl<<"2. Abrir Ayuda"<<endl<<"3. Abrir bitacora del proyecto"<<endl<<"4. Salir"<<endl<<"Su opción: ";
        cin>>principal;
        if(principal==1){
            string nickname;
            cout<<"Ingrese un nickname: ";
            cin>>nickname;
            Ventana v;
            int puntaje;
            float tiempo;
            int opcion=2;
            int gato;
    
            do{
                cout<<"Escoja dificultad: "<<endl<<"1. Facil"<<endl<<"2. Intermedio"<<endl<<"3. Dificil"<<endl<<"Opción: ";
                cin>>gato;
                v.LlenarMatriz2(gato);
                v.IniciarVentana();
                cout<<endl;
                puntaje=v.ObtenerPuntaje();
                tiempo=v.ObtenerTiempo();
                cout<<"El puntaje obtenido es: "<<puntaje<<endl<<endl;
                ofstream archivo2("Highscore.txt",ios::app);
                archivo2<<nickname<<" "<<puntaje<<" "<<tiempo<<endl;
                archivo2.close();
                cout<<"¿Quiere volver a jugar?"<<endl<<"1. Si"<<endl<<"2. No"<<endl<<"Su opcion: ";
                cin>>opcion;
                cout<<endl;
            }while(opcion==1);
        }
        else if(principal==2){
        system("AYUDA.pdf");
        cout<<endl;
        }
        else if(principal==3){
        system("BITACORA.pdf");
        cout<<endl;
        }
    }
    
    return 0;
}

