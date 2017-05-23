#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"
#include <sys/types.h>
#include <sys/wait.h>

int join(char *argumentos[], int n, char *str, char *linha){
  int coluna;

  for(int i=1; i<n; i++){
    if(argumentos[i][0] == '$'){
      coluna = atoi(argumentos[i]+1);
      const char* aux = get_coluna_str(linha, coluna);
      if(i==1)
        strcpy(str, aux);
      else
        strcat(str, aux);
    }else{
      if(i==1)
        strcpy(str, argumentos[i]);
      else
        strcat(str, argumentos[i]);
    }

    if(i != n){
      strcat(str, " ");
    }
  }
}

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
    while((n = getline(&buf, &n, stdin)) != -1){
      linha_atual++;
      //print_array(linhas, atual, maximo);

      tam = 0;

      memcpy(pal, buf, n);
      pal[n-1] = '\0';

      join(argv, argc, comando, pal);
      printf("%s\n", comando);

    }
  }
  return 0;
}
