#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>

int main() {
    int pid1, pid2;
    pid1 = fork();
    pid2 = fork();
 
    printf("좋은하루 ! pid=%d\n", getpid());

}