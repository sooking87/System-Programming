#include <stdio.h>
#include <stdlib.h>
#include "student.h"

// fread, fwrite: 한 번에 일정한 크기의 데이터를 파일에 읽거나 쓰기 위한 입출력 함수
// fread: fp 가 가리키는 파일에서 size 크기의 블록(연속된 바이트)을 n개 읽어서 버퍼 포인터 buf가 가리키는 곳에 저장
// fwrite: 파일 포인터 fp가 지정한 파일에 버퍼 buf에 저장되어 있는 size 크기의 블록(연속된 바이트) n개를 기록
int main(int argc, char* argv[])
{
    struct student rec;
    FILE *fp;
    if (argc != 2)
    {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
    }
    fp = fopen(argv[1], "wb");
    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
    while (scanf("%d %s %d", &rec.id, rec.name,
    &rec.score) == 3)
    {
        fwrite(&rec, sizeof(rec), 1, fp);
    }
    fclose(fp);
    exit(0);
    
}