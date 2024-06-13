#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid1, pid2;
    int status;
    // sleep(2);
    pid1 = fork();
    if (pid1 == 0) {
        printf("[Child 1]: Hello World! pid=%d\n", getpid());
    }
    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2]: Hello World! pid=%d\n", getpid());
    }
    // else {
    //     wait(&status);
    // }
    printf("[PARENT]: Hello World! pid=%d\n", getpid());

}