#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "LineaTopDown.h"
#include "ErrorHandler.h"
#include "ArchivoTopDown.h"
ArchivoTopDown::ArchivoTopDown(){
	LineasArchivo.reserve(10);
	std::cout << "ahora el vector cuenta con " << LineasArchivo.capacity() << "lineas guardadas" << std::endl;
	std::cout << "memoria asignada exitosamente" << std::endl;
}
ArchivoTopDown::~ArchivoTopDown(){
	LineasArchivo.clear();
	std::cout << "memoria liberada exitosamente" << std::endl;
}
void ArchivoTopDown::leeDesdeArchivo(){
	int cantidadLineas = 0;
	std::string auxiliar;
	std::ifstream entrada("topdown");
	try{
		if(!entrada){
			throw(ErrorHandler(TipoError::ERROR_LINEA_ABRIR_ARCHIVO));
		}
		std::getline(entrada,auxiliar);
		while(!entrada.eof()){
			cantidadLineas ++;
			std::getline(entrada,auxiliar);
		}
		entrada.close();
		if(cantidadLineas==0){
			throw(ErrorHandler(TipoError::ERROR_LINEA_ARCHIVO_VACÍO));
		}
		LineasArchivo.resize(cantidadLineas);
		std::cout << "ahora el vector cuenta con " << LineasArchivo.capacity() << "lineas guardadas" << std::endl;
	}
	catch(const ErrorHandler& error){
		entrada.close();
		std::cerr << "[ERROR]: " << error.what() << std::endl;
	}
}
std::string ArchivoTopDown::getLinea(const int& numero){
	//acá debería revisar que sea un número válido
	return LineasArchivo[numero].getCaracteres();
}
