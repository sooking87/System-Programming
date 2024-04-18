#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "student.h"

/* 파일에 저장된 모든 학생 정보를 읽어서 출력한다. */
int listdb(char* filename) {
    struct student rec;
    int fd;
    if ((fd = open(filename, O_RDONLY)) == -1) {
        fprintf(stderr, "파일 열기 오류\n");
        return 1;
    }
    printf("-----------------------------------\n");
    printf("%10s %6s %6s\n", "학번", "이름", "점수");
    printf("-----------------------------------\n");

    while (read(fd, &rec, sizeof(rec)) > 0) {
        if (rec.id != 0)
            printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    }
    printf("-----------------------------------\n");
    close(fd);
    return 0; 
}

/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int querydb(char * filename){
    struct student rec;
    char c;
    int id;
    int fd;
    if ((fd = open(filename, O_RDONLY)) == -1) {
        fprintf(stderr, "파일 열기 오류\n");
        return 1;
    }
    do {
        printf("검색할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            lseek(fd, (id - START_ID) * sizeof(rec), SEEK_SET);
            if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
                printf("학번: %-8d 이름: %-4s 점수: %-4d\n", rec.id, rec.name, rec.score);
            } else {
                printf("레코드 %d 없음\n", id);
            }
            printf("계속하겠습니까?(Y/N)");
            scanf(" %c", &c);
        }
    } while (c == 'Y' || c == 'y');
    close(fd);
    return 0;
}

/* 학번을 입력받아 해당 학생 레코드를 수정한다. */
int updatedb(char *filename){
    struct student rec;
    int id;
    char c;
    int fd;

    if ((fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "파일 열기 오류\n");
        return 1;
    }

    do {
        printf("수정할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            lseek(fd, (id - START_ID) * sizeof(rec), SEEK_SET);
            if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
                printf("학번: %8d 이름: %4s 점수: %4d\n", rec.id, rec.name, rec.score);
                printf("새로운 점수 입력: ");
                scanf("%d", &rec.score);
                lseek(fd, -sizeof(rec), SEEK_CUR);
                write(fd, &rec, sizeof(rec));
            } else {
                printf("레코드 %d 없음\n", id);
            }
        } else {
            printf("입력오류\n");
            break;
        }
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');
    close(fd);
    return 0;
}

/* 학생 정보를 입력받아 데이터베이스 파일에 저장한다. */
int insertdb(char * filename){
    struct student rec;
    int fd;
    char c;
    if ((fd = open(filename, O_RDWR | O_CREAT, 0600)) == -1) {
        perror("파일 열기 오류");
        return 1;
    }
    do {
        printf("새로운 학생 정보 등록을 시작합니다.\n");
        printf("학번 : ");
        scanf("%d", &rec.id);
        printf("이름 : ");
        scanf("%s", rec.name);
        printf("성적 : ");
        scanf("%hd", &rec.score);
        lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
        write(fd, &rec, sizeof(rec));
        printf("새로운 학생 정보가 등록되었습니다.\n계속하겠습니까?(Y/N)");
        scanf(" %c",&c);
    } while (c == 'Y' || c == 'y');
    close(fd);
    return 0;
}

/* 학생 학번을 입력받아 해당 학생 정보를 데이터베이스 파일에서 삭제한다. */
int deletedb(char *filename) {
    int id;
    char c;
    int fd;
    struct student rec;

    if ((fd = open(filename, O_RDWR)) == -1) {
        perror(filename);
        return 1;
    }

    do {
        printf("학생 정보 삭제합니다.\n");
        printf("삭제할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            lseek(fd, (id - START_ID) * sizeof(rec), SEEK_SET);
            if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
                rec.id = 0; // 학생 정보 삭제를 위해 학번을 0으로 설정
                lseek(fd, -sizeof(rec), SEEK_CUR);
                write(fd, &rec, sizeof(rec));
                printf("학번: %8d 이름: %4s 점수: %4d 정보가 삭제되었습니다.\n", id, rec.name, rec.score);
            } else {
                printf("레코드 %d 없음\n", id);
            }
        } else {
            printf("입력 오류\n");
            break;
        }
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}
