#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // open, close 함수

int main() {
    FILE *fp;
    fp = open("./setvbuf", O_RDWR);
    char *buf = "GOOD AFTERNOON";
    
    printf("안녕하세요, ");
    sleep(1);
    printf("리눅스입니다.!");
    sleep(1);
    printf("\n");
    sleep(1);

    setbuf(stdout, NULL);
    printf("여러분, ");
    sleep(1);
    printf("반갑습니다.!");
    sleep(1);
    printf("\n");
    sleep(1);

    setvbuf(fp, buf, _IONBF, sizeof(buf));
    printf("여러분, ");
    sleep(1);
    printf("반갑습니다.!");
    sleep(1);
    printf("\n");
    sleep(1);

}