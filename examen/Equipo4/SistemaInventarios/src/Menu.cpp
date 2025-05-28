
#include "Menu.h"
#include "Bitacora.h"

Menu::Menu() {}

void Menu::mostrarOpciones(Inventario& inventario, Facturacion& factura, const string& nombreUsuario) {
    int subopcion;
    bitacora auditoria;

    do {
        system("cls");
        cout << "\n=====================================\n";
        cout << "      --- SUBMENU INVENTARIO ---\n";
        cout << "=====================================\n";
        cout << "1. CRUD\n";
        cout << "2. Regresar al menu principal\n";
        cout << "-------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> subopcion;

        switch (subopcion) {
            case 1:
                auditoria.insertar(nombreUsuario, 2001, "Ver Inventario General", "Visualización del inventario");
                inventario.mostrarInventarioGeneral();
                break;
            case 2:
                cout << "Regresando al menú principal...\n";
                break;
            default:
                cout << "Opción no válida, intente de nuevo.\n";
        }

        system("pause");

    } while (subopcion != 5);
}

Menu::~Menu() {}
