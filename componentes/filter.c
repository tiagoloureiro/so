#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int get_coluna(char *p, int c1, int c2, int* num[2]){
  char * pch = strtok (p,":");
  int i;
  int nu[2] = &num;

  for(i=2; pch, i<=c2; i++){
    pch = strtok (NULL, ":");
    if(i==c1){
      nu[0] = atoi(pch);
    }
  }

  nu[1] = atoi(pch);

  return 0;
}

int main(int argc, char *argv[]){
  char *buf = NULL;
  char pal[PIPE_BUF];
  ssize_t n;
  int v1, v2;
  int *num[2];

  while((n = getline(&buf, &n, stdin)) != -1){
    if(argc == 4){
      memcpy(pal, buf, n-1);

      get_coluna(pal, atoi(argv[1]), atoi(argv[3]), num);
      v1 = num[0];
      v2 = num[1];

      printf("%d - %d\n", v1, v2);

      if(strcmp(argv[2], "<")){
        if(v1 < v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], "<=")){
        if(v1 <= v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], ">=")){
        if(v1 >= v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], ">")){
        if(v1 > v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], "=")){
        if(v1 == v2)
          write(1, buf, n);

      }else if(strcmp(argv[2], "!=")){
        if(v1 != v2)
          write(1, buf, n);

      }else{
        break;
      }

      num[0] = 0;
      num[1] = 0;
    }
  }

  return 0;
}
