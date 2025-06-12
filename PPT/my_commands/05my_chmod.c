/*
 * 파일명: my_chmod.c
 * 기능: 'chmod' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_chmod my_chmod.c
 * 사용법: ./my_chmod 755 a.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "chmod ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}