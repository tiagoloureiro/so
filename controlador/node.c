#include "node.h"
#include "componentes/funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[], int in_o, int out_o, char* aux, int pipes[100]){
  char onde_escreve[100][PIPE_BUF];
  char* leitura_comandos = malloc( (sizeof( char )) * PIPE_BUF);
  char* aux_l = malloc( (sizeof( char )) * PIPE_BUF);
  char* comandos = malloc( (sizeof( char )) * PIPE_BUF);
  int it = 0;

  /*char str[PIPE_BUF];
  strcpy(str, "aux_");
  strcat(str, id);
  int aux = open(str, O_WRONLY);
  if(aux < 0) _exit(0);*/

  int in=0, out=1;

  read(pipes[atoi(id)-1], leitura_comandos, PIPE_BUF);

  printf("%s -> %s\n", id, leitura_comandos);

  free(leitura_comandos);

  /*strcpy(leitura_comandos, "pipe_");
  strcat(leitura_comandos, id);
  in = open(leitura_comandos, O_RDONLY);
  if(in < 0) _exit(0);

  strcpy(aux_l, "aux_");
  strcat(aux_l, id);
  int aux_in_out = open(aux_l, O_RDONLY);
  if(aux_in_out < 0) _exit(0);

  while(1){
    break;
    read(in, comandos, PIPE_BUF);

    //printf("%s -> %s, %s\n", id, leitura_comandos, comandos);

    if(strstr(comandos, "inject")){
      char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

      separa(comandos, argumentos);

      //printf("inject: %s\n", aux+7);
      //printf("node: %s\n", argv[0]);

      dup2(1, aux_in_out);
      execvp(argumentos[1], argumentos+2);
      dup2(0, aux_in_out);
      execvp(argv[0], argv+1);
      break;
    }else if(strstr(comandos, "connect ")){
      char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);
      separa(comandos, argumentos);

      for(int i=1; argumentos[i]; i++){
        strcpy(onde_escreve[i-1], argumentos[i]);
      }

      //for(int i=0; onde_escreve[i]; i++) printf("%s\n", onde_escreve[i]);
    }

  }*/
}
