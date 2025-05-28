#include "Bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include<algorithm>
#include<ctime>
#include<vector>
#include<sstream>
#include<cstring>

using namespace std;

void bitacora::menu()
{
    int choice;
    do {
        system("cls");

        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t |   SISTEMA GESTION BITACORA  |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t 1. Despliegue Bitacora"<<endl;
        cout<<"\t\t\t 2. Exit"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tOpcion a escoger:[1/2]"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tIngresa tu Opcion: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            desplegar();
            break;
        case 2:
            break;
        default:
            cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.get();
        }
    } while(choice != 2);
}

struct EntradaBitacora {
    int codigo;
    char nombre[20];
    char aplicacion[20];
    char accion[100];
    char fecha[30];
    char hora[10];
};

void bitacora::insertar(string nombre, int codigoDummy, string aplicacion, string accion) {
    fstream binFile;
    EntradaBitacora entrada;

    int ultimoCodigo = 1999;

    // Leer el utlimo código
    binFile.open("bitacora.dat", ios::in | ios::binary);
    if (binFile) {
        EntradaBitacora temp;
        while (binFile.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
            if (temp.codigo > ultimoCodigo)
                ultimoCodigo = temp.codigo;
        }
        binFile.close();
    }

    int nuevoCodigo = ultimoCodigo + 1;
    if (nuevoCodigo > 2999) {
        cout << "❌ Límite de bitácoras alcanzado (2999)" << endl;
        return;
    }

    // Llenar campos
    entrada.codigo = nuevoCodigo;
    strncpy(entrada.nombre, nombre.c_str(), sizeof(entrada.nombre));
    strncpy(entrada.aplicacion, aplicacion.c_str(), sizeof(entrada.aplicacion));
    strncpy(entrada.accion, accion.c_str(), sizeof(entrada.accion));

    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);
    strftime(entrada.fecha, sizeof(entrada.fecha), "%b %d %Y", timeinfo);
    strftime(entrada.hora, sizeof(entrada.hora), "%H:%M:%S", timeinfo);

    // Guardar en archivo binario
    binFile.open("bitacora.dat", ios::app | ios::binary);
    binFile.write(reinterpret_cast<char*>(&entrada), sizeof(entrada));
    binFile.close();
}


void bitacora::desplegar() {
    system("cls");
    fstream binFile;
    EntradaBitacora entrada;
    int total = 0;

    cout << "\n------------------- Bitácora -------------------\n";
    binFile.open("bitacora.dat", ios::in | ios::binary);
    if (!binFile) {
        cout << "\n\t\t\tNo hay información...\n";
    } else {
        while (binFile.read(reinterpret_cast<char*>(&entrada), sizeof(entrada))) {
            cout << "-----------------------------------------------\n";
            cout << "[" << total << "] Código:      " << entrada.codigo << "\n";
            cout << "    Usuario:     " << entrada.nombre << "\n";
            cout << "    Aplicación:  " << entrada.aplicacion << "\n";
            cout << "    Acción:      " << entrada.accion << "\n";
            cout << "    Fecha:       " << entrada.fecha << " " << entrada.hora << "\n";
            total++;
        }
        if (total == 0) {
            cout << "\n\t\t\tNo hay información...\n";
        } else {
            cout << "-----------------------------------------------\n";
        }
    }
    binFile.close();
    system("pause");
}
