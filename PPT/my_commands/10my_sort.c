/*
 * 파일명: my_sort.c
 * 기능: 'sort' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_sort my_sort.c
 * 사용법: ./my_sort -rn numbers.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "sort ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}