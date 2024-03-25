#include <stdio.h>

int fact(int n); // 함수선언
int global = 10; // 전역 변수 선언

int main() {
    int a = 4, b;
    b = fact(a);
    printf("b=%d\n", b);
    global = global + b;
}

int fact(int n) {
    int result = 1;
    for (int i = 1; i < n; i++) {
        result = result * i;
    }
    return result;
}