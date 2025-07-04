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
	topdown.agregaNodo("",titulo);
	return ordenDesde;
}
void CompiladorTopDown::guardaEnArchivo(){
	std::cout << "[CompiladorTopDown]: Guardando archivo formateado de topdown ..." <<std::endl;
	topdown.guardaTopDown();
}
std::string& CompiladorTopDown::juntaContenido(const int & numLinea,const char& caracter){
	std::cout << "juntaContenido (" << numLinea << "," << caracter << ")" << std::endl;
	static std::string stringAuxiliar = "";
	int dentado;
	//primero debo revisar que el orden exista
	if(numLinea > archivoTD.getCantidadLineas()){
		return stringAuxiliar;
	} 
	int numLineaAux = numLinea;
	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	dentado = archivoTD.getDentadoLinea(numLineaAux);
	std::cout << dentado << std::endl;
	for(;dentado==archivoTD.getDentadoLinea(numLineaAux);numLineaAux++){
		archivoTD.getContenidoLinea(numLineaAux, stringAuxiliar);
		if(archivoTD.getBoolLinea(numLineaAux,caracter)){
			break;
		}
	}
	std::cout << "juntaContenido devuelve: " << stringAuxiliar << std::endl;
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
	std::cout << "nombraHijos (" << numLinea << "," << ordenPadre << ")" << std::endl;
	int cantidadHijos = cuentaHijos(numLinea);
	//si no tiene hijos, ni se calienta
	if (cantidadHijos == 0){
		return;
	}
	int cantidadTabs = archivoTD.getDentadoLinea(numLinea);
	std::vector<int> dondeComienzan;
	std::string stringAuxiliar = "";
	std::string nombreAuxiliar = "";
	//guardo donde comienza cada hijo del nodo para luego iterarlo
	for(int i=0;i< cantidadHijos;i++){
		for(int j = 0;j<archivoTD.getCantidadNodos();j++){
			if(cantidadTabs+1==archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(j))){
				dondeComienzan.push_back(archivoTD.getComienzoNodo(j));
			}
		}
	}
	std::cout << "lugares donde comienzan los contenidos de los hijos" << std::endl;
	for (int k=0;k<cantidadHijos;k++){
		std::cout << dondeComienzan[k] << std::endl;
	}
	//acá aplica recursividad para que cada padre nombre a su hijo y así sucesivamente
	for(int i=0;i<cantidadHijos;i++){
		//obtiene todo el contenido de un hijo
		stringAuxiliar = juntaContenido(dondeComienzan[i],';');
		//lo nombra como nodoPadre + . + i y le pone el nombre de su padre
		std::cout << stringAuxiliar << std::endl;
		if(ordenPadre.empty()){
			nombreAuxiliar = std::to_string(i+1);
		}else if(!ordenPadre.empty()){
			nombreAuxiliar = ordenPadre + "." + std::to_string(i+1);
		}
		topdown.agregaNodo(nombreAuxiliar,stringAuxiliar);
		std::cout << "agreganodo(" << nombreAuxiliar << "," << stringAuxiliar << ")"<< std::endl;
		//luego, se le pide que nombre a sus hijos
		nombraHijos(dondeComienzan[i],nombreAuxiliar);
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

		//ahora se le pide que el padre nombre a sus hijos:
		nombraHijos(archivoTD.getComienzoNodo(0),"");
		std::cout << "la cantidad de nodos guardados fue de: " << topdown.getCantidadNodos() << std::endl;

		//guarda todo lo que se procesó en el archivo formateado
		guardaEnArchivo();

		std::cout << "[CompiladorTopDown]: Compilación Completa." << std::endl;
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << ", se detiene compilación." << std::endl;
	}
}
