# COMPILADOR TOP DOWN
    Repositorio creado para mantener activo el desarrollo de un compilador simple
    con el objetivo de ser utilizado en un proyecto personal
## ARCHIVO DE CONFIGURACIÓN PARA EL PROGRAMA QUE GENERA TOPDOWN
	El programa cuenta con un archivo llamado "config" donde se pueden cambiar cosas opcionales dentro del programa.

### COMO EDITARLO:
 	borrar/cambiar/agregar el caracter que veas luego del signo = siempre respetando un espacio por valor a configurar y entre las comillas
 	ejemplo:
 		- original: caracter_tabulador: "\t"
 		- editado : caracter_tabulador: " "

### COSAS A TENER EN CUENTA:

 	- En cualquier caso de error en la lectura de preferencias en la configuración del programa, sea pérdida del archivo, nombre, mala edición del mismo o valores no permitidos
 	  el programa ignorará por completo el contenido de este y trabajará con los valores por defecto.

 	- Lista de valores por defecto:
 	  	caracter_fin_linea: ";"
		caracter_tabulador: "\t"		
		caracter_comentario: "#"
		condicion_linea: "si if"
		iteracion_linea: "repetir mientras for while"
		formato_salida: "pdf"
		imprimir_salida_programa: "false"

	- Los caracters no deben interfereir los unos con los otros, esto es analizado por el programa, si interfiere, trabaja con valores por defecto.

	- Los booleanos y el formato de salida solo pueden tener un dato.
 
 	- No se permiten caracteres o strings vacíos de por el momento

  	- Los formatos de salida admitidos por código DOT son:
   		- PDF 	(más recomendado, mejor resolución)
            	- SVG 	(más recomendado, mejor resolución)
     		- PNG
	 	- JPG
   		- EPS
     		- TIFF
       		- XDOT
	 	- PLAINTEXT

