#ifndef LINEATOPDOWN_H_
#define LINEATOPDOWN_H_
#include <iostream>
#include <fstream>
#include <string>
enum {ERROR_CARACTER_DOBLE,ERROR_ABRIR_ARCHIVO};
class LineaTopDown{
	private:
		int numeroLinea;
		int numeroDentado;
		std::string caracteres;
		bool caracter_fin_linea;
		bool caracter_nodo_abre;
		bool caracter_nodo_cierra;
		//método para contar la cantidad de caracteres de dentado que hay
		void cuentaDentado();
		//método para revisar si la línea almacenada tiene el caracter de fin de línea
		void buscaCaracteresImportantes();
	public:
		//constructores
		LineaTopDown();
		LineaTopDown(const int &numero,const int &dentado,const std::string &carac);
		~LineaTopDown();
		//métodos gets
		int getNumero(void) const {return numeroLinea;}
		int getDentado(void) const {return numeroDentado;}
		std::string getCaracteres(void) const {return caracteres;}
		bool getFinLinea(void)const{return caracter_fin_linea;}
		bool getNodoAbre(void)const{return caracter_nodo_abre;}
		bool getNodoCierra(void)const{return caracter_nodo_cierra;}
		//metodo set
		void setNumero(const int& numero);
		//sobrecarga operadores
		LineaTopDown& operator= (const LineaTopDown& l);
		friend std::ostream& operator<< (std::ostream& os, const LineaTopDown& l);
		friend std::istream& operator>> (std::istream& is, LineaTopDown&l);
		//método para leer desde un archivo
		void leeDesdeArchivo(std::ifstream& archivo);
};
#endif
