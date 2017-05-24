#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  char *buf = NULL;
  char **pal = malloc( sizeof( char * ) * PIPE_BUF );
  ssize_t n;
  int tam[PIPE_BUF];

  int j = 0;
  int linha_atual = 0;
  int aux;
  int coluna;

  char *comando[PIPE_BUF];

  if(argc > 2){
    while((n = getline(&buf, &n, stdin)) != -1){
      linha_atual++;
      tam[j] = 0;

      pal[j] = malloc( PIPE_BUF );
      memcpy(pal[j], buf, n);
      pal[j][n-1] = '\0';

      if(!fork()){
        for(int i=2; i<argc; i++){
          if(argv[i][0] == '$'){
            coluna = atoi(argv[i]+1);
            strcpy(argv[i], get_coluna_str(pal[j], coluna));
          }
          //sleep(4-j);
        }
        execvp(argv[1], argv+1);
        _exit(0);
      }
      j++;
    }

    for(int i=0; i<j; i++){
      int estado;
      wait(&estado);
      if (WIFEXITED(estado)){
        tam[i] += sprintf(pal[i], "%s:%d\n", pal[i], estado);
        write(1, pal[i], tam[i]);
      }
    }
  }
  return 0;
}
