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

#define NOS 100

#define VAZIO 0
#define ABERTO 1

//sstruct no nodes[NOS];

int estados[NOS];
int pipes[NOS];

int stdout_original;
int stdin_original;

int avalia_comando(char** argumentos, char* aux){
  char* str = (char *)malloc(sizeof(char *) * PIPE_BUF);
  char* str_aux = (char *)malloc(sizeof(char *) * PIPE_BUF);

  if(strcmp(argumentos[0], "node") == 0){
    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);
    strcpy(str_aux, "aux_");
    strcat(str_aux, argumentos[1]);

    // Cria o pipe
    mkfifo(str, 0666);
    mkfifo(str_aux, 0666);

    int fd = open(str, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    pipes[atoi(argumentos[1])-1] = fd;

    // Cria o processo
    int pid = fork();
    if(pid == 0){
      estados[atoi(argumentos[1])-1] = ABERTO;
      node(argumentos[1], argumentos+2, stdin_original, stdout_original, aux, pipes);
      _exit(0);
    }

    //write(fd, pal, n);
  }else if(strcmp(argumentos[0], "connect") == 0){
    connect(argumentos+1, pipes);
  }else if(strcmp(argumentos[0], "inject") == 0){
    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);

    int fd = open(str, O_WRONLY | O_TRUNC);
    write(fd, aux, strlen(aux)+1);
  }/*else if(strcmp(argumentos[0], "remove") == 0){
    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);

    int fd = open(str, O_WRONLY);
    free(str);

    write(fd, "disconnect", 7);
    //(*(nodes + (atoi(argumentos[1])-1))).estado = VAZIO;
    //(nodes + atoi(argumentos[1])-1)->estado = VAZIO;
  }else if(strcmp(argumentos[0], "disconnect") == 0){
    printf("disconnect %s %s\n", argumentos[0], argumentos[1]);
    disconnect(argumentos+1);
  }*/

  free(str);
  free(str_aux);

  return 0;
}

int main(int argc, char * argv[]){
   stdin_original = dup(0);
   stdout_original = dup(1);

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

  /*for(int i=0; i<12; i++){
    int estado;
    wait(&estado);
    if (WIFEXITED(estado)){

        char str[PIPE_BUF];
        char auxxx[PIPE_BUF];
        char leitura[PIPE_BUF];
        strcpy(str, "pipe_");
        sprintf(auxxx, "%d", i+1);
        strcat(str, auxxx);

        read(pipes[i], leitura, PIPE_BUF);
        close(pipes[i]);
        printf("%d -> %s\n",i+1, leitura);
    }
  }*/

}
