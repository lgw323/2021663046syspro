# 📝 10주차 학습 정리

## 📅 날짜
- 2025-05-09

## 📌 주제
- 파일 디스크립터 복제 (`dup`, `dup2`)
- 파일의 임의 접근(Random Access)과 `lseek()`
- 파일 내용 확인 유틸리티 (`xxd`)

---

## 📖 이론 정리

### 🔹 파일 복사와 버퍼링
- 셸 명령어 `cp 원본파일 대상파일`은 지난주에 실습한 파일 복사 프로그램과 동일한 원리로 동작합니다.
- 파일을 복사할 때, 프로그램은 원본 파일의 데이터를 한 번에 모두 읽는 것이 아니라, 특정 크기의 임시 저장 공간(**버퍼, buffer**)에 일부를 읽어온 후, 그 내용을 대상 파일에 쓰는 과정을 반복합니다. 이 버퍼의 크기에 따라 입출력 성능이 달라질 수 있습니다.

### 🔹 파일 디스크립터 복제 (`dup`, `dup2`)
`dup`과 `dup2`는 기존에 열려 있는 파일 디스크립터를 복제하는 시스템 호출입니다. 두 디스크립터는 같은 파일을 가리키게 되며, 파일 오프셋(읽기/쓰기 위치)과 상태 플래그를 공유합니다.

- **`int dup(int oldfd);`**
  - `oldfd`가 가리키는 파일을 가리키는 **새로운 파일 디스크립터를 생성**하여 반환합니다.
  - 새로 생성되는 디스크립터는 현재 사용 가능한 **가장 낮은 번호**의 정수 값으로 할당됩니다.
- **`int dup2(int oldfd, int newfd);`**
  - `newfd`가 `oldfd`와 동일한 파일을 가리키도록 만듭니다.
  - 만약 `newfd`가 이미 사용 중이었다면, `dup2`는 해당 디스크립터를 먼저 닫고 재사용합니다.
  - 이 특징 때문에 **입출력 리다이렉션(Redirection)**에 매우 유용하게 사용됩니다. 예를 들어, `dup2(file_fd, 1)`을 호출하면 표준 출력(fd=1)이 `file_fd`가 가리키는 파일로 재지정되어, 이후 `printf`와 같은 함수의 출력이 화면이 아닌 파일에 쓰이게 됩니다.

### 🔹 파일의 임의 접근(Random Access)과 `lseek()`
- `read()`와 `write()`는 파일의 현재 위치(offset)부터 순차적으로 동작하지만, `lseek()` 시스템 호출을 사용하면 이 위치를 원하는 곳으로 자유롭게 이동시킬 수 있습니다.
- **`off_t lseek(int fd, off_t offset, int whence);`**
  - `fd`: 파일 디스크립터
  - `offset`: `whence`를 기준으로 이동할 바이트 수
  - `whence`: 이동의 기준점
    - `SEEK_SET`: 파일의 시작 지점
    - `SEEK_CUR`: 현재 위치
    - `SEEK_END`: 파일의 끝 지점
- 이를 통해 파일의 아무 위치에서나 읽고 쓰는 **임의 접근(Random Access)**이 가능해집니다. 고정된 크기의 레코드(record) 단위로 데이터가 저장된 파일에서 특정 레코드를 수정하거나 읽어올 때 매우 효과적입니다.

### 🔹 파일 헥사 덤프 (`xxd`)
- `xxd [파일명]` 명령어는 파일의 내용을 16진수(hexadecimal)와 아스키(ASCII) 문자로 함께 보여주는 유틸리티입니다.
- 일반 텍스트 에디터로 볼 수 없는 바이너리 파일의 내용을 확인하거나, 파일의 특정 위치에 데이터가 정확히 쓰였는지 검증할 때 유용합니다.

---

## 🛠️ 실습 내용

### 1. `dup2`를 이용한 출력 리다이렉션
- `dup2`를 사용하여 표준 출력(stdout, fd=1)의 대상을 파일로 바꾸는 예제입니다. `printf`의 결과가 터미널이 아닌 파일에 저장되는 것을 확인할 수 있습니다.

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <unistd.h>
  
  int main() {
      int fd;
      char *filename = "output.txt";
  
      // 1. 파일을 쓰기 모드로 열기 (없으면 생성)
      fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd < 0) {
          perror("open");
          exit(1);
      }
  
      // 2. 표준 출력(fd=1)을 파일 디스크립터 fd로 복제(재지정)
      if (dup2(fd, 1) < 0) {
          perror("dup2");
          exit(1);
      }
  
      // 3. 이 printf는 이제 터미널이 아닌 output.txt 파일에 쓰여짐
      printf("이 내용은 파일에 저장됩니다.\n");
      printf("dup2를 통해 표준 출력이 리다이렉션되었습니다.\n");
  
      close(fd); // 복제된 stdout은 여전히 열려있지만 원본 fd는 닫음
      
      return 0;
  }
  ```
  - **실행 방법**: 위 코드를 `dup_test.c`로 저장 후 컴파일(`gcc -o dup_test dup_test.c`)하고 실행(`./dup_test`)하면, 터미널에는 아무것도 출력되지 않고 `output.txt` 파일에 `printf` 내용이 저장됩니다.

### 2. `lseek`를 이용한 레코드 수정
- 고정 길이 레코드로 이루어진 파일의 특정 부분을 `lseek`으로 찾아가 수정하는 예제입니다.

  ```c
  #include <stdio.h>
  #include <string.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <stdlib.h>
  
  typedef struct {
      int id;
      char name[20];
  } Record;
  
  int main() {
      int fd;
      Record rec;
      char *filename = "records.dat";
  
      // 1. 초기 데이터 파일 생성
      fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      for (int i=0; i<3; i++) {
          rec.id = i + 1;
          sprintf(rec.name, "record-%d", i + 1);
          write(fd, &rec, sizeof(Record));
      }
      close(fd);
  
      // 2. 파일 다시 열고, 2번째 레코드(인덱스 1) 수정
      fd = open(filename, O_RDWR);
      
      // 파일 시작(SEEK_SET)에서 1 * sizeof(Record) 바이트만큼 이동
      lseek(fd, 1 * sizeof(Record), SEEK_SET);
      
      // 새로운 데이터로 덮어쓰기
      rec.id = 99;
      strcpy(rec.name, "UPDATED_RECORD");
      write(fd, &rec, sizeof(Record));
  
      close(fd);
      printf("'%s' 파일의 2번째 레코드를 수정했습니다.\n", filename);
      printf("'xxd %s' 명령어로 결과를 확인해보세요.\n", filename);
      
      return 0;
  }
  ```
  - **실행 방법**: 위 코드를 컴파일하고 실행한 뒤, 터미널에 `xxd records.dat`를 입력하여 2번째 레코드 부분이 `UPDATED_RECORD`로 변경되었는지 16진수 값으로 직접 확인할 수 있습니다.