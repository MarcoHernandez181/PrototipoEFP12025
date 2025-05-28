#ifndef FACTURACION_H
#define FACTURACION_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "Inventario.h"

using namespace std;

struct ProductoFactura {
    int CodigoSeleccionado;
    int CantidadLlevada;
};

class Facturacion {
private:
    vector<ProductoFactura> listprod;
    string now, ape, ced, tel, dir;
    float total;
public:
    Facturacion();
    ~Facturacion();
    void generarFactura(Inventario& inventario);
};
#endif
