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
  int col2, col4;
  int *num = malloc(2);
  int flag = 0;

  if(argc == 2){
    int tam = sizeof(argv[1])/4;

    while((n = getline(&buf, &n, stdin)) != -1){
      if(flag == 1){
        write(1, pal, n + tam);
        flag = 0;
      }else{
        memcpy(pal, buf, n);
        pal[n-1] = '\0';
        sprintf(pal, "%s:%s\n", pal, argv[1]);

        num = get_coluna(pal, 2, 4, num);
        col2 = num[0];
        col4 = num[1];

        write(1, pal, n + tam + 1);

        if(col2 >= col4){
          flag = 1;
        }
      }
    }

  }

  return 0;
}
