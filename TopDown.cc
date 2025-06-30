#include <fstream>
#include <iostream>
#include <string>
#include "ErrorHandler.h"
#include "TopDown.h"
Topdown::Topdown(){
	//reserva para 5 nodos
	nodos.reserve(5);
}
Topdown::~Topdown(){}
void Topdown::guardaTopDown(){
	std::ofstream archivo;
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
		for(int i = 0 ; i < nodos.capacity();i++){
			nodos[i].guardarEnString(auxiliar);
			archivo << auxiliar << std::endl;
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
