#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*학생 정보를 입력받아 데이터베이스 파일에 저장한다.*/
int main(int argc, char *argv[]) {
    int selection=0;
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", *argv[0]);
        exit(1);
    }
    while(1) {
        printf("\n****** 학생정보시스템 ******\n\n");
        printf("1. 전체 학생 보기 \n");
        printf("2. 학생 정보 검색 \n");
        printf("3. 학생 정보 수정 \n");
        printf("4. 학생 정보 등록 \n");
        printf("5. 학생 정보 삭제 \n");
        printf("6. 종료 \n");
        printf("\n 선택: : \n");
        scanf("%d", &selection);
        switch(selection) {
            case 1: 
                list(argv[1]);
                break;
            case 2:
                query(argv[1]);
                break;
            case 3:
                update(argv[1]);
                break;
            case 4:
                insert(argv[1]);
                break;
            case 5:
                delete(argv[1]);
                break;
            case 6:
                return(0);
            default:    
                break;
        }

    }
    exit(0);

}