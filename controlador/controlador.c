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

  int j;

  for(j=0; (n = getline(&buf, &n, stdin)) != -1; j++){
    pal[j] = malloc( PIPE_BUF );
    memcpy(pal[j], buf, n);
    pal[j][n-1] = '\0';

    char programa[PIPE_BUF];
    programa[0] = '.';
    programa[1] = '/';
    for(int k=0; pal[j] && pal[j][k] != ' '; k++)
      programa[k+2] = pal[j][k];

    char argumentos[PIPE_BUF];
    if(!fork()){
      if(strcmp(programa, "node") == 0){
        strcpy(argumentos, pal[j]+5);
        //printf("node %s\n", argumentos);

        execvp(programa, (char * const*) argumentos);
        _exit(0);
      }else if(strcmp(programa, "connect") == 0){
        strcpy(argumentos, pal[j]+8);
        //printf("connect %s\n", argumentos);
      }else if(strcmp(programa, "disconnect") == 0){
        strcpy(argumentos, pal[j]+11);
        //printf("disconnect %s\n", argumentos);
      }else if(strcmp(programa, "inject") == 0){
        strcpy(argumentos, pal[j]+7);
        //printf("inject %s\n", argumentos);
      }
    }
  }

  for(int i=0; i<j; i++){
    int estado;
    wait(&estado);
    if (WIFEXITED(estado)){
      tam[i] += sprintf(pal[i], "%s -> %d\n", pal[i], estado);
      //write(1, pal[i], tam[i]);
    }
  }

  return 0;
}
