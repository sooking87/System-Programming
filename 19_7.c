#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>

int main() {
    if (fork() == 0) {
        printf("Hello pid=%d\n", getpid());
    }
    if (fork() == 0) {
        printf("Good morning pid=%d\n", getpid());
    }
}