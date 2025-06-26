#include "LineaTopDown.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
void LineaTopDown::cuentaDentado(){
	bool primerLetra = false;// bandera para marcar cuando encuentre la primer letra de la línea
	int cantidadDentado = 0;
	if (caracteres.empty()){ // si no tiene caracteres, no tiene dentado
		numeroDentado = 0;
		return;
	}
	//se recorre el string en búsqueda de un caracter de dentado, en este caso '\t'
	for (std::string::iterator it = caracteres.begin(); it != caracteres.end()&&primerLetra==false;it++){
		if(*it=='\t'){
			cantidadDentado++;
		}
		primerLetra = true;
	}
	std::cout << "la cantidad de tabuladores es: " << cantidadDentado << std::endl;
	numeroDentado = cantidadDentado;
	return;
}
void LineaTopDown::buscaCaracteresImportantes(){
	//si la línea está vacía, no tiene fin_de_linea
	if(caracteres.empty()){
		caracter_fin_linea = false;
		caracter_nodo_abre = false;
		caracter_nodo_cierra = false;
	}
	//buscará los siguientes caracteeres
	// caracter_fin_linea = ';'
	// caracter_nodo_abre = '{'
	// caracter_nodo_cierra = '}'
	// IMPORTANTE lo único que puede salir mal es que se repita un caracter importante, lanzará excepción en dicho caso
	try{
			
		for(std::string::iterator it = caracteres.begin(); it != caracteres.end(); it++){
			if( *it==';' && ! caracter_fin_linea ){
				caracter_fin_linea = true;
			}else if( *it==';' && caracter_fin_linea ){
				throw (int(ERROR_CARACTER_DOBLE));
			}
			if( *it=='{' && ! caracter_nodo_abre ){
				caracter_nodo_abre = true;
			}else if( *it=='{' && caracter_nodo_abre ){
				throw (int(ERROR_CARACTER_DOBLE));
			}
			if(*it=='}' && ! caracter_nodo_cierra ){
				caracter_nodo_cierra = true;
			}else if( *it=='}' && caracter_nodo_cierra ){
				throw (int(ERROR_CARACTER_DOBLE));
			}
		}
	}
	catch(int e){
		switch (e) {
			case(int(ERROR_CARACTER_DOBLE)):
				std::cerr << "[ERROR] línea " << numeroLinea << ": tiene más de un caracter importante" << std::endl;
		}
	}
	return;
}
void LineaTopDown::setNumero(const int& numero){
	numeroLinea = numero;
	if(numeroLinea < 0){ 
		numeroLinea = 0;
	}
	return;
}
LineaTopDown::LineaTopDown(): numeroLinea(0), numeroDentado(0), caracteres(""), caracter_fin_linea(false), caracter_nodo_abre(false),caracter_nodo_cierra(false){}
LineaTopDown::~LineaTopDown(){
	caracteres.clear();
	return;
}
LineaTopDown::LineaTopDown(const int &numero,const int &dentado,const std::string &carac){
	numeroLinea = numero;
	if(numeroLinea < 0){ 
	numeroLinea = 0;
	}
	numeroDentado = dentado;
	if(numeroDentado< 0){ 
	numeroDentado = 0;
	}
	caracteres = carac;
	cuentaDentado();
	buscaCaracteresImportantes();
	return;
}
LineaTopDown& LineaTopDown::operator=(const LineaTopDown&l){
	numeroLinea = l.numeroLinea;
	numeroDentado = l.numeroDentado;
	caracteres = l.caracteres;
	caracter_fin_linea = l.caracter_fin_linea;
	caracter_nodo_abre = l.caracter_nodo_abre;
	caracter_nodo_cierra = l.caracter_nodo_cierra;
	return *this;
}
std::istream& operator>>(std::istream&is, LineaTopDown&l){
	is >> l.caracteres;
	return is;
}
std::ostream& operator<< (std::ostream& os, const LineaTopDown& l){
	os << l.caracteres;
	return os;
}
void LineaTopDown::leeDesdeArchivo(std::ifstream& archivo){
	try{
		if (!archivo){
			throw (int (ERROR_ABRIR_ARCHIVO));
		}
		std::getline(archivo,caracteres);
		cuentaDentado();
		buscaCaracteresImportantes();
	}
	catch(int e){
		switch (e) {
			case(int(ERROR_ABRIR_ARCHIVO)):
				std::cerr << "[ERROR]: la lectura de archivo falló" << std::endl;
		}
	}
	return;
}
