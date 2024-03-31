#include <stdio.h>
// 텍스트 파일 내용을 표준출력에 출력

// argc(argument count): 메인함수에 전달되는 정보의 갯수를 의미
// argv(argument vector): 메인함수에 전달되는 실질적인 정보, 문자열 배열
// argv[0]: 실행 파일 이름
// argv[1]: 첫 번째 명령줄 인수
int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    // cmd 창에 "./fcat" 만 입력하면 명령줄 인수가 없으므로 argc: 1, argv[0]: ./fcat이 들어간다.
    if (argc < 2) 
        fp = stdin; // 명령줄 인수가 없으면 표준입력 사용, 
    // cmd창에 ./fcat 파일이름.txt 를 입력하게 되면
    // argc: 2
    // argv[0]: 파일경로, argv[1]: 파일이름.txt 가 들어간다. 
    else
        fp = fopen(argv[1], "r"); // 읽기 전용으로 파일 열기

    // argc, argv에 뭐가 들어있는지 살펴보기
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    c = getc(fp); // 파일로부터 문자 읽기
    while (c != EOF) { // 파일 끝이 아닐 동안 반복문 실행
        putc(c, stdout); // 읽은 문자를 표준출력에 출력
        c = getc(fp); // 파일로부터 문자 읽기
    }

    fclose(fp);
    return 0;

}