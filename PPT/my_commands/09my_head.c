/*
 * 파일명: my_head.c
 * 기능: 'head' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_head my_head.c
 * 사용법: ./my_head -n 20 file.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "head ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}