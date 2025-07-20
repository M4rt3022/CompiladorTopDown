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

//el dentado del archivo solo debe tener una línea sin dentado y las demás por lo menos con uno
int CompiladorTopDown::revisaCorrectoDentado(){
	std::cout << "[CompiladorTopDown]: Revisando dentado en el archivo" << std::endl;
	int cantidadLineas = archivoTD.getCantidadLineas();
	int i = archivoTD.getComienzoNodo(1);
	for(;i<cantidadLineas;i++){
		//debe fijarse que el dentado sea el correcto y que la línea no esté vacía
		if((archivoTD.getDentadoLinea(i)<1)&&(0 == archivoTD.getBoolLinea(i, LineaTopDown::flag::flag_linea_vacía))){
			return 1;
		}
	}
	return 0;
}

//método que toma desde un número de línea en específico y junta su contenido hasta encontrar un caracter_fin_linea
//utiliza el orden enviado como referencia y lo modifica
void CompiladorTopDown::juntaContenido(const int & numLinea,std::string& salida){
	salida = "";
	int dentado;
	//primero debo revisar que el orden exista
	if(numLinea > archivoTD.getCantidadLineas()){
		return ;
	} 
	int numLineaAux = numLinea;
	//acá debe ir almacenando los contenidos en el string auxiliar y luego devolverlo 
	dentado = archivoTD.getDentadoLinea(numLineaAux);
	for(; numLineaAux < archivoTD.getCantidadLineas() ;numLineaAux++){
		//si pasa por una línea con un dentado diferente a donde comenzó, deja de juntar contenido
		//	ESTO TIENE UN ERROR: terminará de juntar contenido si encuentra una línea con otro dentado y que tenga
		//	el flag, esto puede generar que junte contenido de una línea sin que termine en ';'
		if(archivoTD.getDentadoLinea(numLineaAux)!=dentado &&
			!archivoTD.getBoolLinea(numLineaAux, LineaTopDown::flag::flag_linea_vacía)){
			break;
		}
		//si la línea está vacía, me salteo la línea
		if(archivoTD.getBoolLinea(numLineaAux, LineaTopDown::flag::flag_linea_vacía)){
			continue;
		}
		archivoTD.getContenidoLinea(numLineaAux, salida);
		// si encontró un final de línea, termina de juntar contenido
		if(archivoTD.getBoolLinea(numLineaAux,LineaTopDown::flag::flag_caracter_fin_linea)){
			break;
		}
	}
	return;
}

//método que cuenta cuantos hijos tiene un nodo y lo devuelve;
int CompiladorTopDown::cuentaHijos(const int& numeroLinea){
	int cantHijos = 0;
	if(numeroLinea > archivoTD.getCantidadLineas()){
		return 1;
	}
	int cantidadTabs = archivoTD.getDentadoLinea(numeroLinea);
	//debo saltear la cantidad de líneas que tenga el mismo nodo
	int dondeTermina = numeroLinea;
	while(dondeTermina < archivoTD.getCantidadLineas()&&archivoTD.getBoolLinea(dondeTermina,LineaTopDown::flag::flag_caracter_fin_linea)==0){
		dondeTermina++;
	}
	//ahora cuenta la cantidad de hijos luego de esa línea
	dondeTermina++;
	for(int i = dondeTermina; i < archivoTD.getCantidadLineas();i++){
		if(archivoTD.getBoolLinea(i, LineaTopDown::flag::flag_linea_vacía)){
			continue;
		}
		if(cantidadTabs+1==archivoTD.getDentadoLinea(i)&&1==archivoTD.getBoolLinea(i,LineaTopDown::flag::flag_caracter_fin_linea)){
			cantHijos++;
		}
		if(cantidadTabs>=archivoTD.getDentadoLinea(i)){
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

		// una vez que ya obtuvo el título, recursivamente nombra a los hijos del mismo
		std::cout << "[CompiladorTopDown]: Generando nodos" << std::endl;
		nombraHijos(archivoTD.getComienzoNodo(0),"");

		//guarda todo lo que se procesó en el archivo formateado
		guardaEnArchivo();

		std::cout << "[CompiladorTopDown]: Compilación Completa." << std::endl;
	}
	catch(const ErrorHandler& error){
		std::cerr << "[ERROR]: " << error.what() << ", se detiene compilación." << std::endl;
	}
}
