#ifndef NODO_H_
#define NODO_H_
#include <iostream>
#include <ostream>
#include <string>
#include "LineaTopDown.h"
class Nodo{
	private:
		std::string orden;
		std::string contenido;
	public:
		//constructores
		Nodo();
		Nodo(const std::string& o, const std::string& cont);

		//destructor
		~Nodo();

		//métodos set
		void setOrden(const std::string& o);
		void setOrdenPadre(const std::string& oP);
		void setContenido(const std::string& cont);

		//métodos get
		std::string getOrden(void)const { return orden;}
		std::string getContenido(void) const {return contenido;}

		//metodo para guardar nodo en un string
		void guardarEnString(std::string & s);

		//sobrecarga operadores
		Nodo& operator=(const Nodo& n);
		bool operator==(const Nodo& n);
		friend std::ostream& operator<< (std::ostream& os, const Nodo& n);

};
#endif
