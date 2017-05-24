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
  char pal[PIPE_BUF];
  ssize_t n;
  int coluna;
  int tam;

  int j = 0;
  int linhas[PIPE_BUF];
  int linha_atual = 0;
  int aux;

  char *comando[PIPE_BUF];

  if(argc > 2){
    while((n = getline(&buf, &n, stdin)) != -1){
      linha_atual++;

      tam = 0;

      memcpy(pal, buf, n);
      pal[n-1] = '\0';

      if(!fork()){
        for(int i=2; i<argc; i++){
          if(argv[i][0] == '$'){
            coluna = atoi(argv[i]+1);
            strcpy(argv[i], get_coluna_str(pal, coluna));
          }
          sleep(4-j);
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
        tam += sprintf(pal, "%s:%d\n", pal, estado);
        write(1, pal, tam);
      }
    }
  }
  return 0;
}
