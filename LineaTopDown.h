#ifndef LINEATOPDOWN_H_
#define LINEATOPDOWN_H_
#include <iostream>
#include <fstream>
#include <string>
#include "ErrorHandler.h"	//clase personalizada para manejar los errores en el programa
class LineaTopDown{
	private:
		int numeroDentado;
		std::string caracteres;
		bool caracter_fin_linea;
		bool linea_vacía;	//si la línea no tiene otro caracter que no sea '\n o \t', está vacía
		// Método interno que cuenta el dentado de la línea, se fija si está vacía o no, y modifica caracteres importantes
		void analizaSintaxis();
	public:
		//constructores
		LineaTopDown();
		LineaTopDown(const std::string &carac);
		~LineaTopDown();

		//métodos gets
		int getDentado(void) const {return numeroDentado;}
		std::string getCaracteres(void) const {return caracteres;}
		bool getFinLinea(void)const{return caracter_fin_linea;}
		bool getLineaVacia(void)const{return linea_vacía;}

		//devuelve el contenido de la línea antes de un caracter importante, si está bien escrita
		void obtieneContenido(std::string& salida);

		//sobrecarga operadores
		LineaTopDown& operator= (const LineaTopDown& l);
		friend std::ostream& operator<< (std::ostream& os, const LineaTopDown& l);
		friend std::istream& operator>> (std::istream& is, LineaTopDown&l);
};
#endif
