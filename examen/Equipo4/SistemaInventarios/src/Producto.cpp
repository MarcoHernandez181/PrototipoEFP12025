#include "Producto.h"
//constructor por Anthony Suc
Producto::Producto(int _codigo, std::string _nombre,
                   float _precio, int _stock,
                   std::string _tipo) :
    codigo(_codigo), nombre(_nombre), precio(_precio),
    stock(_stock), tipo(_tipo) {}
