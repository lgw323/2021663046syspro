/*
 * 파일명: my_cat.c
 * 기능: 'cat' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_cat my_cat.c
 * 사용법: ./my_cat file1.txt file2.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "cat ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}