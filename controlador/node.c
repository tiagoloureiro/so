#include "node.h"
#include "componentes/funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[], int stdin_original, int stdout_original, char* aux){
  char onde_escreve[100][PIPE_BUF];
  char leitura_comandos[PIPE_BUF];
  char aux_l[PIPE_BUF];
  char comandos[PIPE_BUF];
  int it = 0;

  /*char str[PIPE_BUF];
  strcpy(str, "aux_");
  strcat(str, id);
  int aux = open(str, O_WRONLY);
  if(aux < 0) _exit(0);*/

  int in=0, out=1;

  strcpy(leitura_comandos, "pipe_");
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

    /*int file = open("tito", O_WRONLY);

    write(file, comandos, PIPE_BUF);*/
  }
}

/*int node(char* id, char* argv[], int stdin_original, int stdout_original){
  char str_in[PIPE_BUF];
  char str_out[PIPE_BUF];

  strcpy(str_in, "pipe_");
  strcat(str_in, id);

  int in = 0;
  int out = 1;

  //(nodes + (atoi(id)-1))->estado = ABERTO;
  //nodes[atoi(id)-1].estado = 1;

  while(1){
    in = open(str_in, O_RDONLY);
    if(in < 0) _exit(0);

    read(in, str_in, PIPE_BUF);

    //printf("%s\n", str_in);

    if( strcmp(str_in, "connect") ){
      strcpy(str_out, "pipe_");
      strcat(str_out, str_in+8);

      out = open(str_out, O_WRONLY);
      if(out < 0) _exit(0);


    }else if( strcmp(str_in, "disconnect") ){
      printf("disconnect id: %s\n", id);*/

      /*dup2(stdin_original, in);
      dup2(stdout_original, out);
      _exit(0);*/
    /*}else if( strstr(str_in, "inject") ){
      printf("inject id: %s\n", id);

      char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

      separa(str_in, argumentos);

      dup2()
      execvp(argumentos[1], argumentos+2);

      printf("tito\n");
      write(1, "tito", 5);

      break;

      if( strcmp(argv[0], "window") == 0 ){
        // window
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "filter") == 0 ){
        // filter
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "spawn") == 0 ){
        // spawn
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "const") == 0 ){
        // const
        execvp(argv[0], argv+1);
      }else if( strcmp(argv[0], "tee") == 0){
        // tee
        execvp(argv[0], argv+1);
      }
    }
  }

  return 0;
}*/
