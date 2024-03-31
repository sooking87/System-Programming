#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#define START_ID 1001001

/*구조체를 이용하여 학생 정보를 파일에 저장한다. */
// fseek: 파일 위치 포인터를 임의로 설정할 수 있는 함수 -> 파일 커서를 얼만큼 이동시킬지를 나타내는 offset 변수의 데이터타입이 long 이므로 숫자 뒤에 L을 붙힘. ex.100L, 그리고 offset 단위는 바이트
// rewind: 현재 파일 위치를 파일 시작에 위치시킴
// ftell: 파일의 현재 파일 위치를 나태는 파일 위치 지정자 값 리턴
int main(int argc, char* argv[]) {
    struct student rec;
    FILE *fp;
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "wb");
    printf("%7s %6s %4s\n", "학번", "이름", "점수");
    while (scanf("%d %s %hd", &rec.id, rec.name, &rec.score) == 3) {
        fseek(fp, (rec.id - START_ID)* sizeof(rec), SEEK_SET);
        fwrite(&rec, sizeof(rec), 1, fp);
    }
    fclose(fp);
    exit(0);
}