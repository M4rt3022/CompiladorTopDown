#include <fstream>
#include <iostream>
#include <string>
#include "ErrorHandler.h"
#include "TopDown.h"
Topdown::Topdown(){}
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
		for(int i = 0 ; i < nodos.size() ;i++){
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
int Topdown::devuelvePosicionNodo(const std::string& orden){
	int ordenEnVector;
	for(ordenEnVector = 0; ordenEnVector < nodos.size();ordenEnVector++){
		if(nodos[ordenEnVector].getOrden() == orden){
			return ordenEnVector;
		}
	}
	return -1;
}
void Topdown::agregaNodo(const std::string& o, const std::string& oP, const std::string& cont){
	//tal vez debería revisar algo más acá, no sé
	nodos.emplace_back(o,oP,cont);
	return;
}
