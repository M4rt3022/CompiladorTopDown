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
		ArchivoTopDown(const std::ifstream& archivo);
		//métodosGet
		void getLinea (const int& numero);
		//método set
		void setLinea (const int& numero);
		//sobrecarga operador >> para leer todo un archivo y sus líneas
		friend std::ifstream& operator>> (const std::ifstream& entrada,const ArchivoTopDown& archivo);
};
#endif
