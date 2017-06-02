#include "connect.h"

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int connect(char** argumentos, int pipes[NOS][2], int pipes_aux[NOS]){
  char* str = (char *)malloc(sizeof(char *) * PIPE_BUF);
  int id = atoi(argumentos[0]);
  int tam = 0;

  tam = sprintf(str, "connect %s", argumentos[1]);
  for(int i=2; argumentos[i]; i++){
    tam += sprintf(str, "%s %s", str, argumentos[i]);
  }

  write(pipes_aux[id-1], str, tam);

}
