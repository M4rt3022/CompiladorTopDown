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
		bool caracter_fin_linea;	// representa el caracter hasta donde se considerarán los caracteres útiles de un nodo
		bool iteracion_en_linea;	// marca que el contenido de la línea tendrá propiedades de una iteración en el topdown
		bool condicion_en_linea;	// marca que el contenido de la línea tendrá propiedades de una condición en el topdown
		bool linea_vacía;		// si la línea no tiene otro caracter que no sea '\n o \t', está vacía
		void analizaSintaxis();		// Método interno que cuenta el dentado de la línea, se fija si está vacía o no, y modifica caracteres importantes

	public:
		enum class flag{
			flag_caracter_fin_linea,
			flag_iteracion_en_linea,
			flag_condicion_en_linea,
			flag_linea_vacía
		};
		//constructores
		LineaTopDown();
		LineaTopDown(const std::string &carac);
		~LineaTopDown();

		//métodos gets
		int getDentado(void) const {return numeroDentado;}
		std::string getCaracteres(void) const {return caracteres;}
		bool getValorFlag(const flag& f);

		//devuelve el contenido de la línea antes de un caracter importante, si está bien escrita
		void obtieneContenido(std::string& salida);

		//sobrecarga operadores
		LineaTopDown& operator= (const LineaTopDown& l);
		friend std::ostream& operator<< (std::ostream& os, const LineaTopDown& l);
		friend std::istream& operator>> (std::istream& is, LineaTopDown&l);
};
#endif
