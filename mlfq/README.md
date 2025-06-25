# 🧮 MLFQ Scheduler (Python)

**다단계 피드백 큐(Multi-Level Feedback Queue, MLFQ)** 스케줄링 알고리즘을 파이썬으로 구현한 시뮬레이터입니다.  
우선순위 기반의 큐를 사용하고, I/O 이벤트 및 퀀텀 소진에 따라 프로세스를 동적으로 이동시키며, 주기적으로 우선순위를 리셋하는 Priority Boost를 포함합니다.

---

## 📌 개요

- 총 3단계 큐(Q0, Q1, Q2)를 사용
- 각 큐는 다른 **타임 슬라이스(퀀텀)**를 가짐
  - Q0: 2 tick, Q1: 4 tick, Q2: 8 tick
- I/O가 발생한 프로세스는 **2 tick 후 복귀** 처리
- **15 tick마다** 모든 프로세스의 우선순위를 Q0로 리셋 (Priority Boost)
- 각 프로세스는 `total_time` 동안 실행되어야 완료됨

---

## 🧱 사용된 클래스 및 로직

### `Process` 클래스

| 필드 | 설명 |
|------|------|
| `number` | 프로세스 번호 |
| `total_time_left` | 남은 실행 시간 |
| `io_interval` | I/O 발생 주기 (0이면 없음) |
| `current_priority` | 현재 속한 큐의 우선순위 (0~2) |
| `time_in_quantum` | 현재 퀀텀에서 실행된 시간 |

### 주요 메서드

- `run()`: 프로세스를 1 tick 실행
- `is_finished()`: 프로세스가 완료되었는지 확인
- `needs_io()`: 현재 시점에 I/O가 발생하는지 확인

---

## 🔁 큐 및 스케줄링 규칙

| 규칙 | 설명 |
|------|------|
| **MLFQ Rule 1** | 높은 우선순위 큐부터 검사하며 실행할 프로세스 선택 |
| **I/O 처리** | 실행 중 I/O가 발생하면 2 tick 대기 후 원래 우선순위 큐에 복귀 |
| **퀀텀 소진 시** | 다음 우선순위 큐로 **강등** (단, Q2는 유지) |
| **Priority Boost** | 15 tick마다 모든 프로세스를 Q0로 재배치 |

---

## 💻 실행 방법

```bash
python mlfq.py
````

출력 예

```
[Time: 1]
큐 Q0에서 P1 선택.
  - P1 실행 (남은 시간: 9)
[Time: 2]
  - P1 실행 (남은 시간: 8)
  - P1 I/O 발생. 대기 상태로 전환.
[Time: 3]
큐 Q0에서 P2 선택.
  - P2 실행 (남은 시간: 19)
...
--- PRIORITY BOOST! ---
  - P3 I/O 완료. 큐로 복귀.
```

---

## 🧪 샘플 시나리오

```python
processes = [
    Process(1, 10, io_interval=3), # 3 tick마다 I/O 발생
    Process(2, 20),                # CPU 집중 작업
    Process(3, 15, io_interval=5)  # 5 tick마다 I/O 발생
]
```

---

## 📖 관련 개념

* **Multi-Level Feedback Queue**: 동적으로 프로세스 우선순위를 조정하는 큐 기반 알고리즘
* **Time Slice (Quantum)**: 각 우선순위별 실행 제한 시간
* **Priority Boost**: starvation 방지를 위한 우선순위 초기화
* **Blocking / I/O**: 일정 주기로 발생하는 대기 상태

---

## 🧠 참고

* 이 코드는 [OSTEP](http://pages.cs.wisc.edu/~remzi/OSTEP/)의 `CPU Scheduling` 파트를 기반으로 구현하였습니다.
* 다양한 상황에서 스케줄링 정책이 어떻게 동작하는지 시각적으로 이해하는 데 목적이 있습니다.

