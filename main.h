#ifndef MAIN_H
#define MAIN_H

#define  BUFFER_SIZE 1024

extern char **environ;

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

void token(char *input, char **argv);
<<<<<<< HEAD
void execute_command(char** argv, char** env, char* path);
char *my_getline();
=======
void execute_command(char **argv, char **env, char *path);

>>>>>>> f8bd5dec4fa857518b56b2f56c73f23a2f873b9d
/*=============== HANDLE CTRL+C ============*/
void sigint_error(void);
void sigint_handler(int signum);

/*=============== TO HANDLE BUILT IN COMMANDS ============*/
void print_env(char **env);
int exit_command(char *command);
#endif
