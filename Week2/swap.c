#include <stdio.h>

void swap(int *px, int *py) {
    int t;
    t = *py;
    *py = *px;
    *px = t;
}

int main() {
    int a = 10;
    int b = 3;
    printf("a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("a=%d, b=%d\n", a, b);

    int temp_a = 10;
    int temp_b = 20;
    int temp_c = 30;
    int temp_d = 40;
    int *ptr_a = &temp_a;
    // int ptr_b = &temp_b; -> 얘도 * 없다고 경고뜸
    // int ptr_c = *temp_c; -> error: *temp_c를 넣엊는 변수는 포인터 변수여야된다고 함.
    printf("temp_a: %p %d\n", ptr_a, *ptr_a);
    printf("temp_a: %p %d\n", &temp_a, temp_a);
    // int *px로 선언이 되면 &를 사용해서 주소를 넣어주는 변수로 사용
    // 주소 변수 px의 안에 있는 값을 출력하고 싶으면 *px로 안에 있는 값 출력

}

