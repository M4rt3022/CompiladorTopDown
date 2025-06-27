#ifndef LINEATOPDOWN_H_
#define LINEATOPDOWN_H_
#include <iostream>
#include <fstream>
#include <string>
enum {ERROR_FIN_LINEA,ERROR_NODO_ABRE,ERROR_NODO_CIERRA,ERROR_CARACTER_DOBLE,ERROR_ABRIR_ARCHIVO,ERROR_STRING_VACÍO};
class LineaTopDown{
	private:
		int numeroDentado;
		std::string caracteres;
		bool caracter_fin_linea;
		bool caracter_nodo_abre;
		bool caracter_nodo_cierra;
		//método interno para contar la cantidad de caracteres de dentado que hay
		void cuentaDentado();
		//método interno para revisar si la línea almacenada tiene caracteres importantes
		void buscaCaracteresImportantes();
		//método interno para buscar dobles caracteres importantes o más de un caracter importante por línea, lanza excepción en caso de error
		void revisaCorrectaSintaxis();
	public:
		//constructores
		LineaTopDown();
		LineaTopDown(const int &dentado,const std::string &carac);
		~LineaTopDown();
		//métodos gets
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
