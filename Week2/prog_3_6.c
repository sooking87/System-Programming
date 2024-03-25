#include <stdio.h>

// 여러 개의 문자열 저장
int main() {
    // 문자형의 이차원 배열을 사용(문자열 3개, 문자열길이 10이내)
    char colors[3][10] = {"red", "blue", "white"};
    printf("문자열: 이차원 배열 저장의 경우 %s\n", colors[0]);

    // 포인터 배열이용: 배열의 각 원소가 포인터인 배열
    char *ptr1[3] = {"red", "cian", "black"};
    printf("문자열: 포인터 배열 저장의 경우 %p %s\n", ptr1, *(ptr1+1));

    // 포인터의 포인터
    char *ptr2[3] = {"red", "cian", "black"};
    // char *ptr2[3]은 메모리 3개를 가리키는 배열이다.
    char **p = ptr2+1; 
    // 현재 ptr2는 ptr2 배열의 첫 번째 주소를 가지고 있는 변수이고, +1을 함으로서 배열의 다음 "주소"를 가리키고 있다.
    // 근데 여기서 char **p라는 것은 ptr2+1이 이미 주소 이기 때문에 주소 변수의 주소를 가지고 있는 변수가 된다.
    // 변수 사용시 **p 라는 것은 p: ptr2+1(주소)가 가리키는 주소(문자열)가 가리키는 값(문자)
    // *p: ptr2+1(주소)가 가리키는 값(문자열)
    // p: 배열을 가진 주소

    // ** Week2 강의안에 자세히 나와있으니 확인해볼 것

    printf("이중 포인터 %p %s\n", p, *p); // 이중 포인터 0x16cfab298 cian
    printf("이중 포인터 %p %c\n", *p, **(p)); // 이중 포인터 0x102e57f33 c
    printf("이중 포인터 %p %s\n", ptr2, *ptr2); // 이중 포인터 0x16cfab290 red

    int *numPtr1;     // 단일 포인터 선언
    int **numPtr2;    // 이중 포인터 선언
    int num1 = 10;

    numPtr1 = &num1;    // num1의 메모리 주소 저장 

    numPtr2 = &numPtr1; // numPtr1의 메모리 주소 저장

    printf("%d\n", **numPtr2);    // 20: 포인터를 두 번 역참조하여 num1의 메모리 주소에 접근

    return 0;

}