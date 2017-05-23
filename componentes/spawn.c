#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"
#include <sys/types.h>
#include <sys/wait.h>

int join(char * argumentos[], int n, char *str[], char *linha){
  int coluna;

  for(int i=2; i<n; i++){
    printf("inicio %d\n", i-2);
    if(argumentos[i][0] == '$'){
      printf("\tinicio 1");
      coluna = atoi(argumentos[i]+1);
      const char* aux = get_coluna_str(linha, coluna);
      if(i==2)
        strcpy(str[i-2], aux);
      else
        strcat(str[i-2], aux);
      printf("\tfim 1");
    }else{
      printf("\tinicio 2");
      if(i==2)
        strcpy(str[i-2], argumentos[i]);
      else
        strcat(str[i-2], argumentos[i]);
      printf("\tfim 2");
    }

    if(i != n){
      printf("\tinicio 3");
      strcat(str[i-2], " ");
      printf("\tfim 3");
    }

    printf("fim %d\n", i-2);
  }
}

int main(int argc, char * argv[]){

  char *buf = NULL;
  char pal[PIPE_BUF];
  ssize_t n;
  int coluna;
  int tam;

  int res = 0;
  int linhas[PIPE_BUF];
  int linha_atual = 0;
  int aux;

  char *comando[PIPE_BUF];

  if(argc > 2){
    while((n = getline(&buf, &n, stdin)) != -1){
      int estado = -1;
      linha_atual++;

      tam = 0;

      memcpy(pal, buf, n);
      pal[n-1] = '\0';

      join(argv, argc, comando, pal);
      //printf("%s %s\n", argv[1], comando);

      if(!fork()){
        execvp(argv[1], comando);
        _exit(0);
      }

      wait(&estado);
      tam += sprintf(pal, "%s:%d\n", pal, estado);
      write(1, pal, tam);
    }
  }
  return 0;
}
