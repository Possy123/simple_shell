#ifndef MAIN_H
#define MAIN_H

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
void execute_command(char **argv, char **env, char *path);

/*=============== HANDLE CTRL+C ============*/
void sigint_error(void);
void sigint_handler(int signum);

/*=============== TO HANDLE BUILT IN COMMANDS ============*/
void print_env(char **env);
int exit_command(char *command);
#endif
