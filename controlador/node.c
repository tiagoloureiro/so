#include "node.h"
#include "componentes/funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

int node(char* id, char* argv[], int stdin_original, int stdout_original){
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

    printf("%s\n", str_in);

    if( strcmp(str_in, "connect") ){
      strcpy(str_out, "pipe_");
      strcat(str_out, str_in+8);

      out = open(str_out, O_WRONLY);
      if(out < 0) _exit(0);

      //dup2(in, 0);
      //dup2(out, 1);

    }else if( strcmp(str_in, "disconnect") ){
      printf("disconnect id: %s\n", id);

      /*dup2(stdin_original, in);
      dup2(stdout_original, out);
      _exit(0);*/
    }else if( strstr(str_in, "inject") ){
      printf("inject id: %s\n", id);

      char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

      separa(str_in, argumentos);

      execvp(argumentos[0], argumentos+1);

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
}
