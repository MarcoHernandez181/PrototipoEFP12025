#include "Facturacion.h"
Facturacion::Facturacion() {
    total = 0;
}


void Facturacion::generarFactura(Inventario& inventario) {
    total = 0;
    string opc2 = "1";

    cout << "Generando factura...\n";
    cout << "Ingrese los datos del cliente:\n";
    cout << "Nombre: "; cin >> now;
    cout << "Apellido: "; cin >> ape;
    cout << "Cédula: "; cin >> ced;
    cout << "Teléfono: "; cin >> tel;
    cout << "Dirección: "; cin.ignore(); getline(cin, dir);

    while (opc2 == "1") { //corrección de error de desbordamiento al ingresaar tipos de datos incompatibles con el tipo de variables, Luis Valenzuela 2 de mayo de 2025
        ProductoFactura nuevoProducto;
        cout << "Código del producto: ";
        cin >> nuevoProducto.CodigoSeleccionado;
        cout << "Cantidad: ";
        cin >> nuevoProducto.CantidadLlevada;

        listprod.push_back(nuevoProducto);

        cout << "¿Desea agregar otro producto? 1(Sí), 2(No): ";
        cin >> opc2;
    }

    cout << "\n----- FACTURA -----\n";
    cout << "Cliente: " << now << " " << ape << "\n";
    cout << "Cédula: " << ced << "\n";
    cout << "Teléfono: " << tel << "\n";
    cout << "Dirección: " << dir << "\n\n";

    cout << left << setw(10) << "Código"
         << setw(20) << "Producto"
         << setw(10) << "Cantidad"
         << setw(10) << "Precio"
         << setw(10) << "Subtotal" << endl;

    cout << string(60, '-') << endl;

    for (const auto& prod : listprod) {
        Producto* p = inventario.buscarProducto(prod.CodigoSeleccionado);
        if (p) {
            float subtotal = p->precio * prod.CantidadLlevada;
            total += subtotal;
            cout << left << setw(10) << p->codigo
                 << setw(20) << p->nombre
                 << setw(10) << prod.CantidadLlevada
                 << setw(10) << p->precio
                 << setw(10) << subtotal << endl;
        } else {
            cout << "Producto con código " << prod.CodigoSeleccionado << " no encontrado.\n";
        }
    }

    cout << "\nTotal a pagar: Q" << fixed << setprecision(2) << total << endl;
}

Facturacion::~Facturacion() {
    // Destructor vacío
}
