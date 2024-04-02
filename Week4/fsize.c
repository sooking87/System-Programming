#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 512

// 파일 크기를 계산
int main(int argc, char* argv[])
{
    char buffer[BUFSIZE];
    int fd;
    ssize_t nread; // 읽어온 바이트 수를 저장하기 위한 변수
    long total = 0;
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        perror(argv[1]);
    
    // 파일의 끝에 도달할 때까지 반복해서 읽으면서 팡리 크기 계산
    // read() -> 파일 읽기를 성공하면 읽은 바이트수를 리턴
    while ((nread = read(fd, buffer, BUFSIZE)) > 0)
        total += nread;
    close(fd);
    printf("%s 팡리 크기: %ld 바이트 \n", argv[1], total);
    exit(0);
}