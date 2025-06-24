from collections import deque
import time # 시뮬레이션을 위해 추가

# Process 클래스는 상태 저장에 집중
class Process:
    def __init__(self, number, total_time, io_interval=0):
        self.number = number
        self.total_time_left = total_time  # 남은 총 실행 시간
        self.io_interval = io_interval     # I/O 발생 주기 (0이면 I/O 없음)
        
        # 스케줄러가 관리할 상태 정보
        self.current_priority = 0          # 현재 속한 큐의 우선순위
        self.time_in_quantum = 0           # 현재 퀀텀에서 실행된 시간

    def run(self):
        """프로세스를 1 time unit 실행"""
        self.total_time_left -= 1
        self.time_in_quantum += 1
        print(f"  - P{self.number} 실행 (남은 시간: {self.total_time_left})")

    def is_finished(self):
        """프로세스가 끝났는지 확인"""
        return self.total_time_left <= 0
        
    def needs_io(self):
        """I/O가 필요한지 확인"""
        if self.io_interval > 0 and self.time_in_quantum % self.io_interval == 0:
            return True
        return False

# --- 스케줄러 로직 ---

# 1. 큐 및 설정 초기화
queues = [deque(), deque(), deque()]
# 우선순위가 높을수록 퀀텀을 짧게 설정
QUANTUMS = [2, 4, 8]  # Q0=2, Q1=4, Q2=8
PRIORITY_BOOST_PERIOD = 15 # 15 time ticks 마다 우선순위 초기화

# 2. 프로세스 생성 및 초기 큐에 추가
processes = [
    Process(1, 10, io_interval=3), # P1: 총 10, 3 tick 마다 I/O
    Process(2, 20),                # P2: 총 20, CPU 집중 작업
    Process(3, 15, io_interval=5)  # P3: 총 15, 5 tick 마다 I/O
]

for p in processes:
    queues[0].append(p) # 모든 프로세스는 최상위 큐에서 시작

# 스케줄러 메인 루프
system_time = 0
blocked_queue = [] # I/O 대기 중인 프로세스들을 위한 큐

while any(queues) or any(blocked_queue):
    system_time += 1
    print(f"\n[Time: {system_time}]")

    # Priority Boost 확인
    if system_time % PRIORITY_BOOST_PERIOD == 0 and system_time > 0:
        print("--- PRIORITY BOOST! ---")
        # 모든 준비/대기 큐의 프로세스를 최상위 큐로 이동
        blocked_procs_only = [p for p, wakeup_time in blocked_queue]
        all_procs = list(queues[1]) + list(queues[2]) + blocked_procs_only
        queues[0].extend(all_procs)
        queues[1].clear()
        queues[2].clear()
        blocked_queue.clear()
        for p in queues[0]:
            p.current_priority = 0
            p.time_in_quantum = 0


    # I/O 작업이 끝난 프로세스 복귀
    # 실제로는 I/O 완료 시점에 인터럽트로 처리되지만, 여기서는 간단히 2 tick 후에 복귀한다고 가정
    newly_ready = []
    for p, wakeup_time in blocked_queue:
        if system_time >= wakeup_time:
            print(f"  - P{p.number} I/O 완료. 큐로 복귀.")
            p.time_in_quantum = 0 # 퀀텀 초기화
            queues[p.current_priority].append(p)
            newly_ready.append((p, wakeup_time))
    for item in newly_ready:
        blocked_queue.remove(item)

    # 실행할 프로세스 찾기 (MLFQ 규칙 1)
    current_process = None
    for priority, q in enumerate(queues):
        if q:
            current_process = q.popleft()
            break
    
    # 실행할 프로세스가 있는 경우
    if current_process:
        print(f"큐 Q{current_process.current_priority}에서 P{current_process.number} 선택.")
        current_process.run()

        # 1. 작업 완료 확인
        if current_process.is_finished():
            print(f"  - P{current_process.number} 작업 완료.")
            continue # 다음 타임 틱으로

        # 2. I/O 발생 확인
        if current_process.needs_io():
            print(f"  - P{current_process.number} I/O 발생. 대기 상태로 전환.")
            blocked_queue.append((current_process, system_time + 2)) # 2 tick 동안 대기
            continue

        # 3. 퀀텀 소진 확인 (강등)
        if current_process.time_in_quantum >= QUANTUMS[current_process.current_priority]:
            # 최하위 큐가 아니면 강등
            if current_process.current_priority < len(queues) - 1:
                print(f"  - P{current_process.number} 퀀텀 소진. Q{current_process.current_priority + 1}로 강등.")
                current_process.current_priority += 1
                current_process.time_in_quantum = 0
                queues[current_process.current_priority].append(current_process)
            else:
                # 최하위 큐에서는 RR 방식으로 계속 실행
                print(f"  - P{current_process.number} 퀀텀 소진. 최하위 큐에서 계속 실행.")
                current_process.time_in_quantum = 0
                queues[current_process.current_priority].append(current_process)
        else:
            # 퀀텀이 남았으면 다시 큐의 끝으로 (RR)
            queues[current_process.current_priority].append(current_process)
    else:
        print("  (실행할 프로세스 없음. CPU IDLE)")

    time.sleep(0.1) # 시뮬레이션 속도 조절

print("\n모든 프로세스 실행 완료!")