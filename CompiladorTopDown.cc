#include "CompiladorTopDown.h"
#include "ErrorHandler.h"
CompiladorTopDown::CompiladorTopDown(){}
CompiladorTopDown::~CompiladorTopDown(){}
void CompiladorTopDown::leeArchivoTD(){
	archivoTD.leeDesdeArchivo();
}
//el dentado del archivo solo debe tener una línea sin dentado y las demás por lo menos con uno
int CompiladorTopDown::revisaCorrectoDentado(){
	int cantidadLineas = archivoTD.getCantidadLineas();
	for(int i = 1; i < cantidadLineas; i++){
		if(archivoTD.getDentadoLinea(i)<1){
			return 1;
		}
	}
	return 0;
}
int CompiladorTopDown::buscaTituloTP(){
	std::string titulo;
	archivoTD.getContenidoLinea(0,titulo); 
	if (titulo.empty()){
		return 1;
	}
	topdown.agregaNodo("","", titulo);
	return 0;
}
void CompiladorTopDown::compilar(){
	try{
		//carga los datos del topdown
		leeArchivoTD();
		//analiza si algo dentro del Archivo ha salido mal
		if(archivoTD.getError()){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_ARCHIVOTD));
		}
		//busca el título del topdown y lo guarda en un nodo
		if(revisaCorrectoDentado()==1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_DENTADO));
		}
		//busca el título del archivo a guardar
		if(buscaTituloTP()==1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_OBTENER_TITULO_TOPDOWN));
		}


	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << " se detiene compilación." << std::endl;
	}
}
