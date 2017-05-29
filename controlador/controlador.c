#include "node.h"

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

int connect(char** argumentos){
  char str[PIPE_BUF];

  for(int i=0; argumentos[i+1]; i++){
    char pipe[PIPE_BUF];

    strcpy(str, "connect ");
    strcat(str, argumentos[i+1]);

    strcpy(pipe, "pipe_");
    strcat(pipe, argumentos[0]);

    int fd = open(pipe, O_WRONLY);

    write(fd, str, strlen(str));

    printf("id: %s ligado a: %s\n", argumentos[0], argumentos[i+1]);

    close(fd);
  }
}

int avalia_comando(char** argumentos, ssize_t n){
  char str[PIPE_BUF];

  if(strcmp(argumentos[0], "node") == 0 && nodes[atoi(argumentos[1])-1] == VAZIO){

    strcpy(str, "pipe_");
    strcat(str, argumentos[1]);

    // Cria o pipe
    mkfifo(str, 0666);

    /*for(int i=2; argumentos[i]; i++)
      printf("%s | ", argumentos[i]);
    printf("\n");*/

    // Cria o processo
    int pid = fork();
    if(pid == 0){
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

  // Criar 100 named pipes
  /*for(int n=0; n<NOS; n++){
    char str[PIPE_BUF];
    sprintf(str, "pipe_%d", n+1);
    mkfifo(str, 0666);
  }*/

  //for(int n=0; n<NOS; n++) nodes[n] = fork();

  //memset
  char ***argumentos = malloc( (sizeof(char *) * PIPE_BUF) * PIPE_BUF);

  for(i=0; (n = getline(&buf, &n, stdin)) != -1; i++){
    char aux[PIPE_BUF];
    char **argumentos = malloc( (sizeof(char *)) * PIPE_BUF);

    //printf("%s.\n", buf);

    memcpy(aux, buf, n);
    aux[n-1] = '\0';

    separa(aux, argumentos+i);
    avalia_comando(argumentos+i, n);
  }

}
