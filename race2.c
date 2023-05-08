// a conciser version
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <linux/fs.h>

int main() {
  int fd1, fd2;
  char *fn1="";
  char *fn2="";
  fd1 = open(fn1, O_RDONLY);
  fd2 = open(fn2, O_RDONLY);
  printf("fd1: %d | fd2: %d\n", fd1, fd2);
  while(1) 
      syscall(SYS_renameat2, fd1, fn1, fd2,fn2, RENAME_EXCHANGE);
}
