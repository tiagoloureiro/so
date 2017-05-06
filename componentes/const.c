#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]){
  char *buf = NULL;
  ssize_t n;

  while((n = getline(&buf, &n, stdin)) != -1){
    write(1, buf, n-1);

    if(argc == 2){
      printf(":%s", argv[1]);
    }
    printf("\n");
  }

  return 0;
}
