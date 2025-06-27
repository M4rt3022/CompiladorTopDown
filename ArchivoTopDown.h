#ifndef ARCHIVOTOPDOWN_H_
#define ARCHIVOTOPDOWN_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "LineaTopDown.h"
#include "ErrorHandler.h"
class ArchivoTopDown{
	private:
		std::vector<LineaTopDown> LineasArchivo;
	public:
		//constructor
		ArchivoTopDown();
		//destructor
		~ArchivoTopDown();
		//métodosGet
		std::string getLinea (const int& numero);
		//método para leer todo el archivo para almacenar la información en las LineasArchivo
		void leeDesdeArchivo();
};
#endif
