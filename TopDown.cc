#include <fstream>
#include <iostream>
#include <string>
#include "ErrorHandler.h"
#include "TopDown.h"
Topdown::Topdown(){}
Topdown::~Topdown(){}
void Topdown::guardaTopDown(){
	std::ofstream archivo("topdown-formateado");
	std::string auxiliar;
	try{
		if(!archivo){
			//no se pudo abrir archivo
			throw(ErrorHandler(TipoError::ERROR_TOPDOWN_ABRIR_ARCHIVO));
		}
		if(nodos.empty()){
			//no hay nada que guardar
			throw(ErrorHandler(TipoError::ERROR_TOPDOWN_ARCHIVO_VACÍO));
		}
		for(int i = 0 ; i < getCantidadNodos() ;i++){
			auxiliar = "";
			nodos[i].guardarEnString(auxiliar);
			archivo << auxiliar << '\n';
		}
		archivo.close();
	}catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		if(archivo){
			archivo.close();
		}
		return;
	}
}
void Topdown::agregaNodo(const std::string& o, const std::string& cont){
	//tal vez debería revisar algo más acá, no sé
	nodos.emplace_back(o,cont);
	return;
}
int Topdown::getCantidadNodos(){
	return (static_cast<int>(nodos.size()));
}
