#define _POSIX_C_SOURCE 200112L
#define PROMPT "$"
#define MAXSIZE 70

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#define MAGENTA_T   "\x1b[35m"
#define VERDE_T     "\x1b[32m"
#define RESET_COLOR "\x1b[0m"

char *read_line(char *line);
int execute_line(char *line);
int parse_args(char **args, char *line);
int internal_cd(char **args);
int internal_source(char **args);
int internal_jobs(char **args);
int internal_export(char **args);
int check_internal(char **args);

