#include <string>
#include "Nodo.h"
//método para asignarle el numero al nodo
void Nodo::obtenerOrden(){
	std::string ordenFormateado;
	if(ordenPadre.empty()){
		//significa que es el primer nodo (título o se usó el constructor por defecto)
		orden = '0';
		return;
	}
	orden = ordenPadre + orden;
	return;
} 
//constructor por defecto
Nodo::Nodo():orden(""),ordenPadre(""),contenido(""){};
Nodo::Nodo(const std::string& o, const std::string& oP, const std::string& cont){
	orden = o;
	ordenPadre = oP;
	contenido = cont;
	obtenerOrden();
	return;
}
Nodo::~Nodo(){}
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
//sobrecarga operadores
Nodo& Nodo::operator=(const Nodo& n){
	orden = n.getOrden();
	ordenPadre = n.getOrdenPadre();
	contenido = n.getContenido();
	return *this;
}
