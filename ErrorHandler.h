#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include <iostream>
#include <exception>
#include <string>
//lista de todos los errores posibles por el programa 
enum class TipoError {
	ERROR_LINEA_FIN_LINEA,
	ERROR_LINEA_NODO_ABRE,
	ERROR_LINEA_NODO_CIERRA,
	ERROR_LINEA_CARAC_DOBLE,
	ERROR_LINEA_STRING_VACIO,
	ERROR_LINEA_ABRIR_ARCHIVO,
};
//clase que busca el error al ser inicializada y devuelve un mensaje en consecuencia
class ErrorHandler : public std::exception
{
	private:
		TipoError tipo;
		std::string mensajeError;
		static std::string obtenerMensajeError(TipoError error){
			switch(error){
				case(TipoError::ERROR_LINEA_FIN_LINEA):
					return "el caracter de final de línea debe ser el último";
				case(TipoError::ERROR_LINEA_NODO_ABRE):
					return "el caracter de apertura de nodo debe ser el último";
				case(TipoError::ERROR_LINEA_NODO_CIERRA):
					return "el caracter de cerrado de nodo debe ser el último";
				case(TipoError::ERROR_LINEA_CARAC_DOBLE):
					return "se encontró más de un caracter importante en la línea";
				case(TipoError::ERROR_LINEA_STRING_VACIO):
					return "el string leído está vacío";
				case(TipoError::ERROR_LINEA_ABRIR_ARCHIVO):
					return "error al abrir el archivo";
				default:
					return "error desconocido";
			}

		}
	public:
		//constructor
		ErrorHandler(TipoError t): tipo(t), mensajeError(obtenerMensajeError(t)){}
		const char * what() const noexcept override{
			return mensajeError.c_str();
		}
};
#endif
