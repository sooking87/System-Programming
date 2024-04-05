#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 80

// 파일의 내용이 있으면 추가적으로 쓸 수 있도록 해주는 옵션
int main(int argc, char * argv[]){
    int fd;
    char buf[MAX]={'\0'};
    if ((fd = open(argv[1], O_WRONLY|O_APPEND|O_CREAT, 0600)) == -1)
        perror(argv[1]);
    printf("cat >> %s 구현 \n", argv[1]);
    dup2(fd, 1);
    while (gets(buf)!= NULL)
        puts(buf);
    exit(0);
}