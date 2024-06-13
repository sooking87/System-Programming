#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
void sigHandler();
int main() {
    int child, status;

    signal(SIGALRM, sigHandler);
    alarm(6);
    if (fork() == 0) {
        printf("child1=%d\n", getpid());
        while(1) sleep(300);
    }
    if (fork() == 0) {
        printf("child2=%d\n", getpid());
        while(1) sleep(300);
    }
    else {
        child = wait(&status);
        printf("프로세스 %d 종료 \n", getpid());
    }
    return 0;
}
void sigHandler() {
    kill(0, SIGTERM);
}