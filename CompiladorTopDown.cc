#include "CompiladorTopDown.h"
#include "ErrorHandler.h"
CompiladorTopDown::CompiladorTopDown(){}
CompiladorTopDown::~CompiladorTopDown(){}
void CompiladorTopDown::leeArchivoTD(){
	ArchivoTD.leeDesdeArchivo();
}
//el dentado del archivo solo debe tener una línea sin dentado y las demás por lo menos con uno
int CompiladorTopDown::revisaCorrectoDentado(){
	int cantidadLineas = ArchivoTD.getCantidadLineas();
	if (cantidadLineas == 0){
		return 1;
	}
	for(int i = 1; i < cantidadLineas; i++){
		if(ArchivoTD.getDentadoLinea(i)<1){
			return 1;
		}
	}
	return 0;
}
int CompiladorTopDown::buscaTituloTP(){
	std::string titulo;

}
void CompiladorTopDown::compilar(){
	try{
		//carga los datos del topdown
		leeArchivoTD();
		//analiza si algo dentro del Archivo ha salido mal
		if(ArchivoTD.getError()){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_ARCHIVOTD));
		}
		//busca el título del topdown y lo guarda en un nodo
		if(revisaCorrectoDentado()==1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_DENTADO))
		}
		//busca el título del archivo a guardar
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << ", no seguirá compilando" << std::endl;
	}
}
