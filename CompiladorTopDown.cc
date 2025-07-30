#include "CompiladorTopDown.h"
#include "ErrorHandler.h"
#include "LineaTopDown.h"
#include <string>
#include <vector>

//constructor
CompiladorTopDown::CompiladorTopDown(){}

//destructor
CompiladorTopDown::~CompiladorTopDown(){}

//método para buscar el ArchivoTD
void CompiladorTopDown::leeArchivoTD(){
	std::cout << "[CompiladorTopDown]: Leyendo datos desde archivo" << std::endl;
	archivoTD.leeDesdeArchivo();
}

//método para buscar el título del TD, devuelve el numero de línea en donde termina el título, sino, -1
int CompiladorTopDown::buscaTituloTP(){
	std::cout << "[CompiladorTopDown]: Buscando título del top down" <<std::endl;
	std::string titulo;
	int ordenDesde = 0;
	juntaContenido(archivoTD.getComienzoNodo(0),titulo);
	if(ordenDesde==-1){
		return -1;
	}
	//crea nodo con todo el contenido almacenado
	topdown.agregaNodo("",titulo);
	return 0;
}

// solo revisa que estén correctamente dentadas las líneas de comienzoNodos
int CompiladorTopDown::revisaCorrectoDentado(){
	std::cout << "[CompiladorTopDown]: Revisando dentado en el archivo" << std::endl;
	//toma la cantidad de caracteres que tiene la línea de comienzo del título -> será la base para las demás
	int cantidadTabsTitulo = archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(0));
	int cantidadTabsActual;
	int cantidadTabsSiguiente;
	bool esValida = false;
	// primero revisa que todas las líneas tengan más de un dentado que el título
	for(int i = 1;i<archivoTD.getCantidadComienzosNodos();i++){
		if(cantidadTabsTitulo<archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(i))){
			esValida = true;
		}
		if(!esValida){
			return 1;
			break;
		}
	}
	// si la siguiente línea tiene +1 tabs que donde estoy parado, es correcta, si tiene menos o igual, también
	// sino se cumple lo anterior, es falsa
	for(int i=1;i<(archivoTD.getCantidadComienzosNodos()-1);i++){
		//guardo dentado de línea actual
		cantidadTabsActual = archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(i));
		//reviso la siguiente
		cantidadTabsSiguiente = archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(i+1));
		if((cantidadTabsActual>=cantidadTabsSiguiente)||(cantidadTabsActual+1==cantidadTabsSiguiente)){
			esValida = true;
		}else{
			esValida = false;
		}
		if(!esValida){
			return 1;
		}
	}
	// si llega hasta acá, significa que está todo ok
	return 0;
}

//método que toma desde un número de línea en específico y junta su contenido hasta encontrar un caracter_fin_linea
//utiliza el orden enviado como referencia y lo modifica
void CompiladorTopDown::juntaContenido(const int & numLinea,std::string& salida){
	salida = "";
	//primero debo revisar que el orden exista
	if(numLinea > archivoTD.getCantidadLineas()){
		return ;
	} 
	int numLineaAux = numLinea;
	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	for(; numLineaAux < archivoTD.getCantidadLineas() ;numLineaAux++){
		archivoTD.getContenidoLinea(numLineaAux, salida);
		// si encontró un final de línea, termina de juntar contenido
		if(archivoTD.getBoolLinea(numLineaAux,LineaTopDown::flag::flag_caracter_fin_linea)){
			break;
		}
	}
	return;
}

//método que cuenta cuantos hijos tiene un nodo y lo devuelve;
// esto solo funciona si recibe un orden de comienzo de nodo
int CompiladorTopDown::cuentaHijos(const int& ordenComienzoNodo){
	int cantHijos = 0;
	int cantidadTabs;
	if(ordenComienzoNodo>archivoTD.getCantidadComienzosNodos()){
		return -1;
	}
	std::cout << "orden de comienzo de nodo ingresado : " << ordenComienzoNodo << std::endl;
	cantidadTabs = archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(ordenComienzoNodo));
	std::cout << "numero de tabs que tiene : " << cantidadTabs << std::endl;
	for(int i = ordenComienzoNodo+1;i<archivoTD.getCantidadComienzosNodos();i++){
		if(cantidadTabs+1==archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(i))){
			cantHijos++;
		}
		//en cuanto encuentre un nodo con igual o menor cantidad de tabs, paro de contar
		if(cantidadTabs>=archivoTD.getDentadoLinea(archivoTD.getComienzoNodo(i))){
			break;
		}
	}
	return cantHijos;
}

//método que cuentaHijos y les otorga sus nombres en base a el nombre del padre
void CompiladorTopDown::nombraHijos(const int &numLinea ,const std::string& ordenPadre){
	//primero cuento cuantos hijos tiene el nodo recibido
	int cantidadHijos = cuentaHijos(numLinea);
	//si no tiene hijos no hay nada que nombrar
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
		juntaContenido(dondeComienzan[i],stringAuxiliar);
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

//método para tomar todo lo guardado en topdown y almacenarlo en un archivo de texto formateado
void CompiladorTopDown::guardaEnArchivo(){
	std::cout << "[CompiladorTopDown]: Guardando archivo formateado de topdown" <<std::endl;
	topdown.guardaTopDown();
}

//método que engloba todos los métodos anteriores en orden
void CompiladorTopDown::compilar(){
	std::cout << "[CompiladorTopDown]: Compilando topdown" << std::endl;
	try{
		/*
		//carga los datos del topdown
		leeArchivoTD();

		//analiza si algo dentro del Archivo ha salido mal
		if(archivoTD.getError()){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_ARCHIVOTD));
		}

		std::cout << "cantidad LineasGuardadas : " << archivoTD.getCantidadLineas() << std::endl;
		std::cout << "cantidad de comienzod nodos guardados : ";
		for(int i=0;i<archivoTD.getCantidadComienzosNodos();i++){
			std::cout << "ordenComienzo : " << archivoTD.getComienzoNodo(i) << std::endl;
		}

		if(revisaCorrectoDentado()==1){
			throw(ErrorHandler(TipoError::ERROR_COMPILADOR_ERROR_DENTADO));
		}

		//ELIMINAR LUEGO
		int cantidadHijos = cuentaHijos(0);
		std::cout << "cantidad de hijos que tiene : " << cantidadHijos << std::endl;
		//ELIMINAR LUEGO
		
		int numLineaAux = buscaTituloTP();
		if(numLineaAux==-1){
			throw (ErrorHandler(TipoError::ERROR_COMPILADOR_OBTENER_TITULO_TOPDOWN));
		}

		// una vez que ya obtuvo el título, recursivamente nombra a los hijos del mismo
		std::cout << "[CompiladorTopDown]: Generando nodos" << std::endl;
		nombraHijos(archivoTD.getComienzoNodo(0),"");

		//guarda todo lo que se procesó en el archivo formateado
		guardaEnArchivo();
		*/

		std::cout << "[CompiladorTopDown]: Compilación Completa." << std::endl;
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << ", se detiene compilación." << std::endl;
	}
}
