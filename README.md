# COMPILADOR TOP DOWN
Programa que toma un archivo de texto y genera un esquema de jerarquía tipo
top-down.

## COMO SE ESCRIBE
Cada línea es transformada a un nodo, así que cada línea debe contener:
- Dentado (para saber donde colocar el nodo)
- Contenido (que irá dentro del nodo)
- Final de linea (delimita hasta donde llega el contenido de un nodo)
Se permite escribir líneas con solo dentado y contenido, pero solo si luego se le pone el caracter_fin_linea reservado al final

### EJEMPLO
	Leer 10 numeros diferentes
 	a cero;
 		repetir hasta 10 numeros o hasta que el numero sea igual a cero;
   			leer un numero por teclado;
			si el numero es cero;
	 			dejar de leer;
El programa revisa solo el dentado de la línea de comienzo de un nodo, esto quiere decir que para el nodo que dice "Leer 10 numeros diferentes a cero"
solo revisará que la línea "Leer 10 numeros diferentes" tenga un dentado adecuado

El programa tomará que el nodo de menor dentado dentro del archivo es el título y los demás son nodos hijos, a cada uno se le asigna un orden
	 			
## ARCHIVO DE CONFIGURACIÓN PARA EL PROGRAMA QUE GENERA TOPDOWN
El programa cuenta con un archivo llamado "config" donde se pueden cambiar cosas opcionales dentro del programa.

### COMO EDITARLO:
 borrar/cambiar/agregar el caracter que veas luego de los dos puntos (:)
 siempre respetando un espacio en blanco por valor a configurar y entre las comillas
 	ejemplo:
  - iteracion_linea: "repetir para mientras for while"
  - formato_salida: "svg"
  - imprimir_salida_programa: "false"

### COSAS A TENER EN CUENTA:

 En cualquier caso de error en la lectura de preferencias en la configuración del programa,
sea pérdida del archivo, nombre, mala edición del mismo o valores no permitidos
 el programa ignorará por completo el contenido de este y trabajará con los valores por defecto.
 
 - Lista de valores por defecto:
   	- caracter_fin_linea: ";"
   	- caracter_tabulador: "\t"
   	- caracter_comentario: "#"
   	- condicion_linea: "si if"
   	- iteracion_linea: "repetir mientras for while"
   	- formato_salida: "pdf"
   	- imprimir_salida_programa: "false"
- NINGUNA CADENA DE CARACTERES DENTRO DE UNA CONFIGURACIÓN DEBE SER IGUAL A OTRA.
  
- Los booleanos y el formato de salida solo pueden tener un dato.
  
- No se permiten caracteres o strings vacíos de por el momento.
  
- Los formatos de salida admitidos por código DOT son: PDF, SVG, PNG, JPG, EPS, TIFF, XDOT, Plaintext.

- Cualquier palabra ingresada dentro de las comillas será transformada automáticamente a minúscula para evitar confusiones.
