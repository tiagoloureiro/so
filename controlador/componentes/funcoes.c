#include "funcoes.h"

#include <limits.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

int separa(char *pal, char** argumentos){
  char* pch;
  int k;

  pch = strtok (pal," ");

  for (k=0; pch != NULL; k++){
    argumentos[k] = malloc( PIPE_BUF );
    sprintf(argumentos[k], "%s", pch);
    pch = strtok (NULL, " ");
  }

  return k;
}

int* get_coluna_two(char *p, int c1, int c2, int* num){
  int coluna=1, i;

  for(i=1; p[i], coluna<c2; i++){
    if(p[i] == ':') coluna++;

    if(coluna==c1){
      num[0] = atoi(p+i);
    }
  }

  num[1] = atoi(p+i);

  return num;
}

int get_coluna(char *p, int c){
  int coluna=1, i;

  for(i=1; p[i], coluna<c; i++){
    if(p[i] == ':') coluna++;
  }

  return atoi(p+i);
}

char* get_coluna_str(char *p, int c){
  int coluna=1, i, j=0;
  char *str = malloc (sizeof (char) * PIPE_BUF);

  for(i=0; p[i], coluna<c; i++){
    if(p[i] == ':') coluna++;
  }

  for(j=0; p[i] && p[i] != ':'; j++, i++){
    str[j] = p[i];
  }

  return str;
}
