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
 * comprueba si la instrucción es interna mediante check_internal
 *
 * *line: cadena de carácteres introducida en el terminal
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
 * Devuelve el número de tokens
 *
 * *line: cadena de carácteres introducida en el terminal
 * **args: argumentos que se han introducido en el terminal
 */

int parse_args(char **args, char *line){

    int i = 0;
    args[i] = strtok(line,"\t\n\r");
    printf("token %i: %s\n", i, args[i]);
    while (args[i] && args[i][0] != '#'){
        i++;
        args[i] = strtok(NULL, "\t\n\r");
        printf("token %i: %s\n",i,args[i]);
    }
    if (args[i]){
        args[i]=NULL;
        printf("token %i : %s\n",i,args[i]);
    }
    return i;
}


int internal_cd(char **args){

    printf("Esta función cambiara el directorio a la ruta indicada en los"
    	"argumentos\n");
    return 1;
}

int internal_source(char **args){

    printf("Esta función ejecutara un fichero de linias de comandos\n");
    return 1;
}

int internal_jobs(char **args){

    printf("Esta función mostrara el PID de los procesos que s'ejecutan en "
    	"segundo plano.\n");
    return 1;
}

int internal_export(char **args){

    printf("Esta función asignara valores a las variables d'entorno.\n");
    return 1;
}

int internal_exit(char **args){

	exit(0);
	return 1;
}


/*
 * Funcion check_internal
 * ----------------------
 * compara la instrucción introducida con las internas y redirecciona
 *
 * **args: argumentos que se han introducido en el terminal
 *	
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
	  else if(strcmp(args[0],"exit")==0){
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

