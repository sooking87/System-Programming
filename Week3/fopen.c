#include <stdio.h>

int main() {
    FILE *fp, *fp2, *fp3;
    fp = fopen("/Users/sookyoungsohn/STUDY/System-Programming/Week3/text.txt", "r");
    fp2 = fopen("/Users/sookyoungsohn/STUDY/System-Programming/Week3/outdata.txt", "w");
    fp3 = fopen("/Users/sookyoungsohn/STUDY/System-Programming/Week3/text.txt", "a");

    if (fp == NULL) {
        printf("파일 열기 오류 \n");
    }
    // fgets(읽어올 내용을 넣을 변수, 사이즈, 파일 포인터) / 파일 읽어오기 / "r"
    char str[50];
    fgets(str, 50, fp);
    fclose(fp);
    printf("%s\n", str);
    
    // fprintf(파일 포인터, 넣을 내용) / 파일 쓰기 / "w" -> 파일이 없는 경우는 새로 만들고 작성, 파일이 있는 경우는 기존 내용 삭제하고 그 파일 위에 작성
    fprintf(fp2, "sooking87");
    fclose(fp2);

    // fputs(넣을 내용, 파일 포인터) / 파일 내용 추가 / "a"
    fputs("\nfrom the code content\n", fp3);
    fclose(fp3);

}