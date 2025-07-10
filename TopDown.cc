#include <fstream>
#include <iostream>
#include <string>
#include "ErrorHandler.h"
#include "TopDown.h"

//constructor
Topdown::Topdown(){}

//destructor
Topdown::~Topdown(){}

//método para guardar topdown en un archivo
void Topdown::guardaTopDown(){
	std::ofstream archivo("topdown-formateado");
	std::string auxiliar;
	try{
		if(!archivo){
			//no se pudo abrir archivo
			throw(ErrorHandler(TipoError::ERROR_TOPDOWN_ABRIR_ARCHIVO));
			ocurrio_un_error = true;
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
		ocurrio_un_error = true;
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		if(archivo){
			archivo.close();
		}
		return;
	}
}

//método get para obtener el numero de nodos guardados en topdown
int Topdown::getCantidadNodos(){
	return (static_cast<int>(nodos.size()));
}

//método que guarda un nodo con argumentos en el vector
void Topdown::agregaNodo(const std::string& o, const std::string& cont){
	//tal vez debería revisar algo más acá, no sé
	nodos.emplace_back(o,cont);
	return;
}
