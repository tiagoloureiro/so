#include "node.h"
#include "connect.h"

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

int nodes[NOS];


int separa(char *pal, char** argumentos){
  char* pch;

  pch = strtok (pal," ");

  for (int k=0; pch != NULL; k++){
    argumentos[k] = malloc( PIPE_BUF );
    sprintf(argumentos[k], "%s", pch);
    pch = strtok (NULL, " ");
  }

  return 0;
}

int avalia_comando(char** argumentos){
  char str[PIPE_BUF];

  if(strcmp(argumentos[0], "node") == 0 && nodes[atoi(argumentos[1])-1] == VAZIO){

    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);

    // Cria o pipe
    mkfifo(str, 0666);

    // Cria o processo
    int pid = fork();
    if(pid == 0){
      //alarm(60);
      node(argumentos[1], argumentos+2);
      _exit(0);
    }
    nodes[atoi(argumentos[1])-1] = ABERTO;
    //write(fd, pal, n);
  }else if(strcmp(argumentos[0], "connect") == 0){
    connect(argumentos+1);
  }

  return 0;
}

int main(int argc, char * argv[]){
  char *buf = NULL;
  ssize_t n;

  for(int n=0; n<NOS; n++) nodes[n] = 0;
  int i;

  // Guarda todas as linhas num array de arrays de strings
  char ***argumentos = malloc( (sizeof(char *) * PIPE_BUF) * PIPE_BUF);

  // trata o input linha a linha
  for(i=0; (n = getline(&buf, &n, stdin)) != -1; i++){
    char aux[PIPE_BUF];
    char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

    //printf("%s.\n", buf);

    memcpy(aux, buf, n);
    aux[n-1] = '\0';

    separa(aux, argumentos+i);
    avalia_comando(argumentos+i);
  }

}
