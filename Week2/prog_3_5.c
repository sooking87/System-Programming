#include <stdio.h>

// 문자열과 포인터
int main() {
    // *p와 m[]의 차이점?
    char *p = "Hello!"; // 포인터 변수는 스택에 저장, 실제 문자열은 데이터섹션에 저장
    char m[] = "world!"; // 배열에 차례대로 w, o, r, l, d가 들어가고 마지막에 \o가 들어감.
    printf("%s %s\n", p, m);
    p = m;
    printf("%s\n", p);
    while (*p) {
        putchar(*p++); // putchar: 문자열 표준출력 함수.
    }
}