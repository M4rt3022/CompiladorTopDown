#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ErrorHandler.h"
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
		while(LineasArchivo[i].getDentado() == dentadoAuxiliar && 0 == LineasArchivo[i].getFinLinea()){
			i++;
		}
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

//método que devuelve el valor de uno de los 3 booleanos de caracteres de una línea
// 1 si es verdadero, 0 si es falso y -1 si hubo un error
int ArchivoTopDown::getBoolLinea(const int& orden, const char& caracter){
	try{
		if( orden > static_cast<int>(LineasArchivo.size()) ){
			throw(ErrorHandler(TipoError::ERROR_LINEA_INEXISTENTE));
		}
		//busca que bool debe retornar y lo devuelve 
		if(caracter == ';'){
			return (static_cast<int>(LineasArchivo[orden].getFinLinea()));
		}
		if(caracter == '{'){
			return (static_cast<int>(LineasArchivo[orden].getNodoAbre()));
		}
		if(caracter == '}'){
			return (static_cast<int>(LineasArchivo[orden].getNodoCierra()));
		}
		throw(ErrorHandler(TipoError::ERROR_LINEA_BOOL_INEXISTENTE));
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
int ArchivoTopDown::getCantidadNodos(){
	return (static_cast<int>(ComienzoNodos.size()));
}

//ELIMINAR ESTO LUEGO
void ArchivoTopDown::imprimeComienzosNodos(){
	int cantidad = static_cast<int>(ComienzoNodos.size());
	for(int i = 0;i < cantidad; i++){
		std::cout << ComienzoNodos[i] << std::endl;
	}
	return;
}

//método aparte para obtener una línea de un archivo y evitar el uso de GetString ya que el mismo elimina '\n'
void ArchivoTopDown::leerLinea(std::ifstream& archivo, std::string& salida){
	if(!archivo){
		return;
	}
	salida = "";
	char c;
	archivo.get(c);
	while(!archivo.eof() && c != '\n'){
		salida += c;
		archivo.get(c);
	}
	if(c == '\n'){
		salida += c;
		return;
	}
	return;
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
		// Volver a leer desde el principio
		entrada.clear();
		entrada.seekg(0, entrada.beg);
		for (int i = 0; i < cantidadLineas; ++i) {
			leerLinea(entrada, auxiliar);
			LineasArchivo[i] = LineaTopDown(auxiliar);
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
