#include <iostream>
#include <ostream>
#include <fstream>
#include "LineaTopDown.h"
int main(){
	std::ifstream archivo("topdown");
	LineaTopDown linea;
	if (!archivo){
		std::cout << "apertura de archivo fallida" << std::endl;
		return 1;
	}
	std::cout << "archivo abierto exitosamente, se extraerá la primer línea del archivo y sus datos" << std::endl;
	linea.leeDesdeArchivo(archivo);
	std::cout << "la línea extraída es: " << linea << std::endl;
	std::cout << "numero de línea: " << linea.getNumero() << " numero de dentado: " << linea.getDentado() << std::endl;
	std::cout << "se extraerá la segunda línea" << std::endl;
	linea.leeDesdeArchivo(archivo);
	std::cout << "la línea extraída es: " << linea << std::endl;
	std::cout << "numero de línea: " << linea.getNumero() << " numero de dentado: " << linea.getDentado() << std::endl;
	archivo.close();
	return 0;
}
