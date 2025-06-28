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
	LineasArchivo.clear();
}
void ArchivoTopDown::leeDesdeArchivo(){
	int cantidadLineas = 0;
	std::string auxiliar;
	std::ifstream entrada("topdown");
	try{
		if(!entrada){
			throw(ErrorHandler(TipoError::ERROR_LINEA_ABRIR_ARCHIVO));
		}
		entrada.seekg(0,entrada.beg);
		std::getline(entrada,auxiliar);
		while(!entrada.eof()){
			cantidadLineas ++;
			std::getline(entrada,auxiliar);
		}
		entrada.clear();
		if(cantidadLineas==0){
			throw(ErrorHandler(TipoError::ERROR_LINEA_ARCHIVO_VACÍO));
		}
		LineasArchivo.resize(cantidadLineas);
		entrada.seekg(0,entrada.beg);
		for(int i = 0; i < cantidadLineas ;i++){
			LineasArchivo.emplace_back(auxiliar);
		}
		entrada.close();
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
