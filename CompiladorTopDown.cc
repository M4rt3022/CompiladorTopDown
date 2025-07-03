#include "CompiladorTopDown.h"
#include "ErrorHandler.h"
#include <string>
#include <vector>
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
	std::cout << "se analizará el dentado del archivo desde el orden de línea: " << desde << std::endl;
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
std::string& CompiladorTopDown::juntaContenido(int & numLinea,const char& caracter){
	static std::string stringAuxiliar = "";
	int dentado;
	//primero debo revisar que el orden exista
	if(numLinea > archivoTD.getCantidadLineas()){
		return stringAuxiliar;
	} 
	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	dentado = archivoTD.getDentadoLinea(numLinea);
	for(;dentado==archivoTD.getDentadoLinea(numLinea);numLinea++){
		archivoTD.getContenidoLinea(numLinea, stringAuxiliar);
		if(archivoTD.getBoolLinea(numLinea,caracter)){
			break;
		}
	}

	return stringAuxiliar;
}
//método que cuenta cuantos hijos tiene un nodo y lo devuelve;
int CompiladorTopDown::cuentaHijos(const int& numeroLinea){
	int cantHijos = 0;
	if(numeroLinea> archivoTD.getCantidadLineas()){
		return -1;
	}
	int cantidadTabs = archivoTD.getDentadoLinea(numeroLinea);
	for(int i=0;i < archivoTD.getCantidadNodos();i++){
		//si la linea donde comienza un nodo, tiene el mismo numero de tabs+1 que donde comencé, es un hijo
		if(cantidadTabs+1==archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(i))){
			cantHijos++;
		}
	}
	return cantHijos;
}
void CompiladorTopDown::nombraHijos(const int &numLinea ,const std::string& ordenPadre){
	int cantidadHijos = cuentaHijos(numLinea);
	//si no tiene hijos, ni se calienta
	if (cantidadHijos == 0){
		return;
	}
	int cantidadTabs = archivoTD.getDentadoLinea(numLinea);
	std::vector<int> dondeComienzan;
	std::string stringAuxiliar;
	std::string nombreAuxiliar;
	//guardo donde comienza cada hijo del nodo para luego iterarlo
	for(int i=0;i< cantidadHijos;i++){
		for(int j = 0;j<archivoTD.getCantidadNodos();j++){
			if(cantidadTabs+1==archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(j))){
				dondeComienzan.push_back(archivoTD.getComienzoNodo(j));
			}
		}
	}
	//acá aplica recursividad para que cada padre nombre a su hijo y así sucesivamente
	for(int i=0;i<cantidadHijos;i++){
		stringAuxiliar = "";
		nombreAuxiliar = "";
		//obtiene todo el contenido de un hijo
		stringAuxiliar = juntaContenido(dondeComienzan[i],';');
		//lo nombra como nodoPadre + . + i y le pone el nombre de su padre
		nombreAuxiliar = ordenPadre + "." + std::to_string(i);
		topdown.agregaNodo(nombreAuxiliar,ordenPadre,stringAuxiliar);
		//luego, se le pide que nombre a sus hijos
		nombraHijos(archivoTD.getComienzoNodo(i),nombreAuxiliar);
	}
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
		int numLineaAux = buscaTituloTP();
		if(numLineaAux == -1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_OBTENER_TITULO_TOPDOWN));
		}

		//solo para checkear
		archivoTD.imprimeComienzosNodos();
		std::cout << "la cantidad de hijos que tiene el padre son: " << cuentaHijos(0) << std::endl;

		if(revisaCorrectoDentado(++numLineaAux)==1){
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
