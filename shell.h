#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_line(char *lines, char **argv, char **envp);
void token(char *lines, char **argv);
/*void execute_search(char *input);*/
/*void token_path(char *path_ctrl, char **path);*/

#endif
