#ifndef BITACORA_H
#define BITACORA_H
#include<iostream>

using std::string;

class bitacora
{
    public:
        void menu();
        void insertar(string nombre, int codigo, string aplicacion, string accion); //se agrega el int codigo Ferdynand Monroy

        void desplegar();
    protected:

    private:
		string nombre, aplicacion, accion, fecha;

};
#endif // BITACORA_H
