#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Inventario.h"
#include "Facturacion.h"


using namespace std;
class Menu {
public:
    Menu();
    ~Menu();
    void mostrarOpciones(Inventario& inventario, Facturacion& factura, const string& nombreUsuario);
};

#endif

