# COMPILADOR TOP DOWN
    Repositorio creado para mantener activo el desarrollo de un compilador simple
    con el objetivo de ser utilizado en un proyecto personal
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
