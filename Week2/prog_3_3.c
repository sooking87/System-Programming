#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;
    printf("%p %d\n", &a, a);
    printf("%p %d\n\n", p, *p);

    *p = *p + 10; // *p(주소 참조)): p에 있는 메모리 공간의 값 + 10
    printf("%p %d\n", &a, a);
    printf("%p %d\n\n", p, *p);

    a = 30;
    printf("%p %d\n", &a, a);
    printf("%p %d\n\n", p, *p);
    // 주소는 동일하지만, 주소 안에 있는 값이 변한 것을 확인할 수 있음.
}