#include <stdio.h>
#include <stdlib.h>

// 환경 변수 출력
int main(int argc, char *argv[]) {
    char **ptr;
    extern char **environ;

    for (ptr = environ; *ptr != 0; ptr++) {
        printf("%s \n", *ptr);
    }
    exit(0);
}