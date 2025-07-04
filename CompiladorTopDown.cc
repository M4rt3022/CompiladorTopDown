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
int CompiladorTopDown::revisaCorrectoDentado(){
	std::cout << "[CompiladorTopDown]: Revisando dentado en el archivo ..." << std::endl;
	int cantidadLineas = archivoTD.getCantidadLineas();
	int i = archivoTD.getComienzoNodo(1);
	for(;i<cantidadLineas;i++){
		if(archivoTD.getDentadoLinea(i)<1){
			return 1;
		}
	}
	return 0;
}
int CompiladorTopDown::buscaTituloTP(){
	std::cout << "[CompiladorTopDown]: Buscando título del top down ..." <<std::endl;
	std::string titulo;
	int ordenDesde = 0;
	juntaContenido(archivoTD.getComienzoNodo(0),';',titulo);
	if(ordenDesde==-1){
		return -1;
	}
	//crea nodo con todo el contenido almacenado
	topdown.agregaNodo("",titulo);
	return 0;
}
void CompiladorTopDown::guardaEnArchivo(){
	std::cout << "[CompiladorTopDown]: Guardando archivo formateado de topdown ..." <<std::endl;
	topdown.guardaTopDown();
}
void CompiladorTopDown::juntaContenido(const int & numLinea,const char& caracter,std::string& salida){
	salida = "";
	int dentado;
	//primero debo revisar que el orden exista
	if(numLinea > archivoTD.getCantidadLineas()){
		return ;
	} 
	int numLineaAux = numLinea;
	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	dentado = archivoTD.getDentadoLinea(numLineaAux);
	for(;dentado==archivoTD.getDentadoLinea(numLineaAux);numLineaAux++){
		archivoTD.getContenidoLinea(numLineaAux, salida);
		if(archivoTD.getBoolLinea(numLineaAux,caracter)){
			break;
		}
	}
	return;
}
//método que cuenta cuantos hijos tiene un nodo y lo devuelve;
int CompiladorTopDown::cuentaHijos(const int& numeroLinea){
	int cantHijos = 0;
	if(numeroLinea > archivoTD.getCantidadLineas()){
		return -1;
	}
	int cantidadTabs = archivoTD.getDentadoLinea(numeroLinea);
	for(int i = numeroLinea+1; i < archivoTD.getCantidadLineas();i++){
		if(cantidadTabs+1==archivoTD.getDentadoLinea(i)&&1==archivoTD.getBoolLinea(i,';')){
			cantHijos++;
		}
		if(cantidadTabs>=archivoTD.getDentadoLinea(i)){
			break;
		}
	}
	return cantHijos;
}
void CompiladorTopDown::nombraHijos(const int &numLinea ,const std::string& ordenPadre){
	int cantidadHijos = cuentaHijos(numLinea);
	std::cout << "tiene " << cantidadHijos << " hijos" << std::endl;
	//si no tiene hijos, ni se calienta
	if (cantidadHijos == 0){
		return;
	}
	int cantidadTabs = archivoTD.getDentadoLinea(numLinea);
	//debe buscar su orden en el arreglo de gomienzosNodos
	int posicionEnComienzosNodos = 0;
	for (int i=0;i<archivoTD.getCantidadNodos();i++){
		if(numLinea==archivoTD.getComienzoNodo(i)){
			posicionEnComienzosNodos = i;
			break;
		}
	}
	std::vector<int> dondeComienzan;
	std::string stringAuxiliar;
	std::string nombreAuxiliar;
	//guardo donde comienza cada hijo del nodo para luego iterarlo
	for(int i=0;i< cantidadHijos;i++){
		for(int j = posicionEnComienzosNodos;j<archivoTD.getCantidadNodos();j++){
			if(cantidadTabs+1==archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(j))){
				dondeComienzan.push_back(archivoTD.getComienzoNodo(j));
			}
		}
	}
	//acá aplica recursividad para que cada padre nombre a su hijo y así sucesivamente
	for(int i=0;i<cantidadHijos;i++){
		//obtiene todo el contenido de un hijo
		juntaContenido(dondeComienzan[i],';',stringAuxiliar);
		//lo nombra como nodoPadre + . + i y le pone el nombre de su padre
		if(ordenPadre.empty()){
			nombreAuxiliar = std::to_string(i+1);
		}else if(!ordenPadre.empty()){
			nombreAuxiliar = ordenPadre + "." + std::to_string(i+1);
		}
		topdown.agregaNodo(nombreAuxiliar,stringAuxiliar);
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

		
		if(revisaCorrectoDentado()==1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_DENTADO));
		}

		int numLineaAux = buscaTituloTP();
		if(numLineaAux==-1){
			throw (ErrorHandler(TipoError::ERROR_COMPILADOR_OBTENER_TITULO_TOPDOWN));
		}

		//una vez que ya obtuvo el título, recursivamente nombra a los hijos del mismo
		std::cout << "el titulo comienza en la línea: " << archivoTD.getComienzoNodo(0) << std::endl;
		nombraHijos(archivoTD.getComienzoNodo(0),"");


		//guarda todo lo que se procesó en el archivo formateado
		guardaEnArchivo();

		std::cout << "[CompiladorTopDown]: Compilación Completa." << std::endl;
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << ", se detiene compilación." << std::endl;
	}
}
