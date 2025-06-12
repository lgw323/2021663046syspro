# 🐧 리눅스 필수 명령어 51선

리눅스 시스템 관리 및 개발 환경에서 자주 사용되는 필수 명령어 51개를 기능별 5가지 테마로 분류하여 정리했습니다.

---
### 📁 파일 및 디렉토리 관리 (16개)

| 명령어 | 주요 기능 | 대표 사용 예시 |
| :--- | :--- | :--- |
| `ls` | 디렉토리 내의 파일 및 폴더 목록을 보여줍니다. | `ls -alF` |
| `cp` | 파일이나 디렉토리를 복사합니다. | `cp -r source_dir dest_dir` |
| `mv` | 파일이나 디렉토리를 이동시키거나 이름을 변경합니다. | `mv old_name new_name` |
| `rm` | 파일이나 디렉토리를 삭제합니다. | `rm -rf directory` |
| `mkdir`| 새로운 디렉토리를 생성합니다. | `mkdir -p /path/to/new_dir` |
| `rmdir`| 비어있는 디렉토리를 삭제합니다. | `rmdir empty_dir` |
| `touch` | 빈 파일을 생성하거나 파일의 수정 시간을 변경합니다. | `touch new_file.txt` |
| `find` | 특정 조건의 파일을 검색합니다. | `find . -name "*.c"` |
| `locate` | 파일 데이터베이스를 사용하여 파일을 빠르게 검색합니다. | `locate httpd.conf` |
| `du` | 디렉토리 또는 파일의 디스크 사용량을 보여줍니다. | `du -sh /home/user` |
| `df` | 파일 시스템의 디스크 공간 사용 현황을 보여줍니다. | `df -h` |
| `ln` | 파일에 대한 하드 링크나 심볼릭 링크를 생성합니다. | `ln -s /path/to/original link_name` |
| `chmod` | 파일이나 디렉토리의 접근 권한을 변경합니다. | `chmod -R 755 directory` |
| `chown` | 파일이나 디렉토리의 소유자 및 그룹을 변경합니다. | `chown -R user:group directory` |
| `stat` | 파일의 상세 정보(inode, 크기, 시간 등)를 보여줍니다. | `stat filename` |
| `tree` | 디렉토리 구조를 트리 형태로 보여줍니다. | `tree -L 2` |

---
### 📄 파일 내용 확인 및 처리 (12개)

| 명령어 | 주요 기능 | 대표 사용 예시 |
| :--- | :--- | :--- |
| `cat` | 파일 내용을 화면에 출력하거나 여러 파일을 합칩니다. | `cat file1.txt file2.txt` |
| `more` | 파일 내용을 페이지 단위로 보여줍니다. (아래로만 이동) | `more large_file.log` |
| `less` | `more`보다 향상된 기능으로, 위아래 이동 및 검색이 가능합니다. | `less large_file.log` |
| `head` | 파일의 앞부분 몇 줄을 보여줍니다. | `head -n 20 file.txt` |
| `tail` | 파일의 뒷부분 몇 줄을 보여주거나, 실시간으로 추가되는 내용을 감시합니다. | `tail -f /var/log/syslog` |
| `nl` | 파일 내용에 행 번호를 붙여 출력합니다. | `nl source_code.c` |
| `wc` | 파일의 줄 수, 단어 수, 바이트 수를 셉니다. | `wc -l file.txt` |
| `sort` | 텍스트 파일의 내용을 정렬합니다. | `sort -rn numbers.txt` |
| `uniq` | 정렬된 파일에서 중복된 행을 제거하거나 중복 횟수를 보여줍니다. | `sort file.txt \| uniq -c` |
| `diff` | 두 파일 간의 차이점을 비교합니다. | `diff -u old.c new.c` |
| `patch` | `diff`로 생성된 패치 파일을 원본 파일에 적용합니다. | `patch < patch_file` |
| `cut` | 파일의 각 행에서 특정 필드(열)를 잘라냅니다. | `cut -d':' -f1 /etc/passwd` |

---
### 💻 시스템 정보 및 프로세스 관리 (13개)

| 명령어 | 주요 기능 | 대표 사용 예시 |
| :--- | :--- | :--- |
| `ps` | 현재 실행 중인 프로세스의 목록과 상태를 보여줍니다. | `ps aux` |
| `top` | 시스템의 프로세스 및 자원 사용률을 실시간으로 보여줍니다. | `top` |
| `htop` | `top`보다 향상된 인터페이스를 제공하는 프로세스 뷰어입니다. | `htop` |
| `free` | 시스템의 메모리(RAM, swap) 사용 현황을 보여줍니다. | `free -h` |
| `kill` | 특정 PID의 프로세스에 신호를 보내 종료시킵니다. | `kill -9 12345` |
| `pkill` | 프로세스 이름을 이용하여 프로세스를 종료시킵니다. | `pkill nginx` |
| `uptime` | 시스템이 얼마나 오랫동안 켜져 있었는지 보여줍니다. | `uptime` |
| `date` | 현재 시스템의 날짜와 시간을 보여주거나 설정합니다. | `date '+%Y-%m-%d'` |
| `cal` | 달력을 보여줍니다. | `cal` |
| `history`| 이전에 사용했던 명령어 목록을 보여줍니다. | `history \| grep ssh` |
| `uname` | 커널 이름 등 시스템 정보를 보여줍니다. | `uname -a` |
| `who` | 현재 시스템에 로그인한 사용자 목록을 보여줍니다. | `who` |
| `last` | 최근 로그인 기록을 보여줍니다. | `last` |

---
### 🛠️ 텍스트 검색 및 가공 (5개)

| 명령어 | 주요 기능 | 대표 사용 예시 |
| :--- | :--- | :--- |
| `grep` | 텍스트나 파일 내에서 특정 패턴(문자열)을 검색합니다. | `grep -ir "error" /var/log` |
| `awk` | 열(column) 단위의 강력한 패턴 검색 및 처리 언어입니다. | `awk '{print $1, $4}' log.txt` |
| `sed` | 스트림 에디터로, 텍스트를 편집(치환, 삭제 등)하는 데 사용됩니다. | `sed 's/old/new/g' file.txt` |
| `tr` | 문자 단위로 변환하거나 삭제합니다. | `cat file.txt \| tr 'a-z' 'A-Z'` |
| `xargs` | 표준 입력으로 받은 데이터를 다른 명령어의 인자로 넘겨줍니다. | `find . -name "*.tmp" \| xargs rm` |

---
### 🌐 네트워크 (5개)

| 명령어 | 주요 기능 | 대표 사용 예시 |
| :--- | :--- | :--- |
| `ping` | 특정 호스트(서버)에 네트워크 신호를 보내 응답을 확인합니다. | `ping -c 4 google.com` |
| `netstat`| 네트워크 연결, 라우팅 테이블, 인터페이스 통계 등을 보여줍니다. | `netstat -tulnp` |
| `ss` | `netstat`을 대체하는 소켓 통계 확인 명령어입니다. | `ss -lntp` |
| `curl` | URL을 통해 데이터를 전송받거나 보내는 도구입니다. | `curl -L https://example.com` |
| `wget` | 네트워크에서 파일을 다운로드합니다. | `wget -O image.jpg "URL"` |
