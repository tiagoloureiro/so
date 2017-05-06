#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

ssize_t readln(int fildes, void *buf, size_t nbyte){
  ssize_t res = 0;
  int n;
  char *b = buf;

  while ((n = read(fildes, b, 1)) > 0){
    if(res >= nbyte) break;
    if(n < 0) break;
    if(*b == '\n') return res;
    res++;
    b++;
  }

  return 0;
}

int main(int argc, char *argv[]){
  char buf[PIPE_BUF];
  ssize_t n;
  ssize_t i = 0;

  while((n = readln(0, buf, sizeof(buf))) > 0){
    write(1, buf, n);

    if(argc == 2){
      printf(":%s\n", argv[1]);
    }

  }

  return 0;
}
