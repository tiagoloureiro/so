#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct comandos{
  char programa[PIPE_BUF];
  char argumentos[PIPE_BUF];
} *COMANDOS;

int main(int argc, char * argv[]){
  char *buf = NULL;
  char **pal = malloc( sizeof( char * ) * PIPE_BUF );
  ssize_t n;
  int tam[PIPE_BUF];

  COMANDOS *cmd;

  int j;

  for(j=0; (n = getline(&buf, &n, stdin)) != -1; j++){
    pal[j] = malloc( PIPE_BUF );
    memcpy(pal[j], buf, n);
    pal[j][n-1] = '\0';

    cmd[j] = malloc(sizeof(COMANDOS));

    cmd[j]->programa[0] = '.';
    cmd[j]->programa[1] = '/';
    for(int k=0; pal[j] && pal[j][k] != ' '; k++)
      cmd[j]->programa[k+2] = pal[j][k];

    if(!fork()){
      if(strcmp(cmd[j]->programa, "node") == 0){
        strcpy(cmd[j]->argumentos, pal[j]+5);
        //printf("node %s\n", argumentos);

        execvp(cmd[j]->programa, (char * const*) cmd[j]->argumentos);
        _exit(0);
      }else if(strcmp(cmd[j]->programa, "connect") == 0){
        strcpy(cmd[j]->argumentos, pal[j]+8);
        //printf("connect %s\n", argumentos);
      }else if(strcmp(cmd[j]->programa, "disconnect") == 0){
        strcpy(cmd[j]->argumentos, pal[j]+11);
        //printf("disconnect %s\n", argumentos);
      }else if(strcmp(cmd[j]->programa, "inject") == 0){
        strcpy(cmd[j]->argumentos, pal[j]+7);
        //printf("inject %s\n", argumentos);
      }
    }
  }

  for(int i=0; i<j; i++){
    tam[i] = 0;
    int estado;
    wait(&estado);
    char *buff;
    if (WIFEXITED(estado)){
      tam[i] += sprintf(buff, "%s -> %s (%d)\n", cmd[j]->programa, cmd[j]->argumentos, estado);
      write(1, buff, tam[i]);
    }
  }

  return 0;
}
