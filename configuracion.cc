#include "configuracion.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ErrorHandler.h"
#include <unordered_map>
// gpt
static const std::unordered_map<std::string, palabrasConfig> mapaPalabras = {
	{"fin_linea:",palabrasConfig::fin_linea},
	{"tabulador:",palabrasConfig::tabulador},
	{"comentario:",palabrasConfig::comentario},
	{"condicion_linea:",palabrasConfig::condicion_linea},
	{"iteracion_linea:",palabrasConfig::iteracion_linea},
	{"formato_salida:",palabrasConfig::formato_salida},
	{"un_solo_topdown:",palabrasConfig::un_solo_topdown},
	{"imprimir_salida_programa:",palabrasConfig::imprimir_salida_programa}
};
void Configuracion::cargaDesdeArchivo(const std::string& nombreArchivo){
	try{
		int cantidadLineas;
		std::ifstream archivo;
		std::string linea;
		std::string palabra;
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
			iss >> palabra;
			auto it = mapaPalabras.find(palabra);
			if(it == mapaPalabras.end()){
				palabraEnum = palabrasConfig::desconocida;
				continue;
			}
			if(it != mapaPalabras.end()){
				palabraEnum = it->second;
			}
			switch(palabraEnum){
				case palabrasConfig::fin_linea:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::tabulador:
					//acá asigno lo que debo hacer
					break;
				case palabrasConfig::comentario:
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
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
// Edita las variables Internas para volver a la configuración por defecto, sin necesidad de un archivo
void Configuracion::restablecerConfig(void){
	finLinea = ";";
	tabulador = "\t";
	comentario = "#";
	condicionLinea = {"si", "if"};
	iteracionLinea = {"repetir", "mientras", "for", "while"};
	formatoSalida = "pdf";
	unSoloTopDown = true;
	imprimirSalidaPrograma = false;
}
// Hace un nuevo archivo de configuración con los datos por defecto
void creaArchivoConfig(void){
	std::ofstream archivo("config");
	// no hacen falta los comentarios, el readme tiene suficiente información para saber que hay en este archvo
	try{
		if(!archivo){
			throw(ErrorHandler(TipoError::ERROR_CONFIGURACION_APERTURA_ARCHIVO));
		}
		archivo << "fin_linea: \";\"\n"; 
		archivo << "tabulador: \"\\t\"\n"; 
		archivo << "comentario: \"#\"\n"; 
		archivo << "condicion_linea: \"si if\"\n"; 
		archivo << "iteracion_linea: \"repetir mientras for while\"\n"; 
		archivo << "formato_salida: \"pdf\"\n"; 
		archivo << "un_solo_topdown: \"true\"\n"; 
		archivo << "imprimir_salida_programa: \"false\"\n"; 
		archivo.close();
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
// recibe una línea y verifica que sea de configuración, que sea válida. retorna orden enum según el caso
int Configuracion::LineaConfigEsCorrecta(const std::string& linea){
	palabrasConfig palabraEnum = palabrasConfig::Linea_sin_proposito;
	std::string palabra;
	std::stringstream iss(linea);
	if(linea.empty()){
		return (static_cast<int>(palabrasConfig::Linea_sin_proposito));
	}
	// extae de la línea, la primer palabra
	iss >> palabra;
	// la busca entre las palabras reservadas para configurar
	auto it = mapaPalabras.find(palabra);
	if(it == mapaPalabras.end()){
		return (static_cast<int>(palabrasConfig::Linea_sin_proposito));
	}
	if(it != mapaPalabras.end()){
		palabraEnum = it->second;
	}
	// según el tipo de configuración, analiza la línea
	switch(palabraEnum){
		case palabrasConfig::fin_linea:
			break;
		case palabrasConfig::tabulador:
			break;
		case palabrasConfig::comentario:
			break;
		case palabrasConfig::condicion_linea:
			break;
		case palabrasConfig::iteracion_linea:
			break;
		case palabrasConfig::formato_salida:
			break;
		case palabrasConfig::un_solo_topdown:
			break;
		case palabrasConfig::imprimir_salida_programa:
			break;
		default:
			return (static_cast<int>(palabrasConfig::Linea_sin_proposito));
			break;
	}
}
// cuenta la cantidad de palabras entre comillas de un string
int cantidadPalabrasEntreComillas(const std::string& s){
	std::string palabra;
	if(s.empty()){
		return -1;
	}
	// cuenta la cantidad de comillas que tiene antes que nada, por si está mal escrita
	
}
