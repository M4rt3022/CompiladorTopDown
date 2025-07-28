#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_
#include <iostream>
#include <string>
#include <vector>
enum class palabrasConfig{
	caracter_fin_linea,
	caracter_tabulador,
	caracter_comentario,
	condicion_linea,
	iteracion_linea,
	formato_salida,
	agregar_espacios,
	un_solo_topdown,
	imprimir_salida_programa,
	desconocida,
};
class Configuracion{
	public:
		std::string caracterFinLinea = ";";
		std::string caracterTabulador = "\t";
		std::string caracterComentario = "\t";
		std::vector<std::string> condicionLinea = {"si", "if"};
		std::vector<std::string> iteracionLinea = {"repetir", "mientras", "for", "while"};
		std::string formatoSalida = "pdf";
		bool agregarEspacios = true;
		bool unSoloTopDown = true;
		bool imprimirSalidaPrograma = false;
		// lee datos del archivo confg y los guarda
		void cargaDesdeArchivo(const std::string& nombreArchivo);
		void creaArchivoConfig(void);
		void restablecerConfig(void);
};
#endif
