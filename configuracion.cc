#include "configuracion.h"
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
	std::string::iterator it;
	int cantidadLineas = 0;
	int cantidadCosasEditadas = 0;
	palabrasConfig tipoConfig;
	try {
		// abrir archivo
		if(!archivo){
			throw( ErrorHandler(TipoError::ERROR_CONFIGURACION_APERTURA_ARCHIVO));
		}
		//contar líneas y leer hasta que se terminen
		cantidadLineas = cantidadLineasArchivo(archivo);
		if(cantidadLineas == 0){
			throw (ErrorHandler(TipoError::ERROR_CONFIGURACION_ARCHIVO_VACÍO));
		}
		for(int i=0;i<cantidadLineas;i++){
			std::getline(archivo,linea);
			tipoConfig = tipoLineaConfig(linea);
			if(tipoConfig == palabrasConfig::Linea_sin_proposito){
				continue;
			}
			if(aplicaConfiguracion(tipoConfig,linea)==0){
				cantidadCosasEditadas++;
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
palabrasConfig Configuracion::tipoLineaConfig(const std::string& linea){
	palabrasConfig palabraEnum = palabrasConfig::Linea_sin_proposito;
	std::string palabra;
	auto it = linea.begin();
	if(linea.empty()){
		return palabrasConfig::Linea_sin_proposito;
	}
	// extae de la línea, la primer palabra
	sacaPalabra(it, linea, palabra, '\"');
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
// increíble que esté usando este método
void Configuracion::sacaPalabra(std::string::const_iterator& desde,const std::string& origen, std::string& destino,const char& caracterFinal){
	destino.clear();
	// salteo espacios en blanco
	while(desde != origen.end() && (*desde == ' '|| *desde == '\t')){
		desde ++;
	}
	// empiezo a copiar cualquier caracter que sea diferente a un espacio o a un \n
	while(desde != origen.end() & (*desde != ' '&& *desde != '\n' && *desde != caracterFinal)){
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
// toma un orden del enum palabrasConfig y edita el parámetro que corresponda, devuelve 0 si sale bien y de lo contrario !=0
int Configuracion::aplicaConfiguracion(palabrasConfig& config, const std::string& linea){
	if((config == palabrasConfig::Linea_sin_proposito)||(linea.empty())){
		return 1;
	}
	switch (config) {
		case (palabrasConfig::fin_linea):
	
	}
}
