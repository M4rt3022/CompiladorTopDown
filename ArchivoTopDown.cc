#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ErrorHandler.h"
#include "LineaTopDown.h"
#include "ArchivoTopDown.h"

//método interno, guarda donde comienza cada nodo en el vector
void ArchivoTopDown::asignarComienzosNodos(){
	if(getCantidadLineas()==0){
		return;
	}
	int i = 0;
	int dentadoAuxiliar;
	for(;i<getCantidadLineas();i++){
		ComienzoNodos.push_back(i);
		dentadoAuxiliar = LineasArchivo[i].getDentado();
		//salteo lo que es el mismo nodo
		while(LineasArchivo[i].getDentado() == dentadoAuxiliar && 0 == LineasArchivo[i].getValorFlag(LineaTopDown::flag::flag_caracter_fin_linea)){
			i++;
		}
	}
}

//método interno, revisa que por lo menos una línea no esté vacía
//	hice que este método revise que tenga una línea, ya que leeDesdeArchivo elimina automáticamente las líneas vacías
void ArchivoTopDown::revisaArchivoNoVacio(){
	try{
		if(getCantidadLineas()==0){
			throw(ErrorHandler(TipoError::ERROR_LINEA_ARCHIVO_VACÍO));
		}
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		ocurrio_un_error = true;
		return;
	}
}
//constructor
ArchivoTopDown::ArchivoTopDown(){
	ocurrio_un_error = false;
	LineasArchivo.reserve(10);
}

//destructor
ArchivoTopDown::~ArchivoTopDown(){
}

//métodos get
std::string ArchivoTopDown::getLinea(const int& numero){
	//acá debería revisar que sea un número válido
	return LineasArchivo[numero].getCaracteres();
}

int ArchivoTopDown::getCantidadLineas(){
	return (static_cast<int>(LineasArchivo.size()));
}

//Devuelve solo lo que está escrito en una línea antes del ';'
void ArchivoTopDown::getContenidoLinea(const int & orden,std::string& salida){
	try{
		if( orden > static_cast<int>(LineasArchivo.size()) ){
			throw(ErrorHandler(TipoError::ERROR_LINEA_INEXISTENTE));
		}
		LineasArchivo[orden].obtieneContenido(salida);
		return;
	}
	catch(const ErrorHandler& error){
		salida = "";
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}

//Devuelve la cantidad de tabuladores de la linea que se encuentra en orden
int ArchivoTopDown::getDentadoLinea(const int& orden){
	try{
		if( orden > static_cast<int>(LineasArchivo.size())){
			throw(ErrorHandler(TipoError::ERROR_LINEA_INEXISTENTE));
		}
		return (LineasArchivo[orden].getDentado());
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return -1;
	}
}

//devuelve el valor de un booleano de una línea en el orden indicado
int ArchivoTopDown::getBoolLinea(const int& orden, const LineaTopDown::flag & f){
	try{
		if(orden > getCantidadLineas()){
			throw(ErrorHandler(TipoError::ERROR_LINEA_INEXISTENTE));
		}
		return (LineasArchivo[orden].getValorFlag(f));
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return -1;
	}
}

//devuelve el valor de un ComienzoNodo
int ArchivoTopDown::getComienzoNodo(const int& numero){
	if(numero>getCantidadNodos()){
		return -1;
	}
	return(ComienzoNodos[numero]);
}
//método que cuenta la cantidad de comienzos de nodos que tiene y lo devuelve
//	ESTO ES AMBIGUO, DEBE SER CAMBIADO
int ArchivoTopDown::getCantidadNodos(){
	return (static_cast<int>(ComienzoNodos.size()));
}

//método usado para revisar que una línea esté vacía o no
int ArchivoTopDown::estaVacia(std::string & caracteres){
	bool encontro_caracter_diferente = false;
	for (char c : caracteres){
		if( c != '\t' ){
			encontro_caracter_diferente = true;
		}
	}
	if(encontro_caracter_diferente){
		return 0;
	}else{
		return 1;
	}
}

//método para leer todo el archivo para almacenar la información en las LineasArchivo
void ArchivoTopDown::leeDesdeArchivo(){
	int cantidadLineas = 0;
	std::string auxiliar;
	std::ifstream entrada("topdown");
	try {
		if (!entrada) {
			throw(ErrorHandler(TipoError::ERROR_LINEA_ABRIR_ARCHIVO));
		}
		// Contar líneas válidas
		while (std::getline(entrada, auxiliar)) {
			cantidadLineas++;
		}
		if (cantidadLineas == 0) {
			throw(ErrorHandler(TipoError::ERROR_LINEA_ARCHIVO_VACÍO));
		}
		LineasArchivo.resize(cantidadLineas);
		std::cout << "cantidad de líneas reservadas " << cantidadLineas << std::endl;
		// Volver a leer desde el principio
		entrada.clear();
		entrada.seekg(0, entrada.beg);
		for (int i = 0; i < cantidadLineas; ++i) {
			std::getline(entrada,auxiliar);
			//si está vacía, no la guarda
			if(1==estaVacia(auxiliar)){
				std::cout << "esta línea está vacía" <<std::endl;
				continue;
			}
			LineasArchivo[i] = LineaTopDown(auxiliar);
			std::cout << "se guardo una línea" << std::endl;
		}
		//busca donde comienza cada nodo
		asignarComienzosNodos();
		entrada.close();
	}
	catch (const ErrorHandler& error) {
		entrada.close();
		ocurrio_un_error = true;
	}
}
