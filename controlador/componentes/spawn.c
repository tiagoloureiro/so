#include "spawn.h"
#include "funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#include <limits.h>

int spawn(char *argv[], int in, int out){
  char *buf = NULL;
  char **pal = malloc( sizeof( char * ) * PIPE_BUF );
  ssize_t n;
  int tam[PIPE_BUF];

  int j = 0;
  int linha_atual = 0;
  int aux;
  int coluna;

  char *comando[PIPE_BUF];

  int stdin_original = dup(0);
  dup2(in, 0);

  while((n = getline(&buf, &n, stdin)) != -1){
    linha_atual++;
    tam[j] = 0;

    pal[j] = malloc( PIPE_BUF );
    memcpy(pal[j], buf, n);
    pal[j][n-1] = '\0';

    if(!fork()){
      for(int i=2; argv[i]; i++){
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

  dup2(stdin_original, in);

  for(int i=0; i<j; i++){
    int estado;
    wait(&estado);
    if (WIFEXITED(estado)){
      tam[i] += sprintf(pal[i], "%s:%d\n", pal[i], estado);
      write(out, pal[i], tam[i]);
    }
  }

  return 0;
}
