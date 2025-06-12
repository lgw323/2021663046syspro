/*
 * 파일명: my_find.c
 * 기능: 'find' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_find my_find.c
 * 사용법: ./my_find . -name "*.c"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "find ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}