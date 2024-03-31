#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 80

// 텍스트 파일에 줄 번호 붙여 프린트한다.
int main(int argc, char* argv[]) {
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "사용법: line 파일이름 \n");
        exit(1);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    // fprintf(fp, char *format ..) : fp 파일에 format 형태로 입력 / 파일 기준에서 "파일에" 프린트
    // fscanf(fp, char *format .. ) : fp 파일에서 format 형태로 입력 / 파일 기준에서 "파일이" 입력
    // ** 표준입출력 함수와 차이점은 표준입출력의 경우 입출력 주체가 "사람" 이었다면 파일입출력의 경우 입출력 주체가 "파일"이다.

    while (fgets(buffer, MAXLINE, fp) != NULL) {
        line++;
        printf("%3d %s\n", line, buffer);
    }
    exit(0);

}