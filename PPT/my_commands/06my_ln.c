/*
 * 파일명: my_ln.c
 * 기능: 'ln' 명령어 래퍼(Wrapper)
 * 컴파일: gcc -o my_ln my_ln.c
 * 사용법: ./my_ln -s /path/to/original link_name
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[1024] = "ln ";
    for (int i = 1; i < argc; i++) {
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }
    printf("--- 실행: %s ---\n", command);
    system(command);
    return 0;
}