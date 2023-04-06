#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifndef RENAME_EXCHANGE
#define RENAME_EXCHANGE (1 << 1) 
#endif

int main(int argc, char *argv[]) {
    // the function has three parameters: name1, name2, and linkdest.
    if (argc != 4) {
        fprintf(stderr, "Usage: %s name1 name2 linkdest\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *name1 = argv[1], *name2 = argv[2], *linkdest = argv[3];

    int dirfd = open(".", O_DIRECTORY|O_CLOEXEC);
    if (dirfd < 0)
        exit(EXIT_FAILURE);
    // 1. Create a directory named name1.
    if (mkdir(name1, 0755) < 0)
        perror("mkdir failed");
    // 2. Create a symlink named name2 that points to linkdest.
    if (symlink(linkdest, name2) < 0)
        perror("symlink failed");
    // 3. In the while loop, swap the values of name1 an name2. 
    //    As a result, name1 and name2 will alternately point to linkdest.
    while (1)
        syscall(SYS_renameat2, dirfd, name1, dirfd, name2, RENAME_EXCHANGE);
}
