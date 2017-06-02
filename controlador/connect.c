#include "connect.h"

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int connect(char** argumentos, int pipes[100]){
  char str[PIPE_BUF];
  int id = atoi(argumentos[0]);

  for(int i=0; argumentos[i+1]; i++){
    char pipe[PIPE_BUF];

    strcpy(str, "connect");
    for(int i=1; argumentos[i]; i++){
      strcat(str, " ");
      strcat(str, argumentos[i]);
    }

    /*strcpy(pipe, "pipe_");
    strcat(pipe, argumentos[0]);

    int fd = open(pipe, O_WRONLY | O_TRUNC);*/

    write(pipes[id-1], str, strlen(str));

    //printf("id: %s ligado a: %s\n", argumentos[0], argumentos[i+1]);

    close(pipes[id-1]);
  }
}
