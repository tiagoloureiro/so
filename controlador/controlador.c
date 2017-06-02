#include "componentes/funcoes.h"
#include "node.h"
#include "connect.h"
#include "disconnect.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//sstruct no nodes[NOS];
int pipes[NOS][2];
int pipes_aux[NOS];

int avalia_comando(char** argumentos, char* aux){
  char* str = (char *)malloc(sizeof(char *) * PIPE_BUF);
  char* str_aux = (char *)malloc(sizeof(char *) * PIPE_BUF);

  if(strcmp(argumentos[0], "node") == 0){
    sprintf(str, "pipe_%s", argumentos[1]);

    // Cria o pipe
    mkfifo(str, 0666);

    int fd = open(str, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    pipes_aux[atoi(argumentos[1])-1] = fd;
    pipe(pipes[atoi(argumentos[1])-1]);

    // Cria o processo
    int pid = fork();
    if(pid == 0){
      node(argumentos[1], argumentos+2, aux, pipes, pipes_aux);
      _exit(0);
    }/*else{
      char* leitura_comandos_1 = malloc( sizeof(char) * PIPE_BUF);
      read(pipes_aux[atoi(argumentos[1])-1], leitura_comandos_1, PIPE_BUF);
      printf("%s\n", leitura_comandos_1);

      close(pipes[atoi(argumentos[1])-1][1]);
      char* leitura_comandos = malloc( (sizeof( char )) * PIPE_BUF);
      read(pipes[atoi(argumentos[1])-1][0], leitura_comandos, PIPE_BUF);
      printf("%d -> %s\n", atoi(argumentos[1])-1, leitura_comandos);
      free(leitura_comandos);
    }*/

  }else if(strcmp(argumentos[0], "connect") == 0){
    connect(argumentos+1, pipes, pipes_aux);
  }else if(strcmp(argumentos[0], "inject") == 0){
    int x = pipes_aux[atoi(argumentos[1]) - 1];
    write(x, aux, strlen(aux)+1);
  }

  free(str);
  free(str_aux);

  return 0;
}

int main(int argc, char * argv[]){
  char *buf = NULL;
  ssize_t n;

  //for(int n=0; n<NOS; n++) nodes[n] = 0;
  int i;

  // Guarda todas as linhas num array de arrays de strings
  char ***argumentos = malloc( (sizeof(char *) * PIPE_BUF) * PIPE_BUF);

  // trata o input linha a linha
  for(i=0; (n = getline(&buf, &n, stdin)) > 0; i++){
    char aux[PIPE_BUF];
    char aux_2[PIPE_BUF];
    char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

    //printf("%s.\n", buf);

    memcpy(aux, buf, n);
    memcpy(aux_2, buf, n);
    aux[n-1] = '\0';
    aux_2[n-1] = '\0';

    separa(aux, argumentos);
    //printf("%s: %s\n",aux[0], aux[1]);
    avalia_comando(argumentos, aux_2);

    //printf("%s: %s\n", argumentos[0], argumentos[1]);

    argumentos++;
  }

  /*printf("tito\n");
  for(int i=0; pipes[i]; i++) close(pipes[i][0]);
  printf("tito\n");*/
  for(int i=0; i<12; i++){
    int estado;
    close(pipes[i][1]);
    wait(&estado);
    if(WIFEXITED(estado)){
      char* leitura_comandos = malloc( (sizeof( char )) * PIPE_BUF);
      read(pipes[i][0], leitura_comandos, PIPE_BUF);
      printf("%d -> %s\n", i+1, leitura_comandos);
      free(leitura_comandos);
    }
  }
}
