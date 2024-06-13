#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>

int main() {
    // if (fork() == 0) {
    //     printf("Hello pid=%d\n", getpid(), getppid());
    // }
    // if (fork() == 0) {
    //     printf("Good morning pid=%d\n", getpid(), getppid());
    // }
    int pid1, pid2;
    // printf("parent %d\n", getppid());
    pid1 = fork();
    printf("pid1=%d\n", pid1);
    // printf("Hello pid=%d\n", getpid());
    pid2 = fork();
    // printf("Good morning pid=%d\n", getpid());
    printf("pid2=%d\n", pid2);
}