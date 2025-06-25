# 🌀 Round Robin Scheduler (C++)

**라운드 로빈(Round Robin) 스케줄링**을 직접 구현한 C++ 시뮬레이터입니다.  
운영체제의 CPU 스케줄링 알고리즘 중 하나인 라운드 로빈 방식은 각 프로세스에 동일한 시간 조각(time slice)을 주고 순환하며 실행합니다.

---

## 📌 개요

- 모든 프로세스는 도착 시간이 0이라고 가정
- 프로세스는 실행 시간(`total_time`)만큼 실행되어야 완료
- 각 프로세스는 `time slice`만큼만 CPU를 점유하고, 남은 작업이 있으면 큐의 뒤로 이동
- 완료된 프로세스에 대해 다음 정보를 출력
  - 총 실행 시간
  - 완료 시각
  - 반환 시간(Turnaround Time)
  - 응답 시간(Response Time)

---

## 🧱 사용된 클래스 및 로직

### `Process` 클래스

| 필드 | 설명 |
|------|------|
| `name` | 프로세스 이름 |
| `total_time` | 전체 실행 시간 |
| `executed_time` | 지금까지 실행된 시간 |
| `start_time` | 처음 CPU를 받은 시각 |
| `completion_time` | 실행 완료된 시각 |

### 주요 함수

- `round_robin_scheduler(std::vector<Process>&, int time_slice)`
  - 준비 큐(ready queue)를 기반으로 스케줄링을 수행
  - 각 프로세스의 상태와 통계를 출력

---

## 💻 실행 예시

```bash
g++ -std=c++11 round_robin.cpp -o round_robin
./round_robin
```

출력 예

```
--- 라운드 로빈 스케줄링 시뮬레이션 (타임 슬라이스: 3) ---
[0s - 3s]: A 실행 (남은 시간: 7s)
[3s - 6s]: B 실행 (남은 시간: 2s)
...
A:
  총 실행 시간: 10s
  완료 시각: 21s
  반환 시간: 21s
  응답 시간: 0s

평균 반환 시간: 18.00s
평균 응답 시간: 0.00s
```

## 🧪 샘플 시나리오
```
std::vector<Process> processes_1 = {
    Process("A", 10),
    Process("B", 5),
    Process("C", 8)
};
round_robin_scheduler(processes_1, 3);
```
또는
```
std::vector<Process> processes_2 = {
    Process("P1", 7),
    Process("P2", 3),
    Process("P3", 10)
};
round_robin_scheduler(processes_2, 1);
```
## 📖 관련 개념
- Time Slice (Quantum): 각 프로세스가 CPU를 점유할 수 있는 최대 시간

- Turnaround Time: 프로세스의 총 수행 완료 시간

- Response Time: 처음 CPU를 할당받은 시각

- Ready Queue: CPU를 기다리는 프로세스 대기열

## 🧠 참고
이 코드는 OSTEP의 스케줄링 챕터를 기반으로 구현하였습니다.

운영체제 스케줄링 알고리즘을 직접 실습하며 개념을 이해하기 위한 목적입니다.

