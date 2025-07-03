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
ArchivoTopDown::ArchivoTopDown(){
	ocurrio_un_error = false;
	LineasArchivo.reserve(10);
}
ArchivoTopDown::~ArchivoTopDown(){
}
int ArchivoTopDown::getCantidadLineas(){
	return (static_cast<int>(LineasArchivo.size()));
}
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
		std::cout << "archivo leído, ahora se buscarán los comienzos de cada nodo" << std::endl;
		//busca donde comienza cada nodo
		asignarComienzosNodos();
		entrada.close();
	}
	catch (const ErrorHandler& error) {
		entrada.close();
		ocurrio_un_error = true;
	}
}
void ArchivoTopDown::imprimeComienzosNodos(){
	int cantidad = static_cast<int>(ComienzoNodos.size());
	std::cout << "se enunciarán las posiciones de líneas donde comienzan cada nodo en el archivo" << std::endl;
	for(int i = 0;i < cantidad; i++){
		std::cout << ComienzoNodos[i] << std::endl;
	}
	return;
}
std::string ArchivoTopDown::getLinea(const int& numero){
	//acá debería revisar que sea un número válido
	return LineasArchivo[numero].getCaracteres();
}
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
