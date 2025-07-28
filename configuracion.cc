#include "configuracion.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ErrorHandler.h"
#include <unordered_map>
static const std::unordered_map<std::string, palabrasConfig> mapaPalabras = {
	{"caracter_fin_linea",palabrasConfig::caracter_fin_linea},
	{"caracter_tabulador",palabrasConfig::caracter_tabulador},
	{"caracter_comentario",palabrasConfig::caracter_comentario},
	{"condicion_linea",palabrasConfig::condicion_linea},
	{"iteracion_linea",palabrasConfig::iteracion_linea},
	{"formato_salida",palabrasConfig::formato_salida},
	{"agregar_espacios",palabrasConfig::agregar_espacios},
	{"un_solo_topdown",palabrasConfig::un_solo_topdown},
	{"imprimir_salida_programa",palabrasConfig::imprimir_salida_programa}
};
void Configuracion::cargaDesdeArchivo(const std::string& nombreArchivo){
	try{
		int cantidadLineas;
		std::ifstream archivo;
		std::string lineaAuxiliar;
		std::string contenidoABuscar;
		size_t posicion;
		archivo.open(nombreArchivo);
		if(archivo.fail()){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_APERTURA_ARCHIVO));
		}
		while (std::getline(archivo,lineaAuxiliar)){
			cantidadLineas++;
		}
		if(cantidadLineas == 0){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_ARCHIVO_VACÍO));
		}
		archivo.clear();
		archivo.seekg(0,archivo.beg);
		for(int i=0;i<cantidadLineas;i++){
			std::getline(archivo,lineaAuxiliar);
			//si es una línea de comentario o una línea vacía, la ignoro
			if(lineaAuxiliar.empty()){
				continue;
			}
			posicion = lineaAuxiliar.find('#');
			if(posicion != std::string::npos){
				continue;
			}
			//busca cada palabra de configuración en la línea leída
		}
	}
	catch(const ErrorHandler& error){
		std::cout << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
