#include "configuracion.h"
#include <algorithm>
#include <iostream>
#include <fstream>
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
// lee datos del archivo confg y los guarda
void Configuracion::cargaDatosDesdeArchivo(void){
	std::ifstream archivo("config");
	std::string linea;
	std::string caracteres;
	int cantidadLineas = 0;
	palabrasConfig tipoConfig;
	try {
		// abrir archivo
		if(!archivo){
			throw( ErrorHandler(TipoError::ERROR_CONFIGURACION_APERTURA_ARCHIVO));
		}
		//contar líneas y leer hasta que se terminen
		cantidadLineas = cantidadLineasArchivo(archivo);
		if(0==cantidadLineas){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_ARCHIVO_VACÍO));
		}
		archivo.clear();
		archivo.seekg(0,std::ios::beg);
		for(int i=0;i<cantidadLineas;i++){
			std::getline(archivo,linea);
			tipoConfig = tipoLineaConfig(linea);
			if(tipoConfig == palabrasConfig::Linea_sin_proposito){
				continue;
			}
			sacaCaracteresDentroComillas(linea,caracteres);
			if(0!=aplicaConfiguracion(tipoConfig, caracteres)){
				restablecerConfig();
				return;
			}
		}

	} catch (const ErrorHandler& error) {
		std::cerr << "[ERROR]: " << error.what() << " , restableciendo configuración por defecto.\n";
		restablecerConfig();
		return;
	}
}
// Edita las variables Internas para volver a la configuración por defecto, sin necesidad de un archivo
void Configuracion::restablecerConfig(void){
	finLinea = {";"};
	tabulador = {"\t"};
	comentario = {"#"};
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
// recibe una línea y la clasifica según el enum palabrasConfig
palabrasConfig Configuracion::tipoLineaConfig(const std::string& linea){
	palabrasConfig palabraEnum = palabrasConfig::Linea_sin_proposito;
	std::string palabra;
	std::string::const_iterator it = linea.begin();
	if(linea.empty()){
		return palabrasConfig::Linea_sin_proposito;
	}
	// extae de la línea, la primer palabra
	sacaPalabra(it, linea, palabra);
	// la busca entre las palabras reservadas para configurar
	auto itmapa = mapaPalabras.find(palabra);
	if(itmapa == mapaPalabras.end()){
		return palabrasConfig::Linea_sin_proposito;
	}
	if(itmapa != mapaPalabras.end()){
		palabraEnum = itmapa->second;
	}
	if(2!=cuentaComillas(linea)){
		return palabrasConfig::Linea_sin_proposito;
	}
	return palabraEnum;
}
// método simple para sacar una serie de caracteres hasta un espacio en blanco o \n
void Configuracion::sacaPalabra(std::string::const_iterator& desde,const std::string& origen, std::string& destino){
	destino.clear();
	// salteo espacios en blanco
	while(desde != origen.end() && (*desde == ' '|| *desde == '\t')){
		desde ++;
	}
	// empiezo a copiar cualquier caracter que sea diferente a un espacio o a un \n
	while(desde != origen.end() && (*desde != ' '&& *desde != '\n')){
		destino += *desde;
		desde++;
	}
	return;
}
// cuenta la cantidad de comillas que tiene un string, devuelve en que posición encontró a la primer comilla
int Configuracion::cuentaComillas(const std::string& entrada){
	int cantidadComillas = 0;
	auto it = entrada.begin();
	while (it != entrada.end()){
		if (*it=='\"'){
			cantidadComillas++;
		}
		it++;
	}
	return cantidadComillas;
}
// cuenta la cantiad de líneas del archivo
int Configuracion::cantidadLineasArchivo(std::ifstream& archivo){
	int lineas = 0;
	std::string stringAuxiliar;
	if(!archivo){
		return -1;
	}
	while(std::getline(archivo,stringAuxiliar)){
		lineas++;
	}
	archivo.clear();
	archivo.seekg(0,archivo.beg);
	return lineas;
}
// toma una línea de top down y saca todos los caracteres dentro de las comillas
void Configuracion::sacaCaracteresDentroComillas(const std::string& linea, std::string& caracteres){
	auto it = linea.begin();
	caracteres.clear();
	if(2!=cuentaComillas(linea)){
		return;
	}
	it = std::find(it,linea.end(),'\"');
	it++;
	while(*it!='\"'&& it!= linea.end()){
		caracteres += *it;
		it++;
	}
	return;
}
// toma un orden del enum palabrasConfig y edita el parámetro que corresponda, devuelve 0 si sale bien y de lo contrario !=0
int Configuracion::aplicaConfiguracion(palabrasConfig& config, const std::string& caracteresDentrocomillas){
	std::string palabra;
	auto it = caracteresDentrocomillas.begin();
	try{
		switch(config){
			case(palabrasConfig::fin_linea):
				while(it!=caracteresDentrocomillas.end()){
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					finLinea.push_back(palabra); 
				}
				break;
			case(palabrasConfig::tabulador):
				while(it!=caracteresDentrocomillas.end()){
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					tabulador.push_back(palabra); 
				}
				break;
			case(palabrasConfig::comentario):
				while(it!=caracteresDentrocomillas.end()){
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					comentario.push_back(palabra); 
				}
				break;
			case(palabrasConfig::condicion_linea):
				while(it!=caracteresDentrocomillas.end()){
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					condicionLinea.push_back(palabra); 
				}
				break;
			case(palabrasConfig::iteracion_linea):
				while(it!=caracteresDentrocomillas.end()){
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					iteracionLinea.push_back(palabra); 
				}
				break;
			case(palabrasConfig::formato_salida):
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					// ACÁ DEBO VERIFICAR QUE SEA DEL TIPO ADECUADO DE FORMATO -> VA PARA DESPUÉS
					formatoSalida = palabra;
				break;
			case(palabrasConfig::un_solo_topdown):
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					if(palabra == "true"){
						unSoloTopDown = true;
					}else if(palabra == "false"){
						unSoloTopDown = false;
					}else{
						throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_NO_VALIDA));
					}
				break;
			case(palabrasConfig::imprimir_salida_programa):
					sacaPalabra(it, caracteresDentrocomillas, palabra);
					if(palabra == "true"){
						imprimirSalidaPrograma = true;
					}else if(palabra == "false"){
						imprimirSalidaPrograma = false;
					}else{
						throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_NO_VALIDA));
					}
				break;
			default:
				throw(ErrorHandler(TipoError::ERROR_CONFIGURACION_NO_VALIDA));
		}
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << " , restableciendo configuración por defecto.\n"; 
		restablecerConfig();
		return 1;
	}
	return 0;
}
// devuelve true si encuentra la palabra en la variable de configuración y si no, devuelve false;
bool Configuracion::estaEnConfig(const palabrasConfig& conf, const std::string& palabra){
	std::vector<std::string>::const_iterator it;
	if((palabra.empty())||(conf == palabrasConfig::Linea_sin_proposito)){
		return false;
	}
	switch(conf){
		case(palabrasConfig::fin_linea):
			it = finLinea.begin();
			it = std::find(finLinea.begin(),finLinea.end(),palabra);
			if(it!=finLinea.end()){
				return true;
			}
			return false;
		case(palabrasConfig::tabulador):
			it = tabulador.begin();
			it = std::find(tabulador.begin(),tabulador.end(),palabra);
			if(it!=tabulador.end()){
				return true;
			}
			return false;
		case(palabrasConfig::comentario):
			it = comentario.begin();
			it = std::find(comentario.begin(),comentario.end(),palabra);
			if(it!=comentario.end()){
				return true;
			}
			return false;
		case(palabrasConfig::condicion_linea):
			it = condicionLinea.begin();
			it = std::find(condicionLinea.begin(),condicionLinea.end(),palabra);
			if(it!=condicionLinea.end()){
				return true;
			}
			return false;
		case(palabrasConfig::iteracion_linea):
			it = iteracionLinea.begin();
			it = std::find(iteracionLinea.begin(),iteracionLinea.end(),palabra);
			if(it!=iteracionLinea.end()){
				return true;
			}
			return false;
		default:
			//cualquier otra cosa puede ser leída y comparada manualmente
			return false;
	}
}
