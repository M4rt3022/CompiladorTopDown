#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_
#include <iostream>
#include <string>
#include <vector>
enum class palabrasConfig{
	fin_linea,
	tabulador,
	comentario,
	condicion_linea,
	iteracion_linea,
	formato_salida,
	un_solo_topdown,
	imprimir_salida_programa,
	desconocida,
};
class Configuracion{
	public:
		std::string finLinea = ";";
		std::string tabulador = "\t";
		std::string comentario = "\t";
		std::vector<std::string> condicionLinea = {"si", "if"};
		std::vector<std::string> iteracionLinea = {"repetir", "mientras", "for", "while"};
		std::string formatoSalida = "pdf";
		bool unSoloTopDown = true;
		bool imprimirSalidaPrograma = false;
		// lee datos del archivo confg y los guarda
		void cargaDesdeArchivo(const std::string& nombreArchivo);
		// Edita las variables Internas para volver a la configuración por defecto, sin necesidad de un archivo
		void restablecerConfig(void);
		// Hace un nuevo archivo de configuración con los datos por defecto
		void creaArchivoConfig(void);
		// recibe una línea y verifica que sea de configuración, que sea válida. retorna orden enum o desconocida en otro caso
		int LineaConfigEsCorrecta(const std::string& linea);
};
#endif
