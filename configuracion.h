#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_
#include <iostream>
#include <string>
#include <vector>
class Configuracion{
	public:
		std::string caracter_fin_linea = ";";
		std::string caracter_tabulador = "\t";
		std::string caracter_comentario = "\t";
		std::vector<std::string> palabras_condicion = {"si", "if"};
		std::vector<std::string> palabras_iteracion = {"repetir", "mientras", "for", "while"};
		bool agregaEspacios = true;
		std::string formatoSalida = "pdf";
		bool unSoloTopDown = true;
		bool imprimirSalidaPrograma = false;
		void cargaDesdeArchivo(const std::string& nombreArchivo);
};
#endif
