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
  int v1, v2;
  int *num = malloc(2);

  if(argc == 4){
    while((n = getline(&buf, &n, stdin)) != -1){
      memcpy(pal, buf, n);
      pal[n-1] = '\0';

      num = get_coluna_two(pal, atoi(argv[1]), atoi(argv[3]), num);
      v1 = num[0];
      v2 = num[1];

      if(strcmp(argv[2], "<") == 0){
        if(v1 < v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], "<=") == 0){
        if(v1 <= v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], ">=") == 0){
        if(v1 >= v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], ">") == 0){
        if(v1 > v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], "=") == 0){
        if(v1 == v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], "!=") == 0){
        if(v1 != v2)
          write(1, buf, n);

      }else{
        break;
      }
    }
  }

  return 0;
}
