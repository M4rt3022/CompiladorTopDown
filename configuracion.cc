#include "configuracion.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
	{"un_solo_topdown",palabrasConfig::un_solo_topdown},
	{"imprimir_salida_programa",palabrasConfig::imprimir_salida_programa}
};
void Configuracion::cargaDesdeArchivo(const std::string& nombreArchivo){
	try{
		int cantidadLineas;
		std::ifstream archivo;
		std::string linea;
		std::string palabraABuscar;
		std::istringstream iss;
		size_t posicion;
		palabrasConfig palabraEnum = palabrasConfig::desconocida;
		archivo.open(nombreArchivo);
		if(archivo.fail()){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_APERTURA_ARCHIVO));
		}
		while (std::getline(archivo,linea)){
			cantidadLineas++;
		}
		if(cantidadLineas == 0){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_ARCHIVO_VACÍO));
		}
		archivo.clear();
		archivo.seekg(0,archivo.beg);
		for(int i=0;i<cantidadLineas;i++){
			std::getline(archivo,linea);
			//si es una línea de comentario o una línea vacía, la ignoro
			if(linea.empty()){
				continue;
			}
			posicion = linea.find('#');
			if(posicion != std::string::npos){
				continue;
			}
			//extrae una línea, extrae la primer palabra y la busca en mapaPalabras
			iss.str(linea);
			iss >> palabraABuscar;
			auto it = mapaPalabras.find(palabraABuscar);
			if(it != mapaPalabras.end()){
				palabraEnum = it->second;
			}
			switch(palabraEnum){
				case palabrasConfig::caracter_fin_linea:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::caracter_tabulador:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::caracter_comentario:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::condicion_linea:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::iteracion_linea:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::formato_salida:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::un_solo_topdown:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::imprimir_salida_programa:
					//acá asigno lo que debo hacer
					break;
				default:
					break;
			}
		}
	}
	catch(const ErrorHandler& error){
		std::cout << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
