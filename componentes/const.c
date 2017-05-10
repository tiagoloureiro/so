#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]){
  char *buf_r;
  char buf_w[PIPE_BUF];
  char aux[PIPE_BUF];
  ssize_t n;
  int col2;
  int col4;
  int total = 0;

  while((n = getline(&buf_r, &n, stdin)) != -1){
    snprintf(aux, n, "%s:10", buf_r);
    total += n + 1 + sizeof(argv[1]);
    sprintf(buf_w, "%s:%s\n",buf_w,aux, argv[1]);
  }

  printf("%s\n", buf_w);

  return 0;
}
