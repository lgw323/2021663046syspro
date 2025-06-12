# 📝 9주차 학습 정리

## 📅 날짜
- 2025-05-02

## 📌 주제
- 커널(Kernel)과 시스템 호출(System Call)
- 파일 디스크립터(File Descriptor)의 이해
- 로우 레벨 파일 입출력 함수 (`open`, `read`, `write`, `close`)

---

## 📖 이론 정리

### 🔹 커널과 시스템 호출
- **커널(Kernel)**: 운영체제의 핵심부로, 하드웨어 자원(CPU, 메모리 등)을 관리하고 프로세스에 서비스를 제공합니다.
- **시스템 호출(System Call)**: 사용자 프로그램이 파일 생성, 네트워크 통신 등 커널의 보호된 영역에 있는 기능을 사용하기 위해 운영체제에 서비스를 요청하는 공식적인 방법(인터페이스)입니다. 이번 주에 배운 파일 입출력 함수들이 대표적인 시스템 호출입니다.

### 🔹 파일 디스크립터 (File Descriptor, fd)
- **파일 디스크립터**란, 운영체제가 특정 프로세스에서 열려 있는 파일들을 식별하기 위해 부여하는 **음이 아닌 정수(non-negative integer)**입니다.
- 프로세스가 파일을 열 때(`open` 시스템 호출), 커널은 해당 프로세스의 '파일 디스크립터 테이블'에 파일을 등록하고, 이 테이블의 인덱스 번호, 즉 파일 디스크립터를 반환합니다.
- 프로세스는 이 `fd` 값을 이용해 파일을 읽거나 쓰는 등의 작업을 수행합니다.
- 기본적으로 모든 프로세스는 셸에 의해 3개의 파일 디스크립터를 자동으로 할당받고 시작합니다.
  - `0`: 표준 입력 (Standard Input, stdin)
  - `1`: 표준 출력 (Standard Output, stdout)
  - `2`: 표준 에러 (Standard Error, stderr)
- 새로운 파일을 열면, 현재 사용 가능한 가장 낮은 번호의 정수가 `fd`로 할당됩니다. (보통 3번부터 시작)

### 🔹 로우 레벨 파일 입출력 함수
C 표준 라이브러리 함수(`fopen`, `printf` 등)와 달리, 아래 함수들은 유닉스/리눅스 시스템에서 직접 제공하는 저수준 시스템 호출입니다. 버퍼링을 거치지 않아 더 세밀한 제어가 가능합니다.

- **`open()` / `creat()`**: 파일을 열거나 생성합니다. 성공 시 파일 디스크립터를, 실패 시 -1을 반환합니다.
  - `int fd = open("file.txt", O_RDWR);` : `file.txt`를 읽고 쓰기 모드로 엽니다.
  - `O_RDONLY` (읽기 전용), `O_WRONLY` (쓰기 전용), `O_RDWR` (읽기/쓰기), `O_CREAT` (없으면 생성) 등의 옵션이 있습니다.
- **`read()`**: 열린 파일로부터 데이터를 읽습니다.
  - `ssize_t bytes_read = read(fd, buffer, count);` : `fd`로부터 `count` 바이트만큼 데이터를 읽어 `buffer`에 저장하고, 실제 읽은 바이트 수를 반환합니다.
- **`write()`**: 열린 파일에 데이터를 씁니다.
  - `ssize_t bytes_written = write(fd, buffer, count);` : `buffer`의 데이터 `count` 바이트를 `fd`에 쓰고, 실제 쓰인 바이트 수를 반환합니다.
- **`close()`**: 열려 있는 파일 디스크립터를 닫습니다.
  - `close(fd);` : `fd`와 연결된 파일을 닫고, 해당 디스크립터를 다시 사용 가능한 상태로 만듭니다.
- **`lseek()`**: 파일의 읽기/쓰기 위치(offset)를 변경합니다. 파일 크기를 알아내는 등 다양한 용도로 사용됩니다.

---

## 🛠️ 실습 내용

### 1. 프로그램 실행 인자(Argument) 이해하기
- 파일 입출력 프로그램을 만들려면, 처리할 파일 이름을 프로그램 실행 시 인자로 전달받아야 합니다. `main` 함수의 `argc`와 `argv`는 이 역할을 합니다.
- `argument.c`를 통해 `argc`(인자의 개수)와 `argv`(인자 문자열 배열)의 동작을 확인합니다.

  ```c
  #include <stdio.h>
  
  int main(int argc, char *argv[]) {
      printf("총 인자 개수: %d\n", argc);
      
      for (int i = 0; i < argc; i++) {
          printf("argv[%d]: %s\n", i, argv[i]);
      }
  
      return 0;
  }
  ```
  - **컴파일 및 실행**
    ```bash
    gcc -o argument argument.c
    ./argument file1.txt file2.txt
    ```
    - **실행 결과**
    ```
    총 인자 개수: 3
    argv[0]: ./argument
    argv[1]: file1.txt
    argv[2]: file2.txt
    ```

### 2. 파일 디스크립터 할당 원리 확인하기
- `openex.c`는 여러 파일을 순차적으로 열어 할당되는 파일 디스크립터 번호를 출력합니다. 이를 통해 커널이 사용 가능한 가장 낮은 정수 값을 `fd`로 할당하는 원리를 확인할 수 있습니다.
- `a.txt`, `b.txt`, `c.txt` 파일을 미리 생성해 둡니다.

  ```c
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <unistd.h>
  
  int main(int argc, char *argv[])
  {
      int fd1,fd2,fd3;
      // 표준 입출력(0,1,2)이 이미 사용 중이므로 3부터 할당됨
      fd1 = open(argv[1], O_RDWR);
      printf("파일 %s 열기 성공 : %d\n", argv[1], fd1);
  
      fd2 = open(argv[2], O_RDWR);
      printf("파일 %s 열기 성공 : %d\n", argv[2], fd2);
  
      fd3 = open(argv[3], O_RDWR);
      printf("파일 %s 열기 성공 : %d\n", argv[3], fd3);
  
      close(fd1);
      close(fd2);
      close(fd3);
      exit(0);
  }
  ```
  - **컴파일 및 실행**
    ```bash
    gcc -o openex openex.c
    ./openex a.txt b.txt c.txt
    ```
    - **실행 결과**
    ```
    파일 a.txt 열기 성공 : 3
    파일 b.txt 열기 성공 : 4
    파일 c.txt 열기 성공 : 5
    ```

### 3. 로우 레벨 함수로 파일 복사 프로그램 만들기
- `open`, `read`, `write`, `close` 시스템 호출을 모두 사용하여 한 파일을 다른 파일로 복사하는 예제입니다.

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <unistd.h>

  #define BUFFER_SIZE 1024

  int main(int argc, char *argv[]) {
      int source_fd, dest_fd;
      ssize_t n;
      char buffer[BUFFER_SIZE];

      if (argc != 3) {
          fprintf(stderr, "사용법: %s <원본파일> <대상파일>\n", argv[0]);
          exit(1);
      }

      // 원본 파일 열기 (읽기 전용)
      source_fd = open(argv[1], O_RDONLY);
      if (source_fd < 0) {
          perror("원본 파일 열기 실패");
          exit(1);
      }

      // 대상 파일 열기 (쓰기 전용, 없으면 생성, 이미 있으면 내용 삭제)
      dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (dest_fd < 0) {
          perror("대상 파일 열기 실패");
          exit(1);
      }

      // 원본에서 읽어서 대상에 쓰기
      while ((n = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
          if (write(dest_fd, buffer, n) != n) {
              perror("쓰기 오류");
              exit(1);
          }
      }
      if (n < 0) {
          perror("읽기 오류");
          exit(1);
      }

      close(source_fd);
      close(dest_fd);
      printf("파일 복사 완료: %s -> %s\n", argv[1], argv[2]);
      
      return 0;
  }