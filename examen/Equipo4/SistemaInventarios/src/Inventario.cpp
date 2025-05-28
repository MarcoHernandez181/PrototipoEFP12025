
#include "Inventario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

Inventario::Inventario() {
    system("cls");
    cout << "Cargando inventario..." << endl;
    cargarDesdeArchivo();
}

void Inventario::agregarProducto(int codigo, string nombre, float precio, int stock, string tipo) {
    system("cls");
    cout << "=== AGREGAR NUEVO PRODUCTO ===" << endl;

    if (buscarProducto(codigo) != nullptr) {
        cerr << "\nError: El código " << codigo << " ya existe." << endl;
        system("pause");
        return;
    }

    productos.push_back(Producto(codigo, nombre, precio, stock, tipo));
    guardarEnArchivo();

    cout << "\nProducto agregado exitosamente!" << endl;
    system("pause");
}

void Inventario::mostrarInventarioGeneral() {
    system("cls");


    cout << fixed << setprecision(2);


    ofstream backup("kardex_backup.bin", ios::binary | ios::app);
    if (!backup) {
        cerr << "Error al crear archivo de backup" << endl;
    }

    cout << "==================================================================\n";
    cout << "|  - INVENTARIO COMPLETO                         |\n";
    cout << "==================================================================\n";
    cout << "| Cod | Nombre       | Precio  | Stock | Entradas | Salidas | Total  |\n";
    cout << "|-----|--------------|---------|-------|----------|---------|--------|\n";

   int numProductos = productos.size();
   if(backup) {
    backup.write(reinterpret_cast<const char*>(&numProductos), sizeof(numProductos));
   }



    for (const auto& p : productos) {

        int entradas = 0;
        int salidas = 0;

        ifstream bodega("bodega.bin");
        if (bodega.is_open()) {
            string linea;
            while (getline(bodega, linea)) {
                stringstream ss(linea);
                string item;
                vector<string> datos;

                while (getline(ss, item, ',')) {
                    datos.push_back(item);
                }


                if (datos.size() >= 4 && stoi(datos[0]) == p.codigo) {
                    if (datos[2] == "ENTRADA") {
                        entradas += stoi(datos[3]);
                    } else if (datos[2] == "SALIDA") {
                        salidas += stoi(datos[3]);
                    }
                }
            }
            bodega.close();
        }


        float valorTotal = p.precio * p.stock;


        cout << "| " << setw(3) << left << p.codigo << " | "
             << setw(12) << left << p.nombre << " | "
             << setw(7) << right << p.precio << " | "
             << setw(5) << right << p.stock << " | "
             << setw(8) << right << entradas << " | "
             << setw(7) << right << salidas << " | "
             << "$" << setw(6) << right << valorTotal << " |\n";



        if (backup) {

           size_t nombreLenght = p.nombre.size();
            backup.write(reinterpret_cast<const char*>(&nombreLenght), sizeof(nombreLenght));


            backup.write(reinterpret_cast<const char*>(&p.codigo), sizeof(p.codigo));
            backup.write(reinterpret_cast<const char*>(&p.precio), sizeof(p.precio));
            backup.write(reinterpret_cast<const char*>(&p.stock), sizeof(p.stock));
            backup.write(reinterpret_cast<const char*>(&entradas), sizeof(entradas));
            backup.write(reinterpret_cast<const char*>(&salidas), sizeof(salidas));
            backup.write(reinterpret_cast<const char*>(&valorTotal), sizeof(valorTotal));
        }
    }

    cout << "==================================================================\n";
    if (backup) {
        backup.close();
        cout << "\nBackup generado en: kardex_backup.bin\n";
    }

 cout << "\nOpciones:\n";
    cout << "1. Agregar stock (Entrada)\n";
    cout << "2. Sacar stock (Salida)\n";
    cout << "3. Agregar nuevo producto\n";
    cout << "4. Volver al menu principal\n";
    cout << "Seleccione una opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1 || opcion == 2) {
        int codigo, cantidad;
        cout << "Ingrese codigo de producto: ";
        cin >> codigo;
        cout << "Ingrese cantidad: ";
        cin >> cantidad;

        movimientoBodega(codigo, cantidad, opcion == 1);
        mostrarInventarioGeneral();
    }
    else if (opcion == 3) {

        system("cls");
        cout << "=== AGREGAR NUEVO PRODUCTO ===" << endl;

        int codigo, stock;
        string nombre, tipo;
        float precio;

        cout << "Ingrese codigo del producto: ";
        cin >> codigo;


        if (buscarProducto(codigo) != nullptr) {
            cout << "\nError: El codigo " << codigo << " ya existe en el inventario.\n";
            system("pause");
            mostrarInventarioGeneral();
            return;
        }

        cin.ignore();
        cout << "Ingrese nombre del producto: ";
        getline(cin, nombre);

        cout << "Ingrese precio unitario: ";
        cin >> precio;

        cout << "Ingrese cantidad inicial en stock: ";
        cin >> stock;

        cout << "Ingrese tipo de producto: ";
        cin >> tipo;


        productos.push_back(Producto(codigo, nombre, precio, stock, tipo));
        guardarEnArchivo();


        movimientoBodega(codigo, stock, true);

        cout << "\nProducto agregado exitosamente!\n";
        system("pause");
        mostrarInventarioGeneral();
    }

}

Producto* Inventario::buscarProducto(int codigo) {
    for (auto& p : productos) {
        if (p.codigo == codigo) {
            return &p;
        }
    }
    return nullptr;
}

void Inventario::mostrarInventarioPorTipo(string tipo) {
    system("cls");
    cout << fixed << setprecision(2);

    cout << "==============================================================\n";
    cout << "| KARDEX POR TIPO - " << setw(44) << left << tipo << "|\n";
    cout << "==============================================================\n";
    cout << "| Cod | Nombre       | Precio  | Stock | Entradas | Salidas | Total  |\n";
    cout << "|-----|--------------|---------|-------|----------|---------|--------|\n";

    for (const auto& p : productos) {
        if (p.tipo != tipo) continue;

        int entradas = 0;
        int salidas = 0;

        ifstream bodega("bodega.bin");
        if (bodega.is_open()) {
            string linea;
            while (getline(bodega, linea)) {
                stringstream ss(linea);
                string item;
                vector<string> datos;
                while (getline(ss, item, ',')) datos.push_back(item);

                if (datos.size() >= 4 && stoi(datos[0]) == p.codigo) {
                    if (datos[2] == "ENTRADA") entradas += stoi(datos[3]);
                    else if (datos[2] == "SALIDA") salidas += stoi(datos[3]);
                }
            }
            bodega.close();
        }

        float total = p.precio * p.stock;

        cout << "| " << setw(3) << left << p.codigo << " | "
             << setw(12) << left << p.nombre << " | "
             << setw(7) << right << p.precio << " | "
             << setw(5) << right << p.stock << " | "
             << setw(8) << right << entradas << " | "
             << setw(7) << right << salidas << " | "
             << "$" << setw(6) << right << total << " |\n";
    }

    cout << "==============================================================\n";
    system("pause");
}


void Inventario::ventas(int codigo, int stock) {
    Producto* p = buscarProducto(codigo);
    if (p != nullptr) {
        if (p->stock >= stock) {
            p->stock -= stock;
            cout << "Venta realizada: " << stock << " unidades de " << p->nombre << " vendidas." << endl;
            guardarEnArchivo();
        } else {
            cout << "No hay suficiente stock para realizar la venta." << endl;
        }
    } else {
        cout << "Producto no encontrado." << endl;
    }
}

void Inventario::guardarEnArchivo() const {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir archivo para escritura." << endl;
        return;
    }

    for (const auto& p : productos) {
        archivo << p.codigo << "," << p.nombre << ","
                << p.precio << "," << p.stock << ","
                << p.tipo << "\n";
    }
}

void Inventario::cargarDesdeArchivo() {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se encontró archivo. Se creará uno nuevo." << endl;
        return;
    }

    productos.clear();
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string item;
        string datos[5];
        int i = 0;

        while (getline(ss, item, ',') && i < 5) {
            datos[i++] = item;
        }

        if (i == 5) {
            try {
                productos.emplace_back(
                    stoi(datos[0]),
                    datos[1],
                    stof(datos[2]),
                    stoi(datos[3]),
                    datos[4]
                );
            } catch (...) {
                cerr << "Error en línea: " << linea << endl;
            }
        }
    }
}

bool Inventario::eliminarProducto(int codigo) {
    system("cls");
    cout << "=== ELIMINAR PRODUCTO ===" << endl;

    auto it = remove_if(productos.begin(), productos.end(),
        [codigo](const Producto& p) { return p.codigo == codigo; });

    if (it != productos.end()) {
        productos.erase(it, productos.end());
        guardarEnArchivo();
        cout << "\nProducto eliminado exitosamente!" << endl;
        system("pause");
        return true;
    }

    cout << "\nError: No se encontró el producto con código " << codigo << endl;
    system("pause");
    return false;
}


void Inventario::movimientoBodega(int codigo, int cantidad, bool esEntrada) {
    system("cls");
    cout << "=== MOVIMIENTO DE BODEGA ===" << endl;

    Producto* p = buscarProducto(codigo);
    if (p != nullptr) {
        if (esEntrada) {
            p->stock += cantidad;
            cout << "Entrada registrada: " << cantidad
                 << " unidades de " << p->nombre << endl;
        } else {
            if (p->stock >= cantidad) {
                p->stock -= cantidad;
                cout << "Salida registrada: " << cantidad
                     << " unidades de " << p->nombre << endl;
            } else {
                cout << "Error: Stock insuficiente para salida." << endl;
                system("pause");
                return;
            }
        }


         ofstream archivo("bodega.bin", ios::binary | ios::app);

        if (archivo) {

            archivo.write(reinterpret_cast<const char*>(&p->codigo), sizeof(p->codigo));
            char tipoMovimiento = esEntrada ? 'E' : 'S';
            archivo.write(&tipoMovimiento, sizeof(char));
            archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
            archivo.write(reinterpret_cast<const char*>(&p->stock), sizeof(p->stock));
            time_t ahora = time(nullptr);
            archivo.write(reinterpret_cast<const char*>(&ahora), sizeof(ahora));
        }
        archivo.close();

        guardarEnArchivo();
    } else {
        cout << "Error: Producto no encontrado." << endl;
    }
    system("pause");
}

void Inventario::mostrarMovimientosBodega() {
    system("cls");
    cout << "\n--- HISTORIAL DE MOVIMIENTOS DE BODEGA ---\n";
    cout << "Codigo\tNombre\tTipo\tCantidad\tStock\tFecha\n";

    ifstream archivo("bodega.bin");
    if (!archivo) {
        cout << "No hay movimientos registrados." << endl;
        system("pause");
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string item;
        string datos[6];
        int i = 0;

        while (getline(ss, item, ',') && i < 6) {
            datos[i++] = item;
        }

        if (i >= 5) {
            cout << datos[0] << "\t" << datos[1] << "\t"
                 << datos[2] << "\t" << datos[3] << "\t\t"
                 << datos[4] << "\t";
            if (i > 5) cout << datos[5];
            cout << endl;
        }
    }
    archivo.close();
    system("pause");
}

void Inventario::mostrarKardexBodega() {
    system("cls");

    cout << "=============================================\n";
    cout << "| KARDEX DE BODEGA - MOVIMIENTOS DETALLADOS |\n";
    cout << "=============================================\n";
    cout << "| Codigo | Nombre       | Stock | Entradas | Salidas | Monto Total |\n";
    cout << "|--------|--------------|-------|----------|---------|-------------|\n";

    std::map<int, std::tuple<string, int, int, int, float>> resumen;

    ifstream archivo("bodega.bin");
    if (archivo) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            vector<string> datos;
            string item;

            while (getline(ss, item, ',')) {
                datos.push_back(item);
            }

            if (datos.size() >= 5) {
                try {
                    int codigo = stoi(datos[0]);
                    string tipo = datos[2];
                    int cantidad = stoi(datos[3]);
                    int stock = stoi(datos[4]);
                    float monto = 0.0f;

                    Producto* p = buscarProducto(codigo);
                    if (p) monto = cantidad * p->precio;

                    if (resumen.find(codigo) == resumen.end()) {
                        resumen[codigo] = make_tuple(p ? p->nombre : "DESCONOCIDO", stock, 0, 0, 0.0f);
                    }

                    auto& item = resumen[codigo];
                    get<1>(item) = stock;
                    if (tipo == "ENTRADA") {
                        get<2>(item) += cantidad;
                        get<4>(item) += monto;
                    } else {
                        get<3>(item) += cantidad;
                        get<4>(item) -= monto;
                    }
                } catch (...) {}
            }
        }
        archivo.close();
    }


    for (const auto& [codigo, datos] : resumen) {
        printf("| %-6d | %-12s | %-5d | %-8d | %-7d | $%-10.2f |\n",
               codigo,
               get<0>(datos).c_str(),
               get<1>(datos),
               get<2>(datos),
               get<3>(datos),
               get<4>(datos));
    }
    cout << "=============================================\n";
    system("pause");
}
Inventario::~Inventario() {
    guardarEnArchivo();
}
