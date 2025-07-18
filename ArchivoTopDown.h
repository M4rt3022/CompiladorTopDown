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
		std::vector<int> ComienzoNodos;
		bool ocurrio_un_error;
		//método interno, guarda donde comienza cada nodo en el vector
		void asignarComienzosNodos();
	public:
		//constructor
		ArchivoTopDown();

		//destructor
		~ArchivoTopDown();

		//métodosGet
		std::string getLinea (const int& numero);

		int getCantidadLineas ();

		//Devuelve solo lo que está escrito en una línea antes del ';'
		void getContenidoLinea (const int& orden,std::string& salida);

		//Devuelve la cantidad de tabuladores de la linea que se encuentra en orden
		int getDentadoLinea(const int& orden);

		bool getError(void)const{return ocurrio_un_error;}

		//método que devuelve el valor de uno de los booleanos de caracteres de una línea
		// 1 si es verdadero, 0 si es falso y -1 si hubo un error
		int getBoolLinea(const int & orden,const char& caracter);

		//devuelve el valor de un ComienzoNodos
		int getComienzoNodo(const int& numero);

		//método que cuenta la cantidad de comienzos de nodos que tiene y lo devuelve
		//	ESTO ES AMBIGUO, DEBE SER CAMBIADO
		int getCantidadNodos();

		//ELIMINAR ESTO LUEGO
		void imprimeComienzosNodos();

		//método aparte para obtener una línea de un archivo y evitar el uso de GetString ya que el mismo elimina '\n'
		void leerLinea(std::ifstream& archivo, std::string& salida);

		//método para leer todo el archivo para almacenar la información en las LineasArchivo
		void leeDesdeArchivo();

};
#endif
