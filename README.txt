ARCHIVO README -> PRÁCTICA 2 S.O. "MINISHELL"
Alumnes: Antonio Rotger López (43224332H) | Miguel Vidal Coll (43225456S) 

En este archivo se comentaran las diferentes fases de la práctica.


| FASE 1: |
En esta fase se pide que se lea una línea de argumentos introducidos por teclado y se haga pedazos de manera que se puedan reconocer los comandos internos de nuestro Minishell y los que no lo son. Cada vez que se pide una línea, se ha de imprimir por pantalla el Prompt ($) antes de la línea como en el Shell original de Linux. Opcionalmente, se podían imprimir las variables de entorno necesarias para que fuera más parecido al Shell original.

Así pues, se han declarado dos variables globales de tipo char, que contendrán el nombre del usuario de la sesión y el nombre de la máquina que se está utilizando. Dentro del main, antes de entrar en el bucle infinito de readline, se cogen las variables de entorno. Después, dentro de la función read_line (), se imprime usuario @ nompc ~ PROMPT y así queda igual al Shell original.Varem decidió imprimir de color magenta del usuario y de color verde el prompt. Aparte de esta mejora opcional, hemos decidido indicar cuando no se reconoce el pedido como una interna de manera que se indica al usuario que lo ha introducido no forma parte de ningún pedido interna (cd, export, source, jobs ). Este mensaje s'el.liminarà posteriormente ya que se llevará a cabo la ejecución de comandos externos a nuestro Minishell.


| FASE 2: |
En esta fase, se pide la implementación de los comandos internos cd (Change Directory) y export (Cambiar valor de variables de entorno). En ambos casos, se debe imprimir el resultado de llevar a cabo la operación y, en caso de error, imprimir un mensaje de error por pantalla (en el caso del export, indicar la sintaxis correcta para emplear el pedido).

También, lo que hemos hecho es que cada vez que se cambia el directorio con cd, se actualiza una variable global "CWD" (Current Working Directory), lo imprimimos en el read_line () justo antes del Prompt, por lo que siempre se muestra el directorio en el que estamos trabajando.


|FASE 3: |
En esta fase, se pide la implementación del comando interno source y la ejecución de comandos externos a nuestro Minishell. En el caso en que no se reconoce ningun comando interno, ya no se imprime un mensaje que indica que no existe sino que se genera un ID de Proceso (PID) y se lleva a cabo la ejecución del comando externo. Además también se han eliminado los mensajes que imprimían el nuevo directorio y el valor de las variables en la función export.

|FASE 4: |
En esta fase, se pide que se gestione el manejo de las señales SIGINT (Interrupción) y SIGCHLD (El proceso hijo ha terminado). También, hemos gestionado el final de entrada llevado a cabo con CTRL-D. En la fase 4, el Reaper (Enterrador de hijos) imprime un mensaje por pantalla cada vez que un hijo termina, seguido de su correspondiente PID. En fases posteriores se eliminarà.


|FASE 5: |
En esta fase se pedía la implementación del comando interno jobs y la gestión de los procesos en background (indicado con &). Opcionalment es podia dur a terme la implementació de les comandes fg i bg però per falta de temps hem optat per a fer que s'ignori el CTRL-Z. 

|FASE 6:|
En esta fase se pide la implementación del redireccionamiento de los pedidos externas para que guarden la salida a un archivo.

|FASE 7: |
En esta fase se pide la implementación de un nuevo readline a partir de la librería de manera que éste permita guardar los pedidos anteriores y permita moverse sobre la línea escrita para llevar a cabo correcciones de un solo carácter ...

|Makefile: |
Para emplear el archivo MAKEKFILE, y así compilar los archivos fuente de la fase deseada, debe situarse en la carpeta donde están los archivos fuente a compilar (con sus respectivas cabeceras) y se debe introducir "make all" o "make". A continuación, si no ha habido ningún problema, se habrá generado un ejecutable con el nombre faseX donde la X ha de sustituirse por el número de la fase que se ha compilado. Para ejecutarlo, se debe introducir "./faseX" donde X vuelve a ser el número de la fase que se ha compilado.
También ha habido un problema de última hora a la hora de imprimir el prompt a color de esta forma y hemos optado a dejarlo del color predefinido.


