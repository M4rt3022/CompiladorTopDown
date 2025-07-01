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
		ArchivoTopDown archivoTD;
		Topdown topdown;
	public:
		//constructor
		CompiladorTopDown();
		//destructor
		~CompiladorTopDown();
		//método para buscar el ArchivoTD
		void leeArchivoTD();
		//método para buscar el título del TD
		int buscaTituloTP();
		//toma el archivo y busca que todas las lineas luego del título tengan por lo menos 1 tabulador
		int revisaCorrectoDentado();
		//método para generar todos los nodos automáticamente y guardarlos en el topdown
		int generaNodos();
		//método para tomar todo lo guardado en topdown y almacenarlo en un archivo de texto formateado
		void guardaEnArchivo();
		//método que engloba todos los métodos anteriores en orden
		void compilar();
};
#endif
