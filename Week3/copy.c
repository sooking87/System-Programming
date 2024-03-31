#include <stdio.h>

int main(int argc, char *argv[]) {
    char c;
    FILE *fp1, *fp2;
    // argc, argv에 뭐가 들어있는지 살펴보기
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    if (argc != 3) {
        fprintf(stderr, "사용법: %s 파일1 파일2\n", argv[0]);
        return 1;
    }
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "파일 %s 열기 오류\n", argv[1]);
        return 2;
    }
    // fp1(첫 번째 명령인자) 내용을 fp2(두 번째 명령인자)로 복사
    fp2 = fopen(argv[2], "w");
    while ((c == fgetc(fp1)) != EOF) {
        fputc(c, fp2);
        printf("%c 입력", c);
    }
    // 왜지 왜 무한루프가 돌지?
    
    fclose(fp1);
    fclose(fp2);
    return 0;
}