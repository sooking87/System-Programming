#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 80
//키보드 입력을 파일로 출력
int main(int argc, char * argv[]){
    int fd;
    char buf[MAX] = {'\0'};
    if ((fd = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0600)) == -1)
        perror(argv[1]);
    printf("출력 재지정 구현 | 키보드로부터의 입력을 파일 %s 에 저장\n", argv[1]);
    dup2(fd, 1); // 표준 출력이 되는 것은 열린 파일에 저장하면 안되니까 여기에 dup이 들어옴
    while (gets(buf)!= NULL)
        puts(buf);
    exit(0);
}