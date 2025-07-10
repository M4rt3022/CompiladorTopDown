#include <string>
#include "Nodo.h"
//constructores
Nodo::Nodo():orden(""),contenido(""){};
Nodo::Nodo(const std::string& o, const std::string& cont){
	orden = o;
	contenido = cont;
	return;
}

//destructor
Nodo::~Nodo(){}

//métodos set
void Nodo::setOrden(const std::string& o){
	orden = o;
	return;
}
void Nodo::setContenido(const std::string& cont){
	contenido = cont;
	return ;
}

//método para guardar nodo en un string
void Nodo::guardarEnString(std::string & s){
	s += std::string("orden(") + getOrden() + std::string(")") + std::string("contenido(") + getContenido() + std::string(");") ;
}

//sobrecarga operadores
Nodo& Nodo::operator=(const Nodo& n){
	orden = n.getOrden();
	contenido = n.getContenido();
	return *this;
}
bool Nodo::operator==(const Nodo& n){
	if((orden==n.orden)&&(contenido==n.contenido)){
		return true;
	}
	return false;
}
std::ostream& operator<< (std::ostream& os, const Nodo& n){
	os << "orden(" << n.getOrden() << ")"
	<< "contenido(" << n.getContenido() << ");";
	return os;
}
