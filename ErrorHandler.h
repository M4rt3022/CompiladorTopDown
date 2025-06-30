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
	ERROR_LINEA_INEXISTENTE, 
	ERROR_LINEA_ARCHIVO_VACÍO,
	ERROR_LINEA_MAL_ESCRITA,
	ERROR_TOPDOWN_ABRIR_ARCHIVO,
	ERROR_TOPDOWN_ARCHIVO_VACÍO,
	ERROR_COMPILADOR_ERROR_ARCHIVOTD,
	ERROR_COMPILADOR_ERROR_DENTADO,
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
					return "El caracter de final de línea debe ser el último";
				case(TipoError::ERROR_LINEA_NODO_ABRE):
					return "El caracter de apertura de nodo debe ser el último";
				case(TipoError::ERROR_LINEA_NODO_CIERRA):
					return "El caracter de cerrado de nodo debe ser el último";
				case(TipoError::ERROR_LINEA_CARAC_DOBLE):
					return "Se encontró más de un caracter importante en la línea";
				case(TipoError::ERROR_LINEA_STRING_VACIO):
					return "El string leído está vacío";
				case(TipoError::ERROR_LINEA_ABRIR_ARCHIVO):
					return "Error al abrir el archivo";
				case(TipoError::ERROR_LINEA_INEXISTENTE):
					return "El numero de línea buscado no existe";
				case(TipoError::ERROR_LINEA_ARCHIVO_VACÍO):
					return "El archivo abierto se encuentra vacío";
				case(TipoError::ERROR_LINEA_MAL_ESCRITA):
					return "La linea que intenta obtener está mal escrita";
				case(TipoError::ERROR_TOPDOWN_ABRIR_ARCHIVO):
					return "No se pudo abrir el archivo para guardar el topdown";
				case(TipoError::ERROR_TOPDOWN_ARCHIVO_VACÍO):
					return "El topdown a guardar está vacío, no se guardará";
				case(TipoError::ERROR_COMPILADOR_ERROR_ARCHIVOTD):
					return "Algo salió mal en la lectura del topdown";
				case(TipoError::ERROR_COMPILADOR_ERROR_DENTADO):
					return "El dentado que tiene el archivo no es correcto";
				default:
					return "Error desconocido";
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
