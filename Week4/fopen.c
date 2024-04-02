#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // open, close 함수

int main(int argc, char* argv[])
{
    int fd; // 시스템 호출로 파일을 열기 위해서는 파일 디스크립터(fd) 가 필요
    // open 함수가 -1 리턴 -> 오픈 실패
   // O_RDWR: 읽기 쓰기 모드 
    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        perror(argv[1]);
        exit(1);
    }
    printf("파일 %s 열기 성공\n,", argv[1]);
    close(fd);
    exit(0);
}