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

		//método para buscar el título del TD, devuelve el numero de línea en donde termina el título, sino, -1
		int buscaTituloTP();

		//toma el archivo y busca que todas las lineas luego del título tengan por lo menos 1 tabulador
		int revisaCorrectoDentado();

		//método que toma desde un número de línea en específico y junta su contenido hasta encontrar un caracter_fin_linea
		//utiliza el orden enviado como referencia y lo modifica
		void juntaContenido(const int & numLinea,std::string& salida);

		//método que cuenta cuantos hijos tiene un nodo y lo devuelve;
		int cuentaHijos(const int&numLinea);

		//método que cuentaHijos y les otorga sus nombres en base a el nombre del padre
		void nombraHijos(const int &numLinea,const std::string& ordenPadre);

		//método para tomar todo lo guardado en topdown y almacenarlo en un archivo de texto formateado
		void guardaEnArchivo();

		//método que engloba todos los métodos anteriores en orden
		void compilar();

};
#endif
