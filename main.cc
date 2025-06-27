#include <iostream>
#include "ArchivoTopDown.h"
int main(){
	ArchivoTopDown archivoTD;
	std::cout << "se intentará abrir el archivo de top down y se contarán las líneas" << std::endl;
	archivoTD.leeDesdeArchivo();
	return 0;
}
