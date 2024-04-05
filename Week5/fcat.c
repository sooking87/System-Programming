#include <stdio.h>
#define MAXLINE 80

// 키보드 입력한 내용을 파일에 쓰기
int main(int argc, char *argv[]){
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];
    if (argc != 2) {
        fprintf(stderr, "사용법:fcat 파일이름\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "w")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    }
    while (fgets(buffer, MAXLINE, stdin) != NULL) {
        fputs(buffer, fp);
    }
    return 0;
}