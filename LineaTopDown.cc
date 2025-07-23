#include "LineaTopDown.h"
#include <iostream>
#include <istream>
#include <string>
#include "ErrorHandler.h" // clase personalizada para facilitar el manejo de excepciones en el programa

// Método interno que cuenta el dentado de la línea y modifica caracteres importantes
void LineaTopDown::analizaSintaxis(){
	//primero se fija si tiene algo que leer
	if(caracteres.empty()){
		numeroDentado = 0;
		caracter_fin_linea = false;
		iteracion_en_linea = false;
		condicion_en_linea = false;
		return;
	}
	//	cuenta el dentado de la línea y lo almacena
	int cantidadDentado = 0;
	//se recorre el string en búsqueda de un caracter de dentado, en este caso '\t'
	for (std::string::iterator it = caracteres.begin(); it != caracteres.end() && ((*it)==' '||(*it)=='\t');it++){
		cantidadDentado++;
	}
	numeroDentado = cantidadDentado;
	//	luego se fija que no tenga ningún caracter importante repetido
	//	debe abarcar que no encuentre repetido ni caracter_fin_linea ni iteracion_en_linea ni condicion_en_linea
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
}

//constructores
LineaTopDown::LineaTopDown():numeroDentado(0), caracteres(""), caracter_fin_linea(false), iteracion_en_linea(false), condicion_en_linea(false){};
LineaTopDown::LineaTopDown(const std::string& carac){
	caracteres = carac;
	caracter_fin_linea = false;
	iteracion_en_linea = false;
	condicion_en_linea = false;
	analizaSintaxis();
	return;
}

//destructor
LineaTopDown::~LineaTopDown(){
}

//devuelve el valor de algun flag de la línea
bool LineaTopDown::getValorFlag(const flag& f){
	try{
		switch(f){
			case flag::flag_caracter_fin_linea:	return (static_cast<int>(caracter_fin_linea));

			case flag::flag_iteracion_en_linea:	return (static_cast<int>(iteracion_en_linea));

			case flag::flag_condicion_en_linea:	return (static_cast<int>(condicion_en_linea));

			default:	throw(ErrorHandler(TipoError::ERROR_LINEA_BOOL_INEXISTENTE));

		}
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << std::endl;
		return false;
	}
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
	iteracion_en_linea = l.iteracion_en_linea;
	condicion_en_linea = l.condicion_en_linea;
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
