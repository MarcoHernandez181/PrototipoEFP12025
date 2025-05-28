//Implementacion Marco H. 03/04/2025
#ifndef PRODUCTO_H
#define PRODUCTO_H
#include "Bitacora.h"
#include <string>
// cambios realizados para el guardado de productos por Anthony Suc
class Producto {
public:
    int codigo;
    std::string nombre;
    float precio;
    int stock;
    std::string tipo;

    Producto(int _codigo = 0, std::string _nombre = "",
             float _precio = 0.0f, int _stock = 0,
             std::string _tipo = "");

    // Getters constantes
    int getCodigo() const { return codigo; }
    std::string getNombre() const { return nombre; }
    float getPrecio() const { return precio; }
    int getStock() const { return stock; }
    std::string getTipo() const { return tipo; }
};

#endif
