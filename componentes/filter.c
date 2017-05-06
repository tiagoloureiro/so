#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int get_coluna(char *b, ssize_t l, int num){
  
  return 4;
}

int main(int argc, char *argv[]){
  char *buf = NULL;
  ssize_t n;
  int v1, v2;

  while((n = getline(&buf, &n, stdin)) != -1){
    if(argc == 4){
      v1 = get_coluna(&buf, &n, atoi(argv[1]));
      v2 = get_coluna(&buf, &n, atoi(argv[3]));

      if(strcmp(argv[2], "<")){
        if(v1 < v2)
          write(1, buf, n-1);

      }else if(strcmp(argv[3], "<=")){
        if(v1 <= v2)
          write(1, buf, n-1);

      }else if(strcmp(argv[3], ">=")){
        if(v1 >= v2)
          write(1, buf, n-1);

      }else if(strcmp(argv[3], ">")){
        if(v1 > v2)
          write(1, buf, n-1);

      }else if(strcmp(argv[3], "=")){
        if(v1 == v2)
          write(1, buf, n-1);

      }else if(strcmp(argv[3], "!=")){
        if(v1 != v2)
          write(1, buf, n-1);

      }
    }
  }

  return 0;
}
