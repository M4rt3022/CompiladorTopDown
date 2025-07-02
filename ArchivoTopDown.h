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
		bool ocurrio_un_error;
	public:
		//constructor
		ArchivoTopDown();
		//destructor
		~ArchivoTopDown();
		//métodosGet
		std::string getLinea (const int& numero);
		int getCantidadLineas ();
		bool getError(void)const{return ocurrio_un_error;}
		//método que llama a getContenido y lo devuelve
		void getContenidoLinea (const int& orden,std::string& salida);
		//Devuelve la cantidad de tabuladores de la linea que se encuentra en orden
		int getDentadoLinea(const int& orden);
		//método para leer todo el archivo para almacenar la información en las LineasArchivo
		void leeDesdeArchivo();
		//método que devuelve el valor de uno de los 3 booleanos de caracteres de una línea
		// 1 si es verdadero, 0 si es falso y -1 si hubo un error
		int getBoolLinea(const int & orden,const char& caracter);
};
#endif
