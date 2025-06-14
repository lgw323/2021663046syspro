# 📝 6주차 학습 정리

## 📅 날짜
- 2025-04-11

## 📌 주제
- `vi` (Vim) 텍스트 에디터 기본 사용법
- 셸 스크립트(Shell Script) 작성 및 실행
- 스크립트 실행 권한 부여 (`chmod`)
- 스크립트 인자(Argument) 활용 (`$1`)

---

## 📖 이론 정리

### 🔹 셸 스크립트(Shell Script)란?
- 셸(Shell)에서 실행할 명령어들의 순차적인 나열을 담고 있는 텍스트 파일입니다.
- 반복적인 작업을 자동화하거나 여러 명령어를 묶어 하나의 작업으로 만들 때 유용합니다.
- 스크립트 파일의 첫 줄에는 보통 `#!/bin/bash` 와 같은 **Shebang(셔뱅)**을 추가하여 이 스크립트를 어떤 셸로 실행할지 명시해줍니다.

### 🔹 vi (Vim) 에디터
- 리눅스의 대표적인 터미널 기반 텍스트 에디터로, **모드(mode)**를 가지는 것이 특징입니다.
- **명령 모드 (Command Mode)**
  - `vi` 실행 시 기본 모드입니다. 키보드 입력은 명령으로 인식됩니다.
  - `esc` 키를 누르면 언제든지 명령 모드로 돌아올 수 있습니다.
- **입력 모드 (Insert Mode)**
  - 명령 모드에서 `i` 키를 누르면 진입하며, 텍스트를 자유롭게 입력할 수 있습니다.
- **마지막 행 모드 (Last-Line Mode)**
  - 명령 모드에서 `:` 키를 눌러 진입합니다. 파일 저장, 종료 등 추가 명령을 입력합니다.
  - `:w` : 파일 저장 (write)
  - `:q` : 종료 (quit)
  - `:wq` : 저장 후 종료 (write and quit)
  - `:q!` : 저장하지 않고 강제 종료

### 🔹 파일 권한과 chmod
- 리눅스 파일은 **읽기(r), 쓰기(w), 실행(x)** 권한을 가지며, **소유자(user), 그룹(group), 그 외 사용자(others)**에 대해 개별적으로 설정할 수 있습니다.
- `chmod` 명령어는 파일의 권한을 변경합니다.
- `chmod u+x [파일명]` : 파일의 소유자(`u`)에게 실행(`x`) 권한을 추가(`+`)합니다. 셸 스크립트 파일을 실행 가능하게 만들 때 반드시 필요한 과정입니다.

### 🔹 스크립트 실행과 인자
- **실행**: `./[스크립트 파일명]` 형식으로 현재 디렉토리에 있는 스크립트를 실행합니다. `./`는 현재 디렉토리를 의미합니다.
- **인자 (Positional Parameters)**: 스크립트를 실행할 때 함께 전달하는 값입니다. 스크립트 내부에서 `$1`, `$2`, ... 와 같은 변수로 접근할 수 있습니다.
  - `$0`: 실행된 스크립트의 이름
  - `$1`: 첫 번째 인자
  - `$2`: 두 번째 인자

---

## 🛠️ 실습 내용

1. **파일을 즉시 생성하고 실행하는 셸 스크립트 `st` 만들기**
   - `st`라는 이름의 셸 스크립트를 생성합니다.
   - 이 스크립트는 파일 이름을 인자(`$1`)로 받습니다.
   - 받은 파일 이름으로 `vi` 에디터를 열어 내용을 작성하게 합니다.
   - `vi` 에디터를 저장하고 종료하면, 해당 파일에 즉시 실행 권한(`u+x`)을 부여하고 바로 실행합니다.

   **`st` 스크립트 내용**
   ```bash
   #!/bin/bash
   # 첫 번째 인자로 받은 파일을 vi로 엽니다.
   vi $1
   # 해당 파일에 소유자 실행 권한을 부여합니다.
   chmod u+x $1
   # 파일을 실행합니다.
   ./$1