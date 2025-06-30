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
	return LineasArchivo.capacity();
}
int ArchivoTopDown::getDentadoLinea(const int& orden){
	try{
		if(orden>LineasArchivo.capacity()){
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
std::string ArchivoTopDown::getContenidoLinea(const int & orden){
	try{
		if(orden > LineasArchivo.capacity())
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
	}
}
