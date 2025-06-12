/*
 * 파일명: my_wc.c
 * 기능: 'wc' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_wc my_wc.c
 * 사용법: ./my_wc -l file.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "wc ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}