#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ErrorHandler.h"
#include "ArchivoTopDown.h"
ArchivoTopDown::ArchivoTopDown(){
	LineasArchivo.reserve(10);
}
ArchivoTopDown::~ArchivoTopDown(){
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
	}
}
std::string ArchivoTopDown::getLinea(const int& numero){
	//acá debería revisar que sea un número válido
	return LineasArchivo[numero].getCaracteres();
}
