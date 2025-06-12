# 📝 12주차 학습 정리

## 📅 날짜
- 2025-05-23

## 📌 주제
- 프로세스 생성과 제어: `fork()` 시스템 호출
- 부모-자식 프로세스의 관계 이해
- 자식 프로세스 종료 대기: `wait()`, `waitpid()`
- `exit()`를 이용한 프로세스 흐름 제어

---

## 📖 이론 정리

### 🔹 `fork()` 시스템 호출: 프로세스의 복제
- **`pid_t fork(void);`**: 현재 실행 중인 프로세스(부모 프로세스)를 그대로 복제하여 새로운 프로세스(자식 프로세스)를 생성하는 시스템 호출입니다.
- **동작 원리**: `fork()`가 호출되면, 운영체제는 부모 프로세스의 메모리 공간, 열린 파일 디스크립터, 각종 변수 등 대부분의 문맥(context)을 그대로 복사한 자식 프로세스를 만듭니다.
- **반환 값의 중요성**: `fork()`는 호출된 이후, 부모와 자식에게 서로 다른 값을 반환합니다.
  - **부모 프로세스에게**: 생성된 **자식 프로세스의 PID(Process ID)**를 반환합니다.
  - **자식 프로세스에게**: **0**을 반환합니다.
  - **생성 실패 시**: **-1**을 반환합니다.
- 이 반환 값의 차이를 이용해 `if`문으로 분기하여 부모와 자식이 수행할 작업을 다르게 코딩할 수 있습니다.

### 🔹 자식 프로세스 제어: `wait()`와 `waitpid()`
부모 프로세스는 자식 프로세스의 종료를 기다리고 상태 정보를 얻기 위해 `wait()` 계열의 함수를 사용합니다. 이는 자식 프로세스가 종료된 후에도 시스템에 정보가 남아있는 **좀비 프로세스(Zombie Process)**가 되는 것을 방지하는 중요한 과정입니다.

- **`pid_t wait(int *status);`**:
  - 자신의 자식 프로세스 중 **아무나 하나**가 종료될 때까지 부모 프로세스를 대기(block)시킵니다.
  - 종료된 자식의 PID를 반환하며, `status` 포인터를 통해 종료 상태(exit code 등)를 전달받습니다.
- **`pid_t waitpid(pid_t pid, int *status, int options);`**:
  - `wait()`보다 더 정교한 제어가 가능합니다.
  - 특정 PID를 지정하여 **해당 자식 프로세스만** 기다릴 수 있습니다.
  - `options` 인자를 통해 대기 방식을 변경할 수 있습니다. (예: `WNOHANG` - 기다리지 않고 즉시 반환)

### 🔹 `exit()` 시스템 호출의 역할
- **`void exit(int status);`**: 프로세스를 즉시 종료시키는 함수입니다.
- `fork()`를 여러 번 사용하는 코드에서 `exit()`는 매우 중요합니다. 자식 프로세스가 자신의 임무를 마친 후 `exit()`를 호출하여 스스로 종료하지 않으면, 부모의 코드 흐름을 따라 내려가 의도치 않게 또 다른 자식 프로세스(손자 프로세스)를 생성할 수 있습니다. 각 자식 프로세스의 작업 범위 끝에 `exit()`를 명시하여 프로세스 계층 구조가 꼬이는 것을 방지해야 합니다.

---

## 🛠️ 실습 내용

### 1. `fork()`의 기본 동작 (`fork1.c`)
- `fork()` 호출 한 번으로 두 개의 프로세스(부모, 자식)가 생성되며, `fork()` 이후의 모든 코드를 각자 실행하는 것을 보여줍니다.
  ```c
  #include <stdio.h>
  #include <unistd.h>
  
  int main()
  {
      int pid;
      printf("[%d] 프로세스 시작\n", getpid());
      pid = fork();
      // fork() 이후부터는 부모와 자식, 두 프로세스가 아래 코드를 모두 실행
      printf("[%d] 프로세스: 리턴값 %d\n", getpid(), pid);
  }
  ```
  **결과 분석**: `fork()` 이후의 `printf`가 두 번씩 출력되며, 부모 프로세스는 `pid` 값으로 자식의 PID를, 자식 프로세스는 0을 출력합니다.

### 2. 부모와 자식 프로세스 구분 (`fork2.c`)
- `fork()`의 반환 값을 `if`문으로 확인하여 부모와 자식의 실행 코드를 분리하는 가장 기본적인 패턴입니다.
  ```c
  #include <stdio.h>
  #include <unistd.h>
  
  int main()
  {
      int pid = fork();
      if(pid == 0) {
          // 자식 프로세스가 실행할 코드
          printf("[Child]: Hello, world! My PID is %d\n", getpid());
      } else {
          // 부모 프로세스가 실행할 코드
          printf("[Parent]: Hello, world! My PID is %d\n", getpid());
      }
  }
  ```

### 3. 여러 자식 프로세스 생성과 `exit()`의 중요성 (`fork3.c`)
- 부모 프로세스가 두 개의 자식 프로세스를 생성하는 예제입니다. 첫 번째 자식 프로세스가 임무를 마친 후 `exit(0)`를 호출하여, 두 번째 `fork()`를 실행하지 않도록 하는 것이 핵심입니다.
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  
  int main()
  {
      int pid1, pid2;
      pid1 = fork();
      if (pid1 == 0) { // 자식 1
          printf("[Child 1]: Hello, world! pid=%d\n", getpid());
          exit(0); // 자식 1은 여기서 작업을 마치고 종료
      }
  
      pid2 = fork();
      if (pid2 == 0) { // 자식 2
          printf("[Child 2]: Hello, world! pid=%d\n", getpid());
          exit(0); // 자식 2도 여기서 종료
      }
      
      // 부모만 이 코드를 실행
      printf("[PARENT]: All children created.\n");
  }
  ```

### 4. 자식 프로세스 종료 기다리기 (`wait()`) (`fork4.c`)
- 부모 프로세스가 `wait()`를 호출하여 자식 프로세스가 끝날 때까지 기다리고, 자식의 종료 코드를 받아오는 예제입니다.
  ```c
  #include <sys/wait.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  
  int main()
  {
      int pid, child, status;
      printf("[%d] 부모 프로세스 시작\n", getpid());
      pid = fork();
      if (pid == 0) {
          printf("[%d] 자식 프로세스 시작\n", getpid());
          exit(1); // 자식은 1을 반환하며 종료
      }
      child = wait(&status); // 자식이 끝날 때까지 대기
      printf("[%d] 자식 프로세스 %d 종료\n", getpid(), child);
      printf("\t종료 코드: %d\n", status >> 8); // status에서 실제 종료 코드 추출
  }
  ```

### 5. 특정 자식 프로세스 기다리기 (`waitpid()`) (`fork5.c`)
- 부모가 두 자식을 생성한 후, `waitpid()`를 사용해 **첫 번째 자식(pid1)이 종료될 때까지만** 명시적으로 기다리는 예제입니다.
  ```c
  #include <sys/wait.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  
  int main()
  {
      int pid1, pid2, child, status;
  
      printf("[%d] 부모 프로세스 시작\n", getpid());
      pid1 = fork();
      if (pid1 == 0) { // 자식 1
          printf("[%d] 자식 프로세스[1] 시작 -> 1초 후 종료\n", getpid());
          sleep(1);
          exit(1);
      }
  
      pid2 = fork();
      if (pid2 == 0) { // 자식 2
          printf("[%d] 자식 프로세스[2] 시작 -> 2초 후 종료\n", getpid());
          sleep(2);
          exit(2);
      }
  
      // pid1 자식 프로세스만 기다림
      child = waitpid(pid1, &status, 0);
      printf("[%d] 자식 프로세스 #1 (%d) 종료 확인\n", getpid(), child);
      printf("\t종료 코드: %d\n", status >> 8);
  }