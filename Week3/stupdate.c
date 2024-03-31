#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#define START_ID 1001001

// 레코드 수정 과정
// 1. 파일로부터 해당 레코드를 읽어서
// 2. 레코드를 수정한 다음에
// 3. 수정된 레코드를 다시 파일 내의 원래 위치에 쓴다.
int main(int argc, char *argv[])
{
    struct student rec;
    int id;
    char c;
    FILE *fp;

    if (argc != 2)
    {
        fprintf(stderr, "사용법 %s 파일이름\n", argv[0]);
        exit(1);
    }
    if ((fp = fopen(argv[1], "rb+")) == NULL)
    {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    do 
    {
        printf("수정할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1)
        {
            fseek(fp, (id - START_ID)*sizeof(rec), SEEK_SET);
            if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0))
            {
                printf("학번: %8d 이름: %4s 점수: %4d\n", rec.id, rec.name, rec.score);
                printf("새로운 점수 입력: ");
                scanf("%d", &rec.score);
                fseek(fp, -sizeof(rec), SEEK_CUR);
                fwrite(&rec, sizeof(rec), 1, fp);
            } else printf("레코드 %d 없음\n", id);
        } else printf("입력오류\n");
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c",&c);
    } while (c == 'Y');
    fclose(fp);
    exit(0);
}