#include <stdio.h>

int main() {
    int num;

    // 입력 받기
    printf("0부터 255 사이의 수를 입력하세요: ");
    scanf("%d", &num);

    // 유효성 검사
    if (num < 0 || num > 255) {
        printf("잘못된 입력입니다. 0부터 255 사이의 수를 입력하세요.\n");
        return 1;
    }

    // 2진수 출력 및 1의 개수 세기
    int one_count = 0;
    printf("2진수 (8비트): ");
    for (int i = 7; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
        if (bit == 1) {
            one_count++;
        }
    }
    printf("\n");

    // 1의 개수 출력
    printf("1의 개수: %d개\n", one_count);

    // 상위 4비트 출력
    int upper_nibble = (num >> 4) & 0x0F;
    printf("상위 4비트: ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (upper_nibble >> i) & 1);
    }
    printf("\n");

    return 0;
}