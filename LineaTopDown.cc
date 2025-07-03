#include "LineaTopDown.h"
#include <iostream>
#include <istream>
#include <string>
#include "ErrorHandler.h" // clase personalizada para facilitar el manejo de excepciones en el programa
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
	numeroDentado = cantidadDentado;
	return;
}
void LineaTopDown::buscaCaracteresImportantes(){
	//si la línea está vacía, no tiene fin_de_linea ni caracter_nodo_abre ni caracter_nodo_cierra
	if(caracteres.empty()){
		caracter_fin_linea = false;
		caracter_nodo_abre = false;
		caracter_nodo_cierra = false;
		return;
	}
	//buscará los siguientes caracteeres
	// caracter_fin_linea = ';'
	// caracter_nodo_abre = '{'
	// caracter_nodo_cierra = '}'
	try{
		for (char c : caracteres) {
			if((c == ';')&&(caracter_fin_linea == false)){
				caracter_fin_linea = true;
			}else if((c==';')&&(caracter_fin_linea == true)){
				linea_bien_escrita = false;
				throw(ErrorHandler(TipoError::ERROR_LINEA_CARAC_DOBLE));
			}
			if((c == '{')&&(caracter_nodo_abre == false)){
				caracter_fin_linea = true;
			}else if((c == '{')&&(caracter_nodo_abre == true)){
				linea_bien_escrita = false;
				throw(ErrorHandler(TipoError::ERROR_LINEA_CARAC_DOBLE));
			}
			if((c == '}')&&(caracter_nodo_cierra== false)){
				caracter_fin_linea = true;
			}else if((c == '}')&&(caracter_nodo_cierra == true)){
				linea_bien_escrita = false;
				throw(ErrorHandler(TipoError::ERROR_LINEA_CARAC_DOBLE));
			}
		}
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return;
	}
	return;
}
void LineaTopDown::analizaSintaxis(){
	int booleanosActivos = caracter_fin_linea + caracter_nodo_abre + caracter_nodo_cierra;
	//primero se fija si tiene algo que leer
	if(caracteres.empty()){
		return;
	}
	cuentaDentado();
	buscaCaracteresImportantes();
	//si no tiene ningún caracter importante, no hay nada más que analizar
	if(booleanosActivos == 0){
		return;
	}
	try{
		//si tiene más de un caracter importante, está mal escrita
		if(booleanosActivos>1){
			linea_bien_escrita = false;
			throw(ErrorHandler(TipoError::ERROR_LINEA_CARAC_DOBLE));
			return;
		}
		//si la línea tiene el caracter_fin_linea y no es el último, no está bien escrita la línea
		if(caracter_fin_linea&&caracteres.back()!=';'){
			linea_bien_escrita = false;
			throw(ErrorHandler(TipoError::ERROR_LINEA_FIN_LINEA));
			return;
		}
		//si la línea tiene el caracter_nodo_abre y no es el último, no está bien escrita la línea
		if(caracter_nodo_abre&&caracteres.back()!='{'){
			linea_bien_escrita = false;
			throw(ErrorHandler(TipoError::ERROR_LINEA_CARAC_DOBLE));
			return;
		}
		//si la línea tiene el caracter_nodo_cierra y no es el último, no está bien escrita la línea
		if(caracter_nodo_cierra&&caracteres.back()!='}'){
			linea_bien_escrita = false;
			throw(ErrorHandler(TipoError::ERROR_LINEA_NODO_CIERRA));
			return;
		}
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
LineaTopDown::LineaTopDown():numeroDentado(0), caracteres(""), caracter_fin_linea(false), caracter_nodo_abre(false),
	caracter_nodo_cierra(false),linea_bien_escrita(true){
}
LineaTopDown::~LineaTopDown(){
}
LineaTopDown::LineaTopDown(const std::string& carac){
	caracteres = carac;
	caracter_fin_linea = false;
	caracter_nodo_abre = false;
	caracter_nodo_cierra = false;
	linea_bien_escrita = true;
	analizaSintaxis();
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
//método que devuelve un string de lo que tiene la línea antes de un caracter importante, si está bien escrita
void LineaTopDown::obtieneContenido(std::string& salida){
	try{
		if(!linea_bien_escrita){
			throw(ErrorHandler(TipoError::ERROR_LINEA_MAL_ESCRITA));
		}
		std::string::const_iterator it = caracteres.begin();
		while(it != caracteres.end() && ((*it) == ' ' || (*it) == '\t' )) ++it; //método zabalero para llegar a la parte con palabras de un string
		for(;it != caracteres.end() && (*it) != ';' && (*it) != '{' && (*it) != '}'; it++){
			salida += *it;
			if((*it)=='\n'){
				break;
			}
		}
		return;
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return;
	}
}
