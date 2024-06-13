#include <stdio.h>

// 입력받은 argv를 출력하는 프로그램
int main(int argc, char *argv[]) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s \n", i, argv[i]);
    }
    
} 