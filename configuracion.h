#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_
#include <fstream>
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
	Linea_sin_proposito,
};
class Configuracion{
	public:
		std::string finLinea = ";";
		std::string tabulador = "\t";
		std::string comentario = "#";
		std::vector<std::string> condicionLinea = {"si", "if"};
		std::vector<std::string> iteracionLinea = {"repetir", "mientras", "for", "while"};
		std::string formatoSalida = "pdf";
		bool unSoloTopDown = true;
		bool imprimirSalidaPrograma = false;
		// lee datos del archivo confg y los guarda
		void cargaDatosDesdeArchivo(void);
		// Edita las variables Internas para volver a la configuración por defecto, sin necesidad de un archivo
		void restablecerConfig(void);
		// Hace un nuevo archivo de configuración con los datos por defecto
		void creaArchivoConfig(void);
		// recibe una línea y verifica que sea de configuración, que sea válida. retorna orden enum según el caso
		palabrasConfig tipoLineaConfig(const std::string& linea);
		// cuenta la cantidad de palabras entre comillas de un string
		int cantidadPalabrasEntreComillas(const std::string& s);
		// increíble que esté usando este método
		void sacaPalabra(std::string::const_iterator& desde,const std::string& origen, std::string& destino,const char& caracterFinal);
		// cuenta la cantidad de comillas que tiene un string
		int cuentaComillas(const std::string& entrada);
		// cuenta la cantiad de líneas del archivo
		int cantidadLineasArchivo(std::ifstream& archivo);
		// toma un orden del enum palabrasConfig y edita el parámetro que corresponda, devuelve 0 si sale bien y de lo contrario !=0
		int aplicaConfiguracion(palabrasConfig& config, const std::string& linea);
};
#endif
