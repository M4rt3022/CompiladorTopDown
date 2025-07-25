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
		//método interno, revisa que por lo menos una línea no esté vacía
		void revisaArchivoNoVacio();
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

		//devuelve el valor de un booleano de una línea en el orden indicado
		int getBoolLinea(const int& orden, const LineaTopDown::flag & f);

		bool getError(void)const{return ocurrio_un_error;}

		//devuelve el valor de un ComienzoNodos
		int getComienzoNodo(const int& numero);

		//devuelve la cantidad de comienzosNodos que hay
		int getCantidadComienzosNodos(){return(static_cast<int>(ComienzoNodos.size()));};

		//método que cuenta la cantidad de comienzos de nodos que tiene y lo devuelve
		//	ESTO ES AMBIGUO, DEBE SER CAMBIADO
		int getCantidadNodos();

		//método usado para revisar que una línea esté vacía o no
		int estaVacia(std::string & caracteres);

		//método para leer todo el archivo para almacenar la información en las LineasArchivo
		void leeDesdeArchivo();

};
#endif
