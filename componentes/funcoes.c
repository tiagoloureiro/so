#include "funcoes.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

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

const char* get_coluna_str(char *p, int c){
  int coluna=1, i, j=0;
  char str[PIPE_BUF];
  char *str_return;

  for(i=1; p[i], coluna<c; i++){
    if(p[i] == ':') coluna++;
  }

  while(p[i] != '\0' || p[i] != ':'){
    str[j] == p[i];
    j++;
    i++;
  }
  str[j] == '\0';

  snprintf(str_return, j, "%s", str);

  return str_return;
}
