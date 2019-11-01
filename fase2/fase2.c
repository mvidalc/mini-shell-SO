#include "minishell.h"

char hostname[100];
char logname[100];
char cwd[1000];

/*
 * Funcion read_line
 * -----------------
 * Imprime el prompt y lee la instruccion a ejecutar
 *
 *	*line: cadena de carácteres introducida en el terminal
 *	retorna: la linia con el prompt al principio
 */

char *read_line(char *line){

	printf(""MAGENTA_T"%s@%s"VERDE_T"~%s%s"
		RESET_COLOR" ",logname,hostname,cwd,PROMPT);
	fflush(stdout);
	fgets(line, MAXSIZE, stdin);
	return line;
}

/*
 * Funcion execute_line
 * --------------------
 * comprueba si la instrucción es interna
 *
 *	*line: cadena de carácteres introducida en el terminal
 *	retorna: la deducción de check_internal
 */

int execute_line(char *line){

	char *args[100];
	parse_args(args,line);
	return check_internal(args);
}

/*
 * Funcion parse_args
 * ------------------
 * Separa la instrucción introducida en tokens
 * Devuelve el numero de tokens
 *
 *	*line: cadena de carácteres introducida en el terminal
 * **args: argumentos que se han introducido en el terminal
 */

int parse_args(char **args, char *line){

	int i = 0;
	args[i] = strtok(line," \t\r\n");
	while (args[i] && args[i][0] != '#'){
		i++;
		args[i] = strtok(NULL," \t\r\n");
	}
	if (args[i]){
		args[i]=NULL;
	}
	return i;
}

/*
 * Funcion internal_cd
 * -------------------
 * Redirecciona a la ruta indicada en la instrucción
 *
 *	**args: argumento introducido en el terminal
 */

int internal_cd(char **args){
	
	if (chdir(args[1])==-1){
		fprintf(stderr,"Error: Directorio incorrecto\n");
	}
	else {
		getcwd(cwd,sizeof(cwd));
		printf("%s\n", cwd);
	}
	return 1;
}

int internal_source(char **args){

	printf("Aquesta funció executarà un fitxer de línies de comandes\n");
	return 1;
}

int internal_jobs(char **args){

	printf("Aquesta funció mostrarà el PID dels processos que s'executen "
		"en segon pla.\n");
	return 1;
}

/*
 * Funcion internal_export
 * -----------------------
 * Asigna un valor a una variable
 *	**args: argumento introducido en el terminal
 */

int internal_export(char **args){

	char *nom = strtok(args[1],"=");
	char *valor = strtok(NULL," ");

    if (nom != NULL && valor !=NULL){
    	printf("Valor antiguo de %s : %s\n",nom,getenv(nom));
		setenv(nom,valor,1);
		printf("Valor nuevo de %s : %s\n",nom, getenv(nom));
    }
    else {
	printf("Error en la sintaxis de los argumentos. "
		"Utilización: VARIABLE=valor \n");
    }
	return 1;
}

/*
 * Funcion internal exit
 * ---------------------
 * Finaliza la ejecución del programa
 */

int internal_exit(char **args){

	exit(0);
	return 1;
}

/*
 * Funcion check_internal
 * ----------------------
 * compara la instrucción introducida con las internas y redirecciona
 */

int check_internal(char **args){

	if(strcmp(args[0],"cd")==0){
		return internal_cd(args);
	}

	else if(strcmp(args[0],"jobs")==0){
		return internal_jobs(args);
	}

	else if(strcmp(args[0],"export")==0){
		return internal_export(args);
	}

	else if(strcmp(args[0],"source")==0){
		return internal_source(args);
	}
	
	else if (strcmp(args[0],"exit")==0){
		return internal_exit(args);
	}

	else{
        printf("Lo que habeis introducido no forma part de un "
            "comando interno. \n"); 
	}
	return 0;
} 

/*
 * Funcion main
 * ------------
 * Metodo principal que llama a los demás
 */

int main(){

	char line[MAXSIZE];
	gethostname(hostname,100);
	strcpy(logname,getenv("LOGNAME"));
	while(read_line(line)){
		execute_line(line);
	}
	return 0;
}
