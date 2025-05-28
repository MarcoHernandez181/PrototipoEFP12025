#include <iostream>
#include "Usuario.h"
#include "Inventario.h"
#include "Facturacion.h"
#include "Bitacora.h"
#include "Menu.h"
using namespace std;

usuarios usuarioRegistrado;
Menu menu;

int main() {
    bool accesoUsuarios = false;
    char intentarDeNuevo;

    do {
        accesoUsuarios = usuarioRegistrado.loginUsuarios();

        if (!accesoUsuarios) {
            cout << "\nAutenticación fallida. ¿Deseas intentar de nuevo? (S/N): ";
            cin >> intentarDeNuevo;
            intentarDeNuevo = toupper(intentarDeNuevo);
        }

    } while (!accesoUsuarios && intentarDeNuevo == 'S');

    if (!accesoUsuarios) {
        cout << "\nNo se pudo acceder al sistema. Cerrando...\n";
        return 0;
    }

    Inventario inventario;
    Facturacion factura;
    bitacora bit;
    string nombreUsuario = usuarioRegistrado.getNombre();

    int opcionGeneral;
    do {
        system("cls");
        cout << "\n=========== MENÚ GENERAL ===========\n";
        cout << "Usuario: " << nombreUsuario << "\n";
        cout << "1. Catalogo\n";
        cout << "2. Informes\n";
        cout << "3. Seguridad\n";
        cout << "4. Salir de sesion\n";
        cout << "====================================\n";
        cout << "Seleccione una opción: ";
        cin >> opcionGeneral;

        switch (opcionGeneral) {
            case 1:
                menu.mostrarOpciones(inventario, factura, nombreUsuario);
                bit.insertar(nombreUsuario, 1999, "Catálogo", "Acceso al submenú de inventario");
                break;

            case 2: {
                int opcionProcesos;
                do {
                    system("cls");
                    cout << "\n=========== MENÚ DE PROCESOS ===========\n";
                    cout << "1. Facturacion\n";
                    cout << "2. Gestion de usuarios\n";
                    cout << "3. Volver al menú general\n";
                    cout << "========================================\n";
                    cout << "Seleccione una opción: ";
                    cin >> opcionProcesos;

                    switch (opcionProcesos) {
                        case 1:
                            factura.generarFactura(inventario);
                            bit.insertar(nombreUsuario, 2101, "Procesos", "Acceso a facturación");
                            break;
                        case 2:
                            usuarioRegistrado.menuUsuarios();
                            bit.insertar(nombreUsuario, 2102, "Procesos", "Acceso a gestión de usuarios");
                            break;
                        case 3:
                            cout << "Volviendo al menú general...\n";
                            break;
                        default:
                            cout << "Opción inválida. Intente nuevamente.\n";
                            system("pause");
                    }
                } while (opcionProcesos != 3);
                break;
            }

            case 3:
                bit.menu();
                bit.insertar(nombreUsuario, 2003, "Informes", "Revisión de bitácora");
                break;

            case 4:
                cout << "\nCerrando sesión...\n";
                break;

            default:
                cout << "\nOpción inválida. Intenta de nuevo.\n";
                system("pause");
        }

    } while (opcionGeneral != 4);

    cout << "* Hasta la próxima *\n";
    return 0;
}
