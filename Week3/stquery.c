#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#define START_ID 1001001

int main(int argc, char *argv[])
{
    struct student rec;
    char c;
    int id;
    FILE *fp;
    if (argc != 2) {
        fprintf(stderr, "����: %s �����̸�\n", argv[0]);
        exit(1);
    }
    if ((fp = fopen(argv[1], "rb")) == NULL) 
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(2);
    }
    do {
        printf("�˻��� �л��� �й� �Է�: ");
        if (scanf("%d", &id) == 1) {
            fseek(fp, (id - START_ID) *sizeof(rec), SEEK_SET);
            if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
                printf("�й�: %8d �̸�: %4s\n", rec.id, rec.name, rec.score);
            }
            else printf("���ڵ� %d ����\n", id);

            printf("����ϰڽ��ϱ�?(Y/N)");
            scanf(" %c", &c);
        } 
    } while (c == 'Y');
    fclose(fp);
    exit(0);
    
}