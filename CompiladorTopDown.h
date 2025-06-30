#ifndef COMPILADORTOPDOWN_H_
#define COMPILADORTOPDOWN_H_
#include <iostream>
#include <string>
#include <fstream>
#include "ErrorHandler.h"
#include "ArchivoTopDown.h"
#include "TopDown.h"
class CompiladorTopDown{
	private:
		ArchivoTopDown ArchivoTD;
		Topdown TD;
	public:
		//constructor
		CompiladorTopDown();
		//destructor
		~CompiladorTopDown();
		//método para buscar el ArchivoTD
		void leeArchivoTD();
		//método para buscar el título del TD
		int buscaTituloTP();
		//toma el archivo y busca que todas las lineas luego del título tengan por lo menos 1 tab
		int revisaCorrectoDentado();
		//método para realizar una sola rutina de compilación
		//este es el método que engloba todo
		void compilar();
};
#endif
