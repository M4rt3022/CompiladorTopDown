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
std::string& CompiladorTopDown::juntaContenido(int & orden,const char& caracter){
	static std::string stringAuxiliar = "";
	int dentado;

	//primero debo revisar que el orden exista
	if(orden > archivoTD.getCantidadLineas()){
		return stringAuxiliar;
	} 

	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	dentado = archivoTD.getDentadoLinea(orden);
	for(;dentado==archivoTD.getDentadoLinea(orden);orden++){
		archivoTD.getContenidoLinea(orden, stringAuxiliar);
		if(archivoTD.getBoolLinea(orden,caracter)){
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
	int numLineaAux = numeroLinea;
	int cantidadTabs = archivoTD.getDentadoLinea(numLineaAux);
	numLineaAux++;
	for(;cantidadTabs!=archivoTD.getDentadoLinea(numLineaAux);numLineaAux++){
		if(cantidadTabs+1==archivoTD.getDentadoLinea(numLineaAux)&&archivoTD.getBoolLinea(numLineaAux, ';')){
			cantHijos++;
		}
	}
	return cantHijos;
}
void CompiladorTopDown::nombraHijos(const int &numLinea ,const std::string& ordenPadre){
	int cantidadHijos = cuentaHijos(numLinea);
	std::vector<int> ordenesHijos;
	if(cantidadHijos == 0){
		return;
	}
	ordenesHijos.reserve(cantidadHijos);
	int i = 0, j = numLinea;
	int tabsPadre = archivoTD.getDentadoLinea(numLinea);
	if (numLinea>archivoTD.getCantidadLineas()){
		return;
	}
	//guarda en el vector los números de líneas donde se encuentran los principios de contenidos de sus nodos hijos
	for(;i<cantidadHijos&&j<archivoTD.getCantidadLineas();j++){
		if(tabsPadre+1==archivoTD.getDentadoLinea(j)){
			ordenesHijos.push_back(j);
			//se saltea todos los espacios hasta que encuentre donde termina el hijo
			while(0==archivoTD.getBoolLinea(j, ';')){
				j++;
			}
		}
	}
	//para cada hijo
	std::string contenidoAuxiliar;
	std::string ordenAuxiliar;
	for(i = 0; i < cantidadHijos;i++){
		ordenAuxiliar = "";
		contenidoAuxiliar = "";
		archivoTD.getContenidoLinea(ordenesHijos[i],contenidoAuxiliar);
		//ahora es donde crea el hijo y le asigna todo
		ordenAuxiliar = ordenPadre + "." + std::to_string(i+1);		//esto es para que le ponga 1.1, 1.2, 1.3 y así
		topdown.agregaNodo(ordenAuxiliar,ordenPadre,contenidoAuxiliar);
		//la mama de la mamá de la mamá de la mamá
		nombraHijos(ordenesHijos[j],ordenAuxiliar);
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
		int ordenAuxiliar = buscaTituloTP();
		if(ordenAuxiliar == -1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_OBTENER_TITULO_TOPDOWN));
		}

		std::cout << "el titulo termina en la línea: "<< ordenAuxiliar << std::endl;
		std::cout << "la cantidad de hijos del título son: " << cuentaHijos(ordenAuxiliar) << std::endl;

		if(revisaCorrectoDentado(++ordenAuxiliar)==1){
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
