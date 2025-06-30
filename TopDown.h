#ifndef TOPDOWN_H_
#define TOPDOWN_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ErrorHandler.h"
#include "Nodo.h"
class Topdown{
	private:
		std::vector<Nodo> nodos;
	public:
		//constructor
		Topdown();
		//destructor
		~Topdown();
		//metodo para guardar topdown en un archivo
		void guardaTopDown();
};
#endif
