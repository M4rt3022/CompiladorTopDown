#include "LineaTopDown.h"
#include <iostream>
#include <istream>
#include <string>
#include "ErrorHandler.h" // clase personalizada para facilitar el manejo de excepciones en el programa

//método interno para contar la cantidad de caracteres de dentado que hay
void LineaTopDown::cuentaDentado(){
	int cantidadDentado = 0;
	if (caracteres.empty()){ // si no tiene caracteres, no tiene dentado
		numeroDentado = 0;
		return;
	}
	//se recorre el string en búsqueda de un caracter de dentado, en este caso '\t'
	for (std::string::iterator it = caracteres.begin(); it != caracteres.end() && ((*it)==' '||(*it)=='\t');it++){
		cantidadDentado++;
	}
	numeroDentado = cantidadDentado;
	return;
}

//método interno para revisar si la línea almacenada tiene caracteres importantes
void LineaTopDown::buscaCaracteresImportantes(){
	//si la línea está vacía, no tiene ningún caracterImportante
	if(caracteres.empty()){
		caracter_fin_linea = false;
		linea_vacía = true;
		return;
	}
	//buscará los siguientes caracteeres, si encuentra uno repetido, lanza una excepción, actualiza linea_vacía
	// caracter_fin_linea = ';'
	try{
		for (char c : caracteres) {
			if((c == ';')&&(caracter_fin_linea == false)){
				caracter_fin_linea = true;
			}else if((c==';')&&(caracter_fin_linea == true)){
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

//método interno que cuentaDentado, buscaCaracteresImportantes y se fija si tiene caracteres dobles o están mal escritos en la línea
void LineaTopDown::analizaSintaxis(){
	//primero se fija si tiene algo que leer
	if(caracteres.empty()){
		return;
	}
	cuentaDentado();
	buscaCaracteresImportantes();
}

//constructores
LineaTopDown::LineaTopDown():numeroDentado(0), caracteres(""), caracter_fin_linea(false), linea_vacía(true){};
LineaTopDown::LineaTopDown(const std::string& carac){
	caracteres = carac;
	caracter_fin_linea = false;
	analizaSintaxis();
	return;
}

//destructor
LineaTopDown::~LineaTopDown(){
}

//método que devuelve un string de lo que tiene la línea antes de un caracter importante, si está bien escrita
void LineaTopDown::obtieneContenido(std::string& salida){
	try{
		std::string::const_iterator it = caracteres.begin();
		while(it != caracteres.end() && ((*it) == ' ' || (*it) == '\t' )) ++it;
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

//sobrecarga operadores
LineaTopDown& LineaTopDown::operator=(const LineaTopDown&l){
	numeroDentado = l.numeroDentado;
	caracteres = l.caracteres;
	caracter_fin_linea = l.caracter_fin_linea;
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
