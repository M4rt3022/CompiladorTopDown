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
	for(std::string::iterator it = caracteres.begin(); it != caracteres.end(); it++){
		if( *it==';'){
			caracter_fin_linea = true;
		}
		if( *it=='{'){
			caracter_nodo_abre = true;
		}
		if(*it=='}'){
			caracter_nodo_cierra = true;
		}
	}
	return;
}
void LineaTopDown::revisaCorrectaSintaxis(){
	//primero se fija si tiene algo que leer
	if(caracteres.empty()){
		return;
	}
	//si no tiene ningún caracter importante, no hay nada más que analizar
	if((caracter_fin_linea||caracter_nodo_abre||caracter_nodo_cierra)){}
	//si tiene más de un caracter importante, está mal escrita
	if((caracter_fin_linea&&caracter_nodo_abre)||(caracter_fin_linea&&caracter_nodo_cierra)||(caracter_nodo_abre&&caracter_nodo_cierra)){
		throw(int(ERROR_CARACTER_DOBLE));
		return;
	}
	//si la línea tiene el caracter_fin_linea y no es el último, no está bien escrita la línea
	if(caracter_fin_linea&&caracteres.back()!=';'){
		throw(int(ERROR_FIN_LINEA));
		return;
	}
	//si la línea tiene el caracter_nodo_abre y no es el último, no está bien escrita la línea
	if(caracter_nodo_abre&&caracteres.back()!='{'){
		throw(int(ERROR_NODO_ABRE));
		return;
	}
	//si la línea tiene el caracter_nodo_cierra y no es el último, no está bien escrita la línea
	if(caracter_nodo_cierra&&caracteres.back()!='}'){
		throw(int(ERROR_NODO_CIERRA));
		return;
	}
}
LineaTopDown::LineaTopDown():numeroDentado(0), caracteres(""), caracter_fin_linea(false), caracter_nodo_abre(false),caracter_nodo_cierra(false){}
LineaTopDown::~LineaTopDown(){
	caracteres.clear();
	return;
}
LineaTopDown::LineaTopDown(const int &dentado,const std::string &carac){
	numeroDentado = dentado;
	if(numeroDentado< 0){ 
	numeroDentado = 0;
	}
	caracteres = carac;
	return;
}
LineaTopDown& LineaTopDown::operator=(const LineaTopDown&l){
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
