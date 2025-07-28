#include "configuracion.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ErrorHandler.h"
void Configuracion::cargaDesdeArchivo(const std::string& nombreArchivo){
	try{
		std::ifstream archivo;
		archivo.open(nombreArchivo);
		if(archivo.fail()){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_APERTURA_ARCHIVO));
		}

	}
	catch(const ErrorHandler& error){
		std::cout << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
