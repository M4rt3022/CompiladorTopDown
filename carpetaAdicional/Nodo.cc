#include <iostream>
#include <string>
#include "LineaTopDown.h"
#include "Nodo.h"
//constructor por defecto
Nodo::Nodo():orden(""),ordenPadre(""),contenido(""){};
Nodo::Nodo(const std::string& o, const std::string& oP, const std::string& cont){
	orden = o;
	ordenPadre = oP;
	contenido = cont;
	return;
}
//falta implementación destructor
//métodos set
void Nodo::setOrden(const std::string& o){
	orden = o;
	return;
}
void Nodo::setOrdenPadre(const std::string& oP){
	ordenPadre = oP;
	return;
}
void Nodo::setContenido(const std::string& cont){
	contenido = cont;
	return ;
}

