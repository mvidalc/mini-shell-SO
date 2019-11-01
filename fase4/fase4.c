#include "minishell.h"

char hostname[100];
char logname[100];
char cwd[1000];
char line[MAXSIZE];

/*
 * Funcion info_process
 * --------------------
 * Nos indica el estado del proceso
 */

struct info_process {

	pid_t pid;
	char status; // ’E’ o ‘D’
	char command_line[MAXSIZE]; // Comando
};

static struct info_process jobs_list[N_JOBS];

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
    
	char *punter;

	punter = fgets(line, MAXSIZE, stdin); 

	if (!punter && feof(stdin)){	//Si end of file o puntero vacio
		printf("Final del programa.\n");
		line=punter;
    }
 return line;
}

/*
 * Funcion execute_line
 * --------------------
 * En caso de que no se trate de un comando interno se crea un proceso hijo 
 *	para ejecutar el comando externo solicitado.
 *
 *	*line: cadena de carácteres introducida en el terminal
 *	
 */

int execute_line(char *line){
	
	char *args[100];
	parse_args(args,line);
	int i = check_internal(args);

    pid_t pid;
    if (i==0){
    	pid = fork();	//Si no es interno, crea un hijo con fork
    	if (pid == 0){
    		int execucio = execvp(args[0],args);
    		if (execucio == -1){
    			perror("Error");
    			exit(0);
    		}
    	}
    	else if (pid>0){
    		jobs_list[0].pid = pid;
    		while (jobs_list[0].pid != 0){
    			pause();
    		}
    	}
    }		
	return 1;
}

/*
 * Funcion ctrlc
 * -------------
 * implementa la funcionalidad de Ctrl + C dentro del programa
 *	signum: numero de la señal producida
 */

void ctrlc(int signum){
	
	signal(SIGINT, ctrlc);
	if (jobs_list[0].pid > 0){    	
		kill(jobs_list[0].pid,SIGINT);
    }
    printf("\n");
}

/*
 * Funcion reaper
 * -------------
 * Envia una señal al proceso que deba terminar
 * signum: numero de la señal producida
 */

void reaper(int signum){
    signal(SIGCHLD,reaper);
    int end = 0;
  
    while ((end=waitpid(-1,NULL,WNOHANG))>0){
    	printf("Proceso hijo acabado: %d\n", end);
    }
    jobs_list[0].pid = 0;
}

/*
 * Funcion parse_args
 * ------------------
 * Separa la instrucción introducida en tokens
 *
 **line: cadena de carácteres introducida en el terminal
 * **args: argumentos que se han introducido en el terminal
 *
 *	retorna: numero de tokens
 */
int parse_args(char **args, char *line){

	int i = 0;
    args[i] = strtok(line," \t\r\n");   
    while (args[i] && args[i][0] != '#'){
    	i++;
    	args[i] = strtok(NULL," \t\r\n");
    }
	args[i]=NULL;
    return i;
}

/*
 * Funcion internal_cd
 * -------------------
 * Redirecciona a la ruta indicada en la instrucción
 * **args: argumento introducido en el terminal
 */

int internal_cd(char **args){

	if (chdir(args[1])==-1){
		perror("Error");
	}
	else {
		getcwd(cwd,sizeof(cwd));
		printf("%s\n", cwd);
	}
    return 1;
}

/*
 * Funcion internal_source
 * -----------------------
 * Evalua el archivo indicado como una lista de comandos
 */

int internal_source(char **args){
	if (args[1]==NULL){
		printf(stderr,"Error, falta el nombre del archivo de comandos\n");
		return -1;
	}
	else{
		FILE *fp;
		char linea[100];
		fp = fopen(args[1],"r");
		if (fp == NULL){
        	printf("Error abriendo el archivo\n");
            return(-1);
        }
    	while (fgets (linea, 100, fp)!=NULL){
			execute_line(linea);
		} 
		fclose(fp);
        return 1;
    }
}

int internal_jobs(char **args){

	printf("Esta función mostrara el PID de los procesos que s'ejecutan en "
    	"segundo plano.\n");
    return 1;
}

/*
 * Funcion internal_export
 * -----------------------
 * Asigna un valor a una variable
 */

int internal_export(char **args){

	char *nom = strtok(args[1],"=");
	char *valor = strtok(NULL," ");

    if (nom != NULL && valor !=NULL){
    	setenv(nom,valor,1);
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
}

/*
 * Funcion check_internal
 * ----------------------
 * Compara la instrucción introducida con las internas y redirecciona
 */

int check_internal(char **args){

	if (args[0]==NULL) return -1;
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
	else {     
		return 0;
	}
} 

/*
 * Funcion main
 * ------------
 * Metodo principal que llama a los demás
 */

int main(){

	signal(SIGCHLD, reaper);
    signal(SIGINT, ctrlc);

	char line[MAXSIZE];
	gethostname(hostname,100);
	strcpy(logname,getenv("LOGNAME"));
	while(read_line(line)){
		execute_line(line);
		memset(line,'\0',sizeof(line));	//vaciamos
	}
	return 0;
}
