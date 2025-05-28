#include "Usuario.h"
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <sstream>
#include "Bitacora.h"
#include <vector>
using namespace std;

usuarios::usuarios()
{
    // ctor
}

usuarios::~usuarios()
{
    // dtor
}

bool usuarios::loginUsuarios()
{
    string usuario, contra;
    int contador = 0;
    bool ingresa = false;

    do
    {
        system("cls");
        cout << "---------------------------" << endl;
        cout << " AUTENTICACION DE USUARIOS " << endl;
        cout << "---------------------------" << endl;

        cout << "\nNombre Usuario: ";
        getline(cin, usuario);

        cout << "\nContrasena: ";
        char caracter;
        contra = "";
        caracter = getch();
        while (caracter != 13) // Enter
        {
            if (caracter != 8) // Retroceso
            {
                contra.push_back(caracter);
                cout << "*";
            }
            else
            {
                if (contra.length() > 0)
                {
                    cout << "\b \b";
                    contra = contra.substr(0, contra.length() - 1);
                }
            }
            caracter = getch();
        }

        if (buscar(usuario, contra))
        {
            ingresa = true;
            cout << "\n=== Bienvenido al Sistema ===" << endl;
            bitacora auditoria;
            auditoria.insertar(name, 100, "LOGS", "Inicio exitoso");
            cin.get();
        }
        else
        {
            cout << "\nEl usuario y/o contrasena son incorrectos" << endl;
            bitacora auditoria;
            auditoria.insertar(usuario, 100, "LOGF", "Intento fallido");
            cin.get();
            contador++;
        }

    } while (!ingresa && contador < 3);

    if (!ingresa)
    {
        cout << "\nLo siento, no puede ingresar al sistema..." << endl;
        cin.get();
    }

    return ingresa;
}

void usuarios::consultarUsuarios()
{
    system("cls");
    cout << "\t\t\t-------------------------------------------------------" << endl;
    cout << "\t\t\t |   CONSULTA DE USUARIOS                             |" << endl;
    cout << "\t\t\t-------------------------------------------------------" << endl;

    fstream file;
    file.open("Usuarios.txt", ios::in);

    if (!file)
    {
        cout << "\n\t\t\t No hay información de usuarios..." << endl;
        cin.get();
        return;
    }

    string linea;
    bool hayUsuarios = false;
    cout << "\n\tID\tNombre\t\tContrasena" << endl;
    cout << "\t-------------------------------------" << endl;

    while (getline(file, linea))
    {
        istringstream iss(linea);
        int tempId;
        string tempName, tempPass;

        if (iss >> tempId >> tempName >> tempPass)
        {
            hayUsuarios = true;
            cout << "\t" << tempId << "\t" << tempName << "\t\t" << tempPass << endl;
        }
    }

    if (!hayUsuarios)
    {
        cout << "\n\t\t\t No se encontraron usuarios registrados." << endl;
    }

    file.close();
    cout << "\n\t\t\t Presione Enter para continuar...";
    cin.get();
}

void usuarios::menuUsuarios()
{
    int choice;
    do
    {
        system("cls");
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\t |   SISTEMA GESTION DE SEGURIDAD - Catalogos Usuarios |" << endl;
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\t 1. Ingreso Usuarios" << endl;
        cout << "\t\t\t 2. Consulta Usuarios" << endl;
        cout << "\t\t\t 3. Modificacion Usuarios" << endl;
        cout << "\t\t\t 4. Eliminacion Usuarios" << endl;
        cout << "\t\t\t 5. Retornar menu anterior" << endl;
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\tOpcion a escoger:[1/2/3/4/5]" << endl;
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;
        cin.ignore(); // limpiar buffer

        switch (choice)
        {
        case 1:
            agregarUsuarios();
            break;
        case 2:
            consultarUsuarios();
            break;
        case 3:
            modificarUsuarios();
            break;
        case 4:
            eliminarUsuarios();
            break;
        case 5:
            break;
        default:
            cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez.." << endl;
        }
        cin.get();
    } while (choice != 5);
}

bool usuarios::buscar(string user, string passw)
{
    fstream file;
    file.open("Usuarios.txt", ios::in);

    if (!file)
    {
        cout  << "\nNo hay informacion de usuarios..." << endl;
        return false;
    }

    string linea;
    while (getline(file, linea))
    {
        istringstream iss(linea);
        int tempId;
        string tempName, tempPass;

        iss >> tempId >> tempName >> tempPass;

        if (user == tempName && passw == tempPass)
        {
            id = tempId;
            name = tempName;
            pass = tempPass;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
void usuarios::agregarUsuarios()
{
    system("cls");
    cout << "\t\t\t-------------------------------------------------------" << endl;
    cout << "\t\t\t |   INGRESO DE USUARIOS                              |" << endl;
    cout << "\t\t\t-------------------------------------------------------" << endl;

    string nuevoUsuario, nuevaContrasena;
    int nuevoId = 1;

    fstream file("Usuarios.txt", ios::in);
    if (file.is_open())
    {
        string linea;
        while (getline(file, linea))
        {
            istringstream iss(linea);
            int tempId;
            string tempName, tempPass;
            if (iss >> tempId >> tempName >> tempPass)
            {
                if (tempId >= nuevoId)
                {
                    nuevoId = tempId + 1; // Generar id
                }
            }
        }
        file.close();
    }

    cout << "\n\tIngrese Nombre de Usuario: ";
    getline(cin, nuevoUsuario);

    file.open("Usuarios.txt", ios::in);
    bool usuarioExiste = false;
    if (file.is_open())
    {
        string linea;
        while (getline(file, linea))
        {
            istringstream iss(linea);
            int tempId;
            string tempName, tempPass;
            if (iss >> tempId >> tempName >> tempPass)
            {
                if (tempName == nuevoUsuario)
                {
                    usuarioExiste = true;
                    break;
                }
            }
        }
        file.close();
    }

    if (usuarioExiste)
    {
        cout << "\n\t\t\t Error: El usuario ya existe." << endl;
        bitacora auditoria;
        auditoria.insertar(nuevoUsuario, 100, "LOGF", "Intento de registro fallido: usuario existente");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    cout << "\tIngrese Contrasena: ";
    char caracter;
    nuevaContrasena = "";
    caracter = getch();
    while (caracter != 13)
    {
        if (caracter != 8)
        {
            nuevaContrasena.push_back(caracter);
            cout << "*";
        }
        else
        {
            if (nuevaContrasena.length() > 0)
            {
                cout << "\b \b";
                nuevaContrasena = nuevaContrasena.substr(0, nuevaContrasena.length() - 1);
            }
        }
        caracter = getch();
    }
    cout << endl;

    file.open("Usuarios.txt", ios::app);
    if (!file)
    {
        cout << "\n\t\t\t Error al abrir el archivo de usuarios." << endl;
        cin.get();
        return;
    }

    file << nuevoId << " " << nuevoUsuario << " " << nuevaContrasena << endl;
    file.close();

    bitacora auditoria;
    auditoria.insertar(nuevoUsuario, 100, "LOGS", "Usuario registrado exitosamente");

    cout << "\n\t\t\t Usuario registrado con exito. ID: " << nuevoId << endl;
    cout << "\n\t\t\t Presione Enter para continuar...";
    cin.get();
}
void usuarios::modificarUsuarios()
{
    system("cls");
    cout << "\t\t\t-------------------------------------------------------" << endl;
    cout << "\t\t\t |   MODIFICACION DE USUARIOS                         |" << endl;
    cout << "\t\t\t-------------------------------------------------------" << endl;

    string usuarioBuscado;
    cout << "\n\tIngrese Nombre de Usuario a modificar: ";
    getline(cin, usuarioBuscado);

    fstream file("Usuarios.txt", ios::in);
    vector<string> lineas;
    bool encontrado = false;
    int idUsuario = 0;
    string nombreActual, contrasenaActual;
    string linea;

    if (!file)
    {
        cout << "\n\t\t\t Error: No hay información de usuarios." << endl;
        bitacora auditoria;
        auditoria.insertar(usuarioBuscado, 100, "LOGF", "Intento de modificación fallido: archivo no encontrado");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    while (getline(file, linea))
    {
        istringstream iss(linea);
        int tempId;
        string tempName, tempPass;
        if (iss >> tempId >> tempName >> tempPass)
        {
            if (tempName == usuarioBuscado)
            {
                encontrado = true;
                idUsuario = tempId;
                nombreActual = tempName;
                contrasenaActual = tempPass;
            }
        }
        lineas.push_back(linea);
    }
    file.close();

    if (!encontrado)
    {
        cout << "\n\t\t\t Error: El usuario no existe." << endl;
        bitacora auditoria;
        auditoria.insertar(usuarioBuscado, 100, "LOGF", "Intento de modificación fallido: usuario no encontrado");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    cout << "\n\tDatos actuales del usuario:" << endl;
    cout << "\tID: " << idUsuario << endl;
    cout << "\tNombre: " << nombreActual << endl;
    cout << "\tContrasena: " << contrasenaActual << endl;

    string nuevoNombre, nuevaContrasena;
    cout << "\n\tIngrese nuevo Nombre de Usuario (Enter para mantener '" << nombreActual << "'): ";
    getline(cin, nuevoNombre);
    if (nuevoNombre.empty())
    {
        nuevoNombre = nombreActual;
    }

    if (nuevoNombre != nombreActual)
    {
        file.open("Usuarios.txt", ios::in);
        bool nombreExiste = false;
        while (getline(file, linea))
        {
            istringstream iss(linea);
            int tempId;
            string tempName, tempPass;
            if (iss >> tempId >> tempName >> tempPass)
            {
                if (tempName == nuevoNombre)
                {
                    nombreExiste = true;
                    break;
                }
            }
        }
        file.close();

        if (nombreExiste)
        {
            cout << "\n\t\t\t Error: El nuevo nombre de usuario ya existe." << endl;
            bitacora auditoria;
            auditoria.insertar(nuevoNombre, 100, "LOGF", "Intento de modificación fallido: nombre de usuario existente");
            cout << "\n\t\t\t Presione Enter para continuar...";
            cin.get();
            return;
        }
    }

    cout << "\tIngrese nueva Contrasena (Enter para mantener actual): ";
    char caracter;
    nuevaContrasena = "";
    caracter = getch();
    while (caracter != 13) // Enter
    {
        if (caracter != 8) // Retroceso
        {
            nuevaContrasena.push_back(caracter);
            cout << "*";
        }
        else
        {
            if (nuevaContrasena.length() > 0)
            {
                cout << "\b \b";
                nuevaContrasena = nuevaContrasena.substr(0, nuevaContrasena.length() - 1);
            }
        }
        caracter = getch();
    }
    cout << endl;
    if (nuevaContrasena.empty())
    {
        nuevaContrasena = contrasenaActual;
    }

    for (size_t i = 0; i < lineas.size(); i++)
    {
        istringstream iss(lineas[i]);
        int tempId;
        string tempName, tempPass;
        if (iss >> tempId >> tempName >> tempPass && tempName == usuarioBuscado)
        {
            ostringstream oss;
            oss << idUsuario << " " << nuevoNombre << " " << nuevaContrasena;
            lineas[i] = oss.str();
            break;
        }
    }

    file.open("Usuarios.txt", ios::out | ios::trunc);
    if (!file)
    {
        cout << "\n\t\t\t Error al abrir el archivo para escritura." << endl;
        bitacora auditoria;
        auditoria.insertar(usuarioBuscado, 100, "LOGF", "Intento de modificación fallido: error al escribir archivo");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    for (const auto& l : lineas)
    {
        file << l << endl;
    }
    file.close();

    bitacora auditoria;
    auditoria.insertar(nuevoNombre, 100, "LOGS", "Usuario modificado exitosamente");

    cout << "\n\t\t\t Usuario modificado con exito." << endl;
    cout << "\n\t\t\t Presione Enter para continuar...";
    cin.get();
}
void usuarios::eliminarUsuarios()
{
    system("cls");
    cout << "\t\t\t-------------------------------------------------------" << endl;
    cout << "\t\t\t |   ELIMINACION DE USUARIOS                          |" << endl;
    cout << "\t\t\t-------------------------------------------------------" << endl;

    string usuarioBuscado;
    cout << "\n\tIngrese Nombre de Usuario a eliminar: ";
    getline(cin, usuarioBuscado);

    // Abrir archivo para buscar el usuario
    fstream file("Usuarios.txt", ios::in);
    vector<string> lineas;
    bool encontrado = false;
    int idUsuario = 0;
    string nombreActual, contrasenaActual;
    string linea;

    if (!file)
    {
        cout << "\n\t\t\t Error: No hay información de usuarios." << endl;
        bitacora auditoria;
        auditoria.insertar(usuarioBuscado, 100, "LOGF", "Intento de eliminación fallido: archivo no encontrado");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    while (getline(file, linea))
    {
        istringstream iss(linea);
        int tempId;
        string tempName, tempPass;
        if (iss >> tempId >> tempName >> tempPass)
        {
            if (tempName == usuarioBuscado)
            {
                encontrado = true;
                idUsuario = tempId;
                nombreActual = tempName;
                contrasenaActual = tempPass;
                continue;
            }
        }
        lineas.push_back(linea);
    }
    file.close();

    if (!encontrado)
    {
        cout << "\n\t\t\t Error: El usuario no existe." << endl;
        bitacora auditoria;
        auditoria.insertar(usuarioBuscado, 100, "LOGF", "Intento de eliminación fallido: usuario no encontrado");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    // Mostrar datos del usuario a eliminar
    cout << "\n\tUsuario encontrado:" << endl;
    cout << "\tID: " << idUsuario << endl;
    cout << "\tNombre: " << nombreActual << endl;
    cout << "\tContrasena: " << contrasenaActual << endl;

    char confirmacion;
    cout << "\n\t¿Está seguro de eliminar este usuario? (S/N): ";
    confirmacion = toupper(getch());
    cout << confirmacion << endl;

    if (confirmacion != 'S')
    {
        cout << "\n\t\t\t Eliminación cancelada." << endl;
        bitacora auditoria;
        auditoria.insertar(nombreActual, 100, "LOGF", "Eliminación cancelada por el usuario");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    // Escribir las líneas restantes al archivo
    file.open("Usuarios.txt", ios::out | ios::trunc);
    if (!file)
    {
        cout << "\n\t\t\t Error al abrir el archivo para escritura." << endl;
        bitacora auditoria;
        auditoria.insertar(nombreActual, 100, "LOGF", "Intento de eliminación fallido: error al escribir archivo");
        cout << "\n\t\t\t Presione Enter para continuar...";
        cin.get();
        return;
    }

    for (const auto& l : lineas)
    {
        file << l << endl;
    }
    file.close();

    // Registrar en bitácora
    bitacora auditoria;
    auditoria.insertar(nombreActual, 100, "LOGS", "Usuario eliminado exitosamente");

    cout << "\n\t\t\t Usuario eliminado con exito." << endl;
    cout << "\n\t\t\t Presione Enter para continuar...";
    cin.get();
}
string usuarios::getNombre()
{
    return name;
}

void usuarios::setNombre(string nombre)
{
    name = nombre;
}
