#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"

void print_array(int *array, int inicio, int fim){
  for(int i=inicio; i<=fim; i++){
    printf("(i%d, %d) ", i, array[i]);
  }
  printf("|\n");
}


int avg(int *array, int n, int fim){
  int res = 0;
  int i, j=0;

  int inicio = fim-n;

  if(inicio > 0){
    for(i=inicio-1; i<fim && j<n ; i++, j++){
      res += array[i];
    }
    res = res/j;
  }else if(inicio == 0){
    res = array[0];
  }else if(inicio < 0){
    res = 0;
  }

  return res;
}

int maximo(int *array, int n, int fim){
  int max = 0;
  int i, j=0;

  int inicio = fim-n;

  if(inicio > 0){
    for(i=inicio-1; i<fim && j<n ; i++, j++){
      if(array[i] > max){
        max = array[i];
      }
    }
  }else if(inicio == 0){
    max = array[0];
  }else if(inicio < 0){
    max = 0;
  }

  return max;
}

int minimo(int *array, int n, int fim){
  int min = 0;
  int i, j=0;
  int flag = 0;

  int inicio = fim-n;

  if(inicio > 0){
    for(i=inicio-1; i<fim && j<n ; i++, j++){
      if(flag == 0){
        min = array[i];
        flag++;
      }
      if(array[i] < min){
        min = array[i];
      }
    }
  }else if(inicio == 0){
    min = array[0];
  }else if(inicio < 0){
    min = 0;
  }

  return min;
}

int soma(int *array, int n, int fim){
  int res = 0;
  int i, j=0;

  int inicio = fim-n;

  if(inicio > 0){
    for(i=inicio-1; i<fim && j<n ; i++, j++){
      res += array[i];
    }
  }else if(inicio == 0){
    res = array[0];
  }else if(inicio < 0){
    res = 0;
  }

  return res;
}

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

      linhas[linha_atual-1] = aux;

      if(strcmp(argv[2], "avg") == 0){
        res = avg(linhas, n_valores, linha_atual);
      }else if(strcmp(argv[2], "min") == 0){
        res = minimo(linhas, n_valores, linha_atual);
      }else if(strcmp(argv[2], "max") == 0){
        res = maximo(linhas, n_valores, linha_atual);
      }else if(strcmp(argv[2], "sum") == 0){
        res = soma(linhas, n_valores, linha_atual);
      }else{
        break;
      }

      tam += sprintf(pal, "%s:%d\n", pal, res);
      write(1, pal, n + tam + 1);
    }

    //print_array(linhas, linha_atual-1);
  }

  return 0;
}
