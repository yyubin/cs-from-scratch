# CS From Scratch 🛠️  
직접 구현하며 배우는 컴퓨터 사이언스

## 📚 소개

이 저장소는 운영체제, 시스템 프로그래밍, 네트워크, 분산 시스템 등 컴퓨터 사이언스의 핵심 개념들을 **직접 구현해보며 학습**한 내용을 정리한 공간입니다. 단순히 책을 읽는 것을 넘어서, 핵심 개념을 손으로 구현하고 실험하며 더 깊이 있게 이해하는 것을 목표로 합니다.

### 💡 참고한 서적

- 📘 [OSTEP](http://pages.cs.wisc.edu/~remzi/OSTEP/) - *Operating Systems: Three Easy Pieces*  
  → 스케줄링, 메모리, 파일 시스템 등 운영체제 전반에 대한 핵심 구현

- 📘 [CSAPP] - *Computer Systems: A Programmer’s Perspective*  
  → 메모리, 어셈블리, 함수 호출 스택, 바이너리 이해를 위한 실습

- 📘 [Top-down Network] - *Computer Networking: A Top-Down Approach*  
  → 네트워크 계층별 구조 및 소켓 통신 등 구현 예정

- 📘 [DDIA] - *Designing Data-Intensive Applications*  
  → 분산 시스템, 데이터 모델링, 로그 시스템 등 향후 구현 대상

---

## 🗂️ 디렉토리 구조

```
├── mini_shell # fork/exec 기반 셸 구현 (C)
├── round_robin # 라운드 로빈 CPU 스케줄링 시뮬레이터 (C++)
├── mlfq # 다단계 피드백 큐 스케줄링 시뮬레이터 (Python)
├── bin # 실행 파일 저장 디렉토리
└── .vscode # VSCode 실행/빌드 설정
```

---

## 🧪 구현 목표 예시

| 주제 | 구현 예 |
|------|--------|
| 운영체제 | 셸, 스케줄링 알고리즘 (MLFQ, RR), 메모리 할당 시뮬레이터 |
| 시스템 프로그래밍 | fork/exec, 파일 디스크립터, 파이프, 시그널 처리 등 |
| 네트워크 | 소켓 통신, HTTP 서버 (예정) |
| 분산 시스템 | 로그 시스템, 메시지 큐, 키-밸류 저장소 등 (예정) |

---

## 🔧 실행 방법

```bash
# 예: mini_shell 실행
cd mini_shell
gcc mini_shell.c -o mini_shell
./mini_shell
```
또는 Python 프로젝트의 경우,

```
cd mlfq
python mlfq.py
```
## 👨‍💻 개발자 노트
이 프로젝트는 CS의 핵심 개념을 체화하기 위해 **바퀴를 다시 만들어보는 과정**입니다. 상용 수준의 복잡한 개념을 그대로 복제하기보다는, 핵심 동작 원리를 최소한의 코드로 구현하고 학습하는 데 초점을 맞춥니다.
