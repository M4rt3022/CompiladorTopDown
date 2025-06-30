#ifndef NODO_H_
#define NODO_H_
#include <iostream>
#include <ostream>
#include <string>
#include "LineaTopDown.h"
class Nodo{
	private:
		std::string orden;
		std::string ordenPadre;
		std::string contenido;
		//método para calcular el orden del nodo en base al del padre y si es hijo o no
		void obtenerOrden();
	public:
		//constructores
		Nodo();
		Nodo(const std::string& o, const std::string& oP, const std::string& cont);
		//destructor
		~Nodo();
		//métodos set
		void setOrden(const std::string& o);
		void setOrdenPadre(const std::string& oP);
		void setContenido(const std::string& cont);
		//métodos get
		std::string getOrden(void)const { return orden;}
		std::string getOrdenPadre(void)const { return ordenPadre;}
		std::string getContenido(void) const {return contenido;}
		//sobrecarga operadores
		Nodo& operator=(const Nodo& n);
		bool operator==(const Nodo& n);
		friend std::ostream& operator<< (std::ostream& os, const Nodo& n);
		//metodo para guardar nodo en un string
		void guardarEnString(std::string & s);
};
#endif
