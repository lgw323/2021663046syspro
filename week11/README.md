# 📝 11주차 학습 정리

## 📅 날짜
- 2025-05-16

## 📌 주제
- Inode와 링크(Link) 동작 원리 복습
- 명령어 옵션 파싱: `getopt()`, `getopt_long()`
- 셸의 명령어 실행 원리: `fork()`와 `exec()`
- 하드 링크, 심볼릭 링크, 프로세스 생성 실습

---

## 📖 이론 정리

### 🔹 Inode와 링크 복습
- **Inode(아이노드)**: 파일이나 디렉토리에 대한 모든 메타데이터(파일 크기, 소유자, 권한, 데이터 블록 위치 등)를 저장하는 데이터 구조입니다. 파일 이름은 단지 특정 Inode를 가리키는 포인터 역할을 합니다.
- **하드 링크(Hard Link)**: 하나의 Inode에 여러 개의 파일 이름을 연결하는 것입니다. 모든 하드 링크는 동일한 Inode를 가리키므로, 사실상 같은 파일에 대한 다른 이름입니다. Inode의 **링크 카운트(Link Count)**는 해당 Inode를 가리키는 파일 이름의 개수를 나타냅니다.
- **심볼릭 링크(Symbolic Link)**: 원본 파일의 경로를 텍스트로 저장하고 있는 특수한 파일입니다. 원본 파일을 가리키는 '바로 가기'와 유사하며, 고유한 Inode를 가집니다.

### 🔹 명령어 옵션 파싱: `getopt()` 와 `getopt_long()`
C 프로그램에서 `ls -al` 처럼 명령어 뒤에 붙는 옵션(argument)을 체계적으로 처리하기 위해 사용되는 표준 라이브러리 함수입니다.

- **`getopt()`**: `-a`, `-l`과 같이 한 글자로 된 짧은 옵션을 파싱하는 데 사용됩니다. `main` 함수의 `argv` 배열을 순회하며 정의된 옵션을 찾아 처리하고, `optarg` 전역 변수를 통해 옵션에 딸린 인자(예: `-f filename`의 `filename`)를 가져올 수 있습니다.
- **`getopt_long()`**: `getopt()`의 확장 버전으로, `--all`, `--list`처럼 긴 이름의 옵션도 함께 처리할 수 있습니다. `struct option` 구조체 배열을 사용하여 긴 옵션의 이름, 인자 필요 여부 등을 정의합니다.

### 🔹 셸의 명령어 실행 원리 (chap8.pdf)
셸(Shell)이 사용자의 명령어를 실행하는 과정은 새로운 프로세스를 생성하는 대표적인 예시이며, `fork()`와 `exec()` 시스템 호출이 핵심적인 역할을 합니다.

- **`fork()` 시스템 호출**: 현재 실행 중인 프로세스(부모 프로세스, 예: 셸)를 거의 완벽하게 복제하여 새로운 자식 프로세스를 생성합니다. 자식 프로세스는 부모의 코드, 데이터, 열린 파일 디스크립터 등을 모두 상속받습니다.
- **`exec()` 계열 함수**: `fork()`로 생성된 자식 프로세스가 자신의 메모리 공간을 완전히 새로운 프로그램의 이미지로 덮어쓰게 만듭니다. 즉, 자식 프로세스는 더 이상 셸의 복사본이 아닌, 실행하고자 하는 새로운 프로그램(예: `ls`)이 됩니다.
- **`wait()` 시스템 호출**: 부모 프로세스는 `wait()`를 호출하여 자식 프로세스가 종료될 때까지 기다립니다. 이를 통해 명령어 실행이 끝난 후 다음 프롬프트를 띄우는 동기적인 작업 흐름이 가능해집니다.

---

## 🛠️ 실습 내용

### 1. 하드 링크와 심볼릭 링크 동작 확인
`ls -li` 명령어를 사용하여 Inode 번호와 링크 카운트의 변화를 직접 관찰하며 두 링크의 차이점을 확인합니다.

- **하드 링크 실습**: 여러 개의 파일 이름이 **하나의 Inode(데이터)**를 공유하며 링크 카운트가 변하는 것을 확인합니다.
  ```bash
  # a.txt 생성 후 하드 링크 b, c, d 생성
  echo "Original Data" > a.txt
  ln a.txt b.txt && ln a.txt c.txt && ln a.txt d.txt
  
  # 네 파일 모두 Inode 번호가 같고, 링크 카운트가 4로 표시됨
  ls -li a.txt b.txt c.txt d.txt
  
  # 링크 중 하나인 c.txt 삭제
  rm c.txt
  
  # 나머지 파일은 영향이 없으며, 링크 카운트만 3으로 감소
  ls -li a.txt b.txt d.txt
  ```

- **심볼릭 링크 실습**: 원본을 가리키는 별도의 파일이 생성되는 것을 확인합니다.
  ```bash
  # a.txt를 가리키는 심볼릭 링크 e.txt 생성
  ln -s a.txt e.txt
  
  # e.txt는 별도의 Inode를 가지며, 파일 타입이 'l'로 표시됨 (e.txt -> a.txt)
  ls -li a.txt e.txt
  ```

### 2. `getopt()`를 이용한 옵션 처리 예제
명령행 인자로 `-n`과 `-f <파일명>` 옵션을 받는 C 프로그램 예제입니다.

```c
#include <stdio.h>
#include <unistd.h> // getopt()를 위해 필요

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg; // optarg는 f 옵션의 인자를 가리킴
                break;
            case '?': // 인식할 수 없는 옵션
            default:
                fprintf(stderr, "사용법: %s [-f 파일명]\n", argv[0]);
                return 1;
        }
    }

    if (filename != NULL) {
        printf("전달된 파일명: %s\n", filename);
    } else {
        printf("파일명을 입력해주세요. (예: -f a.txt)\n");
    }

    return 0;
}
```

### 3. `fork()`와 `exec()`를 이용한 명령어 실행
`fork()`로 자식 프로세스를 만들고, 자식 프로세스가 `exec()`를 이용해 `ls -l` 명령어를 실행하는 프로그램입니다. 부모 프로세스는 자식이 끝날 때까지 `wait()`로 기다립니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // 자식 프로세스 생성
    pid = fork();

    if (pid < 0) { // fork 실패
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) { // 자식 프로세스
        printf("자식 프로세스: ls -l 실행\n");
        // execlp는 PATH 환경변수를 검색하여 'ls'를 찾아 실행
        execlp("/bin/ls", "ls", "-l", NULL);
    } else { // 부모 프로세스
        // 자식 프로세스가 종료될 때까지 대기
        wait(NULL);
        printf("부모 프로세스: 자식 프로세스 종료됨\n");
    }

    return 0;
}
```

### 🔹 학습 조언 (교수님 코멘트)
- 이론 학습 외에도, 개인적으로 흥미 있는 주제로 코딩을 해보거나, 간단한 앱을 만들어보고 외부 API를 사용하는 등 실제 프로젝트 경험을 쌓는 것이 실력 향상에 큰 도움이 됩니다.