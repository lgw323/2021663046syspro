# 📖 시스템 프로그래밍 학습 저장소 (2025년 1학기)

## 📌 소개
이 저장소는 2025년 1학기 동안 진행된 시스템 프로그래밍 과목의 학습 내용을 주차별로 정리하고, 관련 실습 코드와 과제를 관리하기 위해 만들어졌습니다. 리눅스 환경 설정부터 파일 시스템, 프로세스 제어, 빌드 자동화에 이르기까지 한 학기의 학습 여정이 모두 담겨있습니다.

---

## 📚 주차별 학습 내용 요약

| 주차 (Week) | 핵심 주제 | 상세 내용 (Link) |
| :---: | :--- | :---: |
| **1주차** | 시스템 프로그래밍 O.T, WSL 환경 설정 | [바로가기](./week01/README.md)  |
| **2주차** | 리눅스 디렉토리 구조, 기본 명령어 (`mkdir`, `cat`, `tree`) | [바로가기](./week02/README.md)  |
| **3주차** | 사용자 및 파일 탐색 명령어 (`ls`, `cd`, `whoami`), `gcc` 컴파일 기초 | [바로가기](./week03/README.md)  |
| **4주차** | 파일 속성 및 접근 권한 (`chmod`), 링크 (`ln`), 소유권 변경 (`chown`) | [바로가기](./week04/README.md) |
| **5주차** | C언어 비트 연산 (2진수 변환, 비트 마스킹) | [바로가기](./week05/README.md) |
| **6주차** | 셸 스크립트 작성, `vi` 에디터 사용법, 스크립트 인자 (`$1`) | [바로가기](./week06/README.md) |
| **7주차** | C언어 분할 컴파일, `Makefile`을 이용한 빌드 자동화 | [바로가기](./week07/README.md) |
| **8주차** | 중간고사 및 핵심 내용 복습 | [바로가기](./week08/README.md) |
| **9주차** | 로우 레벨 파일 입출력, 시스템 호출, 파일 디스크립터 (`open`, `read`, `write`) | [바로가기](./week09/README.md) |
| **10주차**| 파일 디스크립터 복제 (`dup`, `dup2`), `lseek`을 이용한 임의 접근 | [바로가기](./week10/README.md) |
| **11주차**| 명령어 옵션 파싱 (`getopt`), `fork()`와 `exec()`를 이용한 프로세스 실행 | [바로가기](./week11/README.md) |
| **12주차**| 프로세스 생성 및 제어 (`fork`, `wait`, `waitpid`, `exit`) | [바로가기](./week12/README.md) |
| **13주차**| 학기 최종 정리 및 발표 안내 | [바로가기](./week13/README.md) |
| **발표** | 한 학기 깃허브 정리와 명령어 50개 | [바로가기](./PPT/README.md)  |

---

## ⭐ 주요 학습 역량 및 프로젝트

-   **Linux Command-Line Proficiency**: 파일 시스템 탐색, 권한 관리 등 리눅스 환경을 능숙하게 제어하는 능력 배양
-   **Shell Scripting for Automation**: 반복적인 작업을 자동화하는 셸 스크립트 작성 능력 습득
-   **C Programming with System Calls**: `fork`, `open`, `read`, `write`, `dup` 등 저수준 시스템 호출을 이용한 C 프로그래밍 능력 강화
-   **Process Creation and Control**: `fork`, `wait`, `exec` 모델을 이해하고 다중 프로세스 환경 제어 능력 함양
-   **Build Management with `Makefile`**: 분할 컴파일된 C 프로젝트의 빌드 과정을 `Makefile`로 자동화
-   **Version Control with Git & GitHub**: Git과 GitHub를 활용하여 학습 과정과 결과물을 체계적으로 관리하는 습관 형성

---

## 🚀 저장소 사용법

각 주차별 디렉토리에는 해당 주차에 학습한 내용을 상세히 기술한 `README.md` 파일과 모든 실습 코드(`*.c`, `*.sh` 등)가 포함되어 있습니다.

```bash
# 예시: 12주차 디렉토리 구조 확인
tree week12

# week12
# ├── fork1.c
# ├── fork2.c
# ├── fork3.c
# ├── fork4.c
# ├── fork5.c
# └── README.md
