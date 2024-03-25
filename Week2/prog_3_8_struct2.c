#include <stdio.h>
#define LEN 1

// 구조체와 포인터
struct student {
    char name[10];
    int age;
} man[LEN], *p; // 배열 변수, 포인터 변수 선언

int main() {
    int i;
    for (i = 0; i < LEN; i++) {
        printf("이름: ");
        scanf("%s", man[i].name); // name[10]이라는게 주소를 의미하므로 &를 사용하지 않음.
        printf("나이: ");
        scanf("%d", &man[i].age); // 얘는 왜 &가들어가는 거지? -> 원래 형태: scanf("변환 문자", &변수명);
    }
    for (i = 0; i < LEN; i++) {
        printf("\n이름=%10s 나이=%3d", man[i].name, man[i].age);
    }

    // 포인터 변수의 경우 구조체에 아래 두 방법으로 변수를 넣어준다.
    for (i = 0, p=man; i < LEN; i++, p++) {
        printf("\n이름=%10s 나이=%3d", (*p).name, (*p).age);
    }
    for (i = 0, p=man; i < LEN; i++, p++) {
        printf("\n이름=%10s 나이=%3d", p->name, p->age);
    }
}