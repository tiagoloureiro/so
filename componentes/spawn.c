#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
  char *buf = NULL;
  char pal[PIPE_BUF];
  ssize_t n;
  int coluna;
  int tam;

  int res = 0;
  int linhas[PIPE_BUF];
  int linha_atual = 0;
  int aux;

  char comando[PIPE_BUF];

  if(argc > 2){

    for(int i=1; i<argc; i++){
      printf("%s\n", argv[i]);
      /*if(argv[i][0] == '$'){
        printf("tito\n");
        coluna = atoi(argv[i]+1);
      }
      sprintf(comando, "%s:%s\n", comando, argv[i]);*/
    }

    while((n = getline(&buf, &n, stdin)) != -1){
      linha_atual++;
      //print_array(linhas, atual, maximo);

      tam = 0;

      memcpy(pal, buf, n);
      pal[n-1] = '\0';
      aux = get_coluna(pal, coluna);

      //system(comando);

    }

    printf("%s\n%d\n", comando,coluna);
  }
  return 0;
}
