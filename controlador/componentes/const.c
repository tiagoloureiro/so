#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "funcoes.h"
#include "const.h"

int const( char* argv[], int in, int out){
  char *buf = NULL;
  char pal[PIPE_BUF];
  ssize_t n;
  int col2, col4;
  int *num = malloc(2);
  int flag = 0;

  int tam = sizeof(argv[1])/4;

  int stdin_original = dup(0);
  dup2(in, 0);

  while((n = getline(&buf, &n, stdin)) != -1){
    if(flag == 1){
      write(1, pal, n + tam);
      flag = 0;
    }else{
      memcpy(pal, buf, n);
      pal[n-1] = '\0';
      sprintf(pal, "%s:%s\n", pal, argv[1]);

      get_coluna_two(pal, 2, 4, num);
      col2 = num[0];
      col4 = num[1];

      write(out, pal, n + tam + 1);

      if(col2 >= col4){
        flag = 1;
      }
    }
  }

  dup2(stdin_original, in);

  return 0;
}
