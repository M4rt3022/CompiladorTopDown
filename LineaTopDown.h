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
		bool caracter_nodo_abre;
		bool caracter_nodo_cierra;
		bool linea_bien_escrita;
		//método interno para contar la cantidad de caracteres de dentado que hay
		void cuentaDentado();
		//método interno para revisar si la línea almacenada tiene caracteres importantes
		void buscaCaracteresImportantes();
		//método interno que cuentaDentado, buscaCaracteresImportantes y se fija si tiene caracteres dobles o están mal escritos en la línea
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
		bool getNodoAbre(void)const{return caracter_nodo_abre;}
		bool getNodoCierra(void)const{return caracter_nodo_cierra;}
		bool getLineaBienEscrita(void)const{return linea_bien_escrita;}
		//devuelve el contenido de la línea antes de un caracter importante, si está bien escrita
		void obtieneContenido(std::string& salida);
		//metodo set
		void setNumero(const int& numero);
		//sobrecarga operadores
		LineaTopDown& operator= (const LineaTopDown& l);
		friend std::ostream& operator<< (std::ostream& os, const LineaTopDown& l);
		friend std::istream& operator>> (std::istream& is, LineaTopDown&l);
};
#endif
