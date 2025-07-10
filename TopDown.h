#ifndef TOPDOWN_H_
#define TOPDOWN_H_
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "ErrorHandler.h"
#include "Nodo.h"
class Topdown{
	private:
		std::vector<Nodo> nodos;
		bool ocurrio_un_error;
	public:
		//constructor
		Topdown();

		//destructor
		~Topdown();

		//método get
		bool getError(void){return ocurrio_un_error;}

		//metodo para guardar topdown en un archivo
		void guardaTopDown();

		//método get para obtener el numero de nodos guardados en topdown
		int getCantidadNodos();

		//método que guarda un nodo con argumentos en el vector
		void agregaNodo(const std::string& o, const std::string& cont);
};
#endif
