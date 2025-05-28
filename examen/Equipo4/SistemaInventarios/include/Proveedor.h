#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <string>
#include "Bitacora.h"

using namespace std;

class proveedores
{
private:
    int id;
    string nombre;
    string direccion;

public:
    proveedores();
    ~proveedores();
    void consultarProveedores();
};

#endif // PROVEEDORES_H
