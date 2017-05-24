#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  char *buf = NULL;
  char **pal = malloc( sizeof( char * ) * PIPE_BUF );
  ssize_t n;
  int tam[PIPE_BUF];

  char **programa = malloc( sizeof( char * ) * PIPE_BUF );
  char **argumentos = malloc( sizeof( char * ) * PIPE_BUF );

  int j;

  for(j=0; (n = getline(&buf, &n, stdin)) != -1; j++){
    pal[j] = malloc( PIPE_BUF );
    memcpy(pal[j], buf, n);
    pal[j][n-1] = '\0';

    programa[j] = malloc( PIPE_BUF );
    argumentos[j] = malloc( PIPE_BUF );

    programa[j][0] = '.';
    programa[j][1] = '/';
    for(int k=0; pal[j] && pal[j][k] != ' '; k++)
      programa[j][k+2] = pal[j][k];

    if(!fork()){

      if(strcmp(programa[j], "./node") == 0){
        strcpy(argumentos[j], pal[j]+5);
        //printf("node %s\n", argumentos[j]);
        printf("%s\n", argumentos[j]);
        execvp(programa[j], (char * const*) argumentos[j]);
      }else if(strcmp(programa[j], "./connect") == 0){
        strcpy(argumentos[j], pal[j]+8);
        //printf("connect %s\n", argumentos[j]);
      }else if(strcmp(programa[j], "./disconnect") == 0){
        strcpy(argumentos[j], pal[j]+11);
        //printf("disconnect %s\n", argumentos[j]);
      }else if(strcmp(programa[j], "./inject") == 0){
        strcpy(argumentos[j], pal[j]+7);
        //printf("inject %s\n", argumentos[j]);
      }

      _exit(0);
    }
  }

  for(int i=0; i<j; i++){
    int estado;

    char buff[PIPE_BUF];
    int tam;

    wait(&estado);
    if (WIFEXITED(estado)){
      tam = sprintf(buff, "%s -> %s (%d)\n", programa[i], argumentos[i], estado);
      write(1, buff, tam);
    }
  }

  return 0;
}
