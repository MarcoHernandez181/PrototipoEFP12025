#include "Proveedor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <conio.h>

using namespace std;

proveedores::proveedores()
{
    id = 0;
    nombre = "";
    direccion = "";
}

proveedores::~proveedores()
{
}

void proveedores::consultarProveedores()
{
    system("cls");
    cout << "\t\t\t-------------------------------------------------------" << endl;
    cout << "\t\t\t |   CONSULTA DE PROVEEDORES                          |" << endl;
    cout << "\t\t\t-------------------------------------------------------" << endl;

    fstream fileProveedores("Proveedores.txt", ios::in);
    if (!fileProveedores)
    {
        cout << "\n\t\t\t No hay información de proveedores..." << endl;
        bitacora auditoria;
        auditoria.insertar("Sistema", 100, "LOGF", "Consulta de proveedores fallida: archivo no encontrado");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    // Leer y mostrar lista de proveedores
    vector<pair<int, string>> listaProveedores;
    string linea;
    bool hayProveedores = false;
    cout << "\n\tID\tNombre\t\tDirección" << endl;
    cout << "\t-------------------------------------" << endl;

    while (getline(fileProveedores, linea))
    {
        istringstream iss(linea);
        int tempId;
        string tempNombre, tempDireccion;
        if (iss >> tempId)
        {
            getline(iss, tempNombre, ' ');
            getline(iss, tempNombre, ' ');
            getline(iss, tempDireccion);
            listaProveedores.push_back({tempId, tempNombre});
            hayProveedores = true;
            cout << "\t" << tempId << "\t" << tempNombre << "\t\t" << tempDireccion << endl;
        }
    }
    fileProveedores.close();

    if (!hayProveedores)
    {
        cout << "\n\t\t\t No se encontraron proveedores registrados." << endl;
        bitacora auditoria;
        auditoria.insertar("Sistema", 100, "LOGF", "Consulta de proveedores fallida: no hay proveedores");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    // Solicitar ID del proveedor
    int idSeleccionado;
    cout << "\n\tIngrese el ID del proveedor para ver sus productos (0 para salir): ";
    cin >> idSeleccionado;
    cin.ignore();

    if (idSeleccionado == 0)
    {
        cout << "\n\t\t\t Consulta cancelada." << endl;
        bitacora auditoria;
        auditoria.insertar("Sistema", 100, "LOGF", "Consulta de productos cancelada por el usuario");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    bool idValido = false;
    string nombreProveedor;
    for (const auto& prov : listaProveedores)
    {
        if (prov.first == idSeleccionado)
        {
            idValido = true;
            nombreProveedor = prov.second;
            break;
        }
    }

    if (!idValido)
    {
        cout << "\n\t\t\t Error: ID de proveedor no válido." << endl;
        bitacora auditoria;
        auditoria.insertar("Sistema", 100, "LOGF", "Consulta de productos fallida: ID de proveedor no válido");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    fstream fileProductos("ProductosProveedor.txt", ios::in);
    if (!fileProductos)
    {
        cout << "\n\t\t\t No hay información de productos para proveedores..." << endl;
        bitacora auditoria;
        auditoria.insertar(nombreProveedor, 100, "LOGF", "Consulta de productos fallida: archivo de productos no encontrado");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    cout << "\n\tProductos vendidos por " << nombreProveedor << " (ID: " << idSeleccionado << "):" << endl;
    cout << "\t-------------------------------------------------------" << endl;
    cout << "\tCódigo\tNombre Producto\tCantidad\tTotal Neto" << endl;
    cout << "\t-------------------------------------------------------" << endl;

    bool hayProductos = false;
    while (getline(fileProductos, linea))
    {
        istringstream iss(linea);
        int tempIdProv;
        string codigoProducto, nombreProducto;
        int cantidad;
        float precioUnitario, totalNeto;
        if (iss >> tempIdProv >> codigoProducto)
        {
            getline(iss, nombreProducto, ' ');
            getline(iss, nombreProducto, ' ');
            iss >> cantidad >> precioUnitario >> totalNeto;
            if (tempIdProv == idSeleccionado)
            {
                hayProductos = true;
                cout << "\t" << codigoProducto << "\t" << nombreProducto << "\t\t" << cantidad << "\t\t" << totalNeto << endl;
            }
        }
    }
    fileProductos.close();

    if (!hayProductos)
    {
        cout << "\n\t\t\t No se encontraron productos para este proveedor." << endl;
        bitacora auditoria;
        auditoria.insertar(nombreProveedor, 100, "LOGF", "Consulta de productos fallida: no hay productos para el proveedor");
    }
    else
    {
        bitacora auditoria;
        auditoria.insertar(nombreProveedor, 100, "LOGS", "Consulta de productos exitosa");
    }

    cout << "\n\t\t\t Presione Enter para continuar...";
    cin.get();
}

