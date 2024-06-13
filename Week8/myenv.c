#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *ptr;
    ptr = getenv("HOME");
    printf("HOME = %s \n", ptr);

    ptr = getenv("SHELL");
    printf("SHELL = %s \n", ptr);
}