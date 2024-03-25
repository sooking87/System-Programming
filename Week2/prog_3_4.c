#include <stdio.h>

// 배열과 포인터
int main() {
    int *p, a[4] = {10, 20, 30, 40};
    printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
    p = a; // 주소의 경우는 모두 주소로 전달이 되므로 int *p로 전달을 하는 것이다.
    printf("%d %d %d %d\n", *p, *(p+1), p[1], *(p+2), p[2]);
}