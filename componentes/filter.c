#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int* get_coluna(char *p, int c1, int c2, int* num){
  char* pch = strtok (p,":");
  int i;

  for(i=2; pch, i<=c2; i++){
    pch = strtok (NULL, ":");
    if(i==c1){
      num[0] = atoi(pch);
    }
  }

  num[1] = atoi(pch);

  return num;
}

int main(int argc, char *argv[]){
  char *buf = NULL;
  char pal[PIPE_BUF];
  ssize_t n;
  int v1, v2;
  int *num = malloc(2);

  while((n = getline(&buf, &n, stdin)) != -1){
    if(argc == 4){
      memcpy(pal, buf, n-1);

      num = get_coluna(pal, atoi(argv[1]), atoi(argv[3]), num);
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
    }
  }

  return 0;
}
