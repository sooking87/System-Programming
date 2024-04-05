//rdInput.c
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 80
// 키보드 입력을 안해도 자동으로 파일의 내용이 터미널에 출력될 수 있도록

int main(int argc, char * argv[]){
    int fd;
    char buf[SIZE]={'\0'};
    if((fd = open(argv[1], O_RDONLY|O_CREAT, 0600))== -1)
        perror(argv[1]);
    printf("입력재지정 구현 | 파일 %s 내용을 화면에 출력\n", argv[1]);
    dup2(fd, 0);
    while (gets(buf)!= NULL)
        puts(buf);
    exit(0);
}