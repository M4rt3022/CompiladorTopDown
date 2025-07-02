#include "CompiladorTopDown.h"
#include "ErrorHandler.h"
CompiladorTopDown::CompiladorTopDown(){}
CompiladorTopDown::~CompiladorTopDown(){}
void CompiladorTopDown::leeArchivoTD(){
	std::cout << "[CompiladorTopDown]: Leyendo datos desde archivo ..." << std::endl;
	archivoTD.leeDesdeArchivo();
}
//el dentado del archivo solo debe tener una línea sin dentado y las demás por lo menos con uno
int CompiladorTopDown::revisaCorrectoDentado(int& desde){
	std::cout << "[CompiladorTopDown]: Revisando dentado en el archivo ..." << std::endl;
	int cantidadLineas = archivoTD.getCantidadLineas();
	for(;desde<cantidadLineas;desde++){
		if(archivoTD.getDentadoLinea(desde)<1){
			return 1;
		}
	}
	return 0;
}
int CompiladorTopDown::buscaTituloTP(){
	std::cout << "[CompiladorTopDown]: Buscando título del top down ..." <<std::endl;
	std::string titulo;
	int ordenDesde = 0;
	titulo = juntaContenido(ordenDesde,';');
	if(ordenDesde==-1){
		return -1;
	}
	//crea nodo con todo el contenido almacenado
	topdown.agregaNodo("","",titulo);
	return ordenDesde;
}
void CompiladorTopDown::guardaEnArchivo(){
	std::cout << "[CompiladorTopDown]: Guardando archivo formateado de topdown ..." <<std::endl;
	topdown.guardaTopDown();
}
std::string& CompiladorTopDown::juntaContenido(int & orden,const char& caracter){
	static std::string stringAuxiliar = "";
	int dentado;
	//primero debo revisar que el orden exista
	if(orden > archivoTD.getCantidadLineas()){
		return stringAuxiliar;
	} 
	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	dentado = archivoTD.getDentadoLinea(orden);
	std::cout << "valor de dentado: " << dentado << std::endl;
	for(;dentado==archivoTD.getDentadoLinea(orden);orden++){
		std::cout << "valor de orden: " << orden << std::endl;
		archivoTD.getContenidoLinea(orden, stringAuxiliar);
		if(archivoTD.getBoolLinea(orden,caracter)){
			break;
		}
	}
	return stringAuxiliar;
}
//método para generar todos los nodos automáticamente y guardarlos en el topdown
int CompiladorTopDown::generaNodos(int & desde){
	//voy a diseñar esto como si no existieran nodos que abarcan otros nodos
	return desde;
}
void CompiladorTopDown::compilar(){
	std::cout << "[CompiladorTopDown]: Compilando topdown ..." << std::endl;
	try{
		//carga los datos del topdown
		leeArchivoTD();
		//analiza si algo dentro del Archivo ha salido mal
		if(archivoTD.getError()){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_ARCHIVOTD));
		}
		//busca el título del archivo a guardar y guarda en ordenAuxiliar, la línea donde termina el título
		int ordenAuxiliar = buscaTituloTP();
		if(ordenAuxiliar == -1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_OBTENER_TITULO_TOPDOWN));
		}
		ordenAuxiliar++;
		std::cout << "La  línea que sigue al título es la línea: " << ordenAuxiliar << std::endl;
		if(revisaCorrectoDentado(ordenAuxiliar)==1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_DENTADO));
		}
		//guarda todo lo que se procesó en el archivo formateado
		guardaEnArchivo();
		std::cout << "[CompiladorTopDown]: Compilación Completa." << std::endl;
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << ", se detiene compilación." << std::endl;
	}
}
