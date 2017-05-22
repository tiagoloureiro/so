#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"

int main(int argc, char *argv[]){
  char *buf = NULL;
  char pal[PIPE_BUF];
  ssize_t n;
  int coluna, n_valores;
  char *opcao;
  int tam;

  int res = 0;
  int linhas[PIPE_BUF];
  int linha_atual = 0;
  int aux;

  if(argc == 4){
    coluna = atoi(argv[1]);
    n_valores = atoi(argv[3]);
    opcao = argv[2];

    while((n = getline(&buf, &n, stdin)) != -1){
      linha_atual++;
      //print_array(linhas, atual, maximo);

      tam = 0;

      memcpy(pal, buf, n);
      pal[n-1] = '\0';
      aux = get_coluna(pal, coluna);
