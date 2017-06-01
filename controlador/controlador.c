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
int ligacoes[NOS][NOS];
int in[NOS];
int out[NOS];
char comandos[NOS][PIPE_BUF][PIPE_BUF];

int stdout_original;
int stdin_original;

int avalia_comando(char** argumentos, char* aux){
  char* str = (char *)malloc(sizeof(char *) * PIPE_BUF);

  if(strcmp(argumentos[0], "node") == 0){
    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);

    // Cria o pipe
    mkfifo(str, 0666);
    free(str);

    // Cria o processo
    int pid = fork();
    if(pid == 0){
      node(argumentos[1], argumentos+2, stdin_original, stdout_original);
      _exit(0);
    }

    //write(fd, pal, n);
  }else if(strcmp(argumentos[0], "connect") == 0){
    connect(argumentos+1);
  }else if(strcmp(argumentos[0], "inject") == 0){
    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);

    int fd = open(str, O_WRONLY);
    free(str);

    write(fd, aux, strlen(aux));
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
    char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

    //printf("%s.\n", buf);

    memcpy(aux, buf, n);
    aux[n-1] = '\0';

    separa(aux, argumentos);
    //printf("%s: %s\n",aux[0], aux[1]);
    avalia_comando(argumentos, aux);

    //printf("%s: %s\n", argumentos[0], argumentos[1]);

    argumentos++;
  }

  for(int i=0; i<3; i++){
    int estado;
    wait(&estado);
    if (WIFEXITED(estado)){
      printf("\tno %d estado=%d\n", i+1, estado);
    }
  }

}
