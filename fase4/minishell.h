#define _POSIX_C_SOURCE 200112L
#define PROMPT "$"
#define MAXSIZE 70
#define N_JOBS 1000

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAGENTA_T   "\x1b[35m"
#define VERDE_T     "\x1b[32m"
#define RESET_COLOR "\x1b[0m"

char *read_line(char *line);
int execute_line(char *line);
void ctrlc(int signum);
void reaper(int signum);
int parse_args(char **args, char *line);
int internal_cd(char **args);
int internal_source(char **args);
int internal_jobs(char **args);
int internal_export(char **args);
int internal_exit(char **args);
int check_internal(char **args);
