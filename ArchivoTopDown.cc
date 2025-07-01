#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ErrorHandler.h"
#include "ArchivoTopDown.h"
ArchivoTopDown::ArchivoTopDown(){
	ocurrio_un_error = false;
	LineasArchivo.reserve(10);
}
ArchivoTopDown::~ArchivoTopDown(){
}
int ArchivoTopDown::getCantidadLineas(){
	return LineasArchivo.size();
}
int ArchivoTopDown::getDentadoLinea(const int& orden){
	try{
		if( orden > static_cast<int>(LineasArchivo.size())){
			throw(ErrorHandler(TipoError::ERROR_LINEA_INEXISTENTE));
		}
		return (LineasArchivo[orden].getDentado());
	}
	catch(const ErrorHandler& error){
		std::cout << "[ERROR]: " << error.what() << std::endl;
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
		    std::getline(entrada, auxiliar);
		    LineasArchivo[i] = LineaTopDown(auxiliar);
		}

		entrada.close();
	}
	catch (const ErrorHandler& error) {
		entrada.close();
		ocurrio_un_error = true;
	}
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
