#include "node.h"
#include "componentes/funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[], char* aux, int pipes[NOS][2], int pipes_aux[NOS]){
  int onde_escreve[NOS][NOS];
  int it = 0;
  int id_int = atoi(id);
  int n = 0;

  int in=0, out=1;
  int link[2];

  while(1){
    char** argumentos = malloc( (sizeof(char *)) * PIPE_BUF);
    char* leitura_comandos = malloc( sizeof(char) * PIPE_BUF);

    read(pipes_aux[atoi(id)-1], leitura_comandos, PIPE_BUF);
    //printf("%s -> %s\n", id, leitura_comandos);

    char str[PIPE_BUF];
    strcpy(str, leitura_comandos);

    n = separa(str, argumentos);

    if(strstr(leitura_comandos, "connect")){
      printf("CONNECT: %s -> %s\n", id, leitura_comandos);
      for(int i=1; argumentos[i]; i++){
        onde_escreve[id_int-1][i-1] = pipes[atoi(argumentos[i]) - 1][0];
      }
    }else if(strstr(leitura_comandos, "inject")){
      printf("INJECT: %s -> %s\n", id, leitura_comandos);

      //dup2(1, pipes[id_int-1]);
      dup2 (pipes[id_int-1][1], STDOUT_FILENO);
      close(pipes[id_int-1][0]);
      close(pipes[id_int-1][1]);
      execvp(argumentos[2], argumentos+3);

      for(int k=0; k<n; k++){
        dup2 (onde_escreve[id_int-1][k], STDIN_FILENO);
        close(onde_escreve[id_int-1][k]);
        execvp(argv[0], argv+1);
      }

    }

    free(argumentos);
    free(leitura_comandos);
  }

  return 0;
}
