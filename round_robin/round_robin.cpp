#include <iostream>
#include <vector>
#include <string>
#include <queue> // std::queue (준비 큐 구현용)
#include <numeric>
#include <iomanip>

class Process
{
public:
    std::string name;
    int total_time;
    int executed_time;
    int start_time;
    int completion_time;

    Process(std::string name, int total_time)
        : name(name), total_time(total_time), executed_time(0), start_time(-1), completion_time(-1) {}

    bool is_completed() const
    {
        return executed_time >= total_time;
    }

    void print() const
    {
        std::cout << "Process(name='" << name << "', total_time=" << total_time
                  << ", executed_time=" << executed_time
                  << ", completed=" << (is_completed() ? "true" : "false") << ")\n";
    }
};

void round_robin_scheduler(std::vector<Process> &processes_data, int time_slice)
{
    std::queue<Process> ready_queue;
    for (const auto &p : processes_data)
    {
        ready_queue.push(p);
    }
    int current_time = 0;
    std::vector<Process> completed_processes;

    std::cout << "--- 라운드 로빈 스케줄링 시뮬레이션 (타임 슬라이스: " << time_slice << ") ---\n";

    while (!ready_queue.empty())
    {
        Process current_process = ready_queue.front();
        ready_queue.pop();

        if (current_process.start_time == -1)
        {
            current_process.start_time = current_time;
        }

        int remaining_time = current_process.total_time - current_process.executed_time;
        int execution_time = std::min(remaining_time, time_slice);

        current_process.executed_time += execution_time;
        current_time += execution_time;

        std::cout << "[" << current_time - execution_time << "s - " << current_time << "s]: "
                  << current_process.name << " 실행 (남은 시간: "
                  << current_process.total_time - current_process.executed_time << "s)\n";

        if (current_process.is_completed())
        {
            current_process.completion_time = current_time;
            completed_processes.push_back(current_process);
            std::cout << "  -> " << current_process.name << " 완료!\n";
        }
        else
        {
            ready_queue.push(current_process);
        }
    }

    std::cout << "\n--- 스케줄링 완료 ---\n";

    double total_turnaround_time = 0;
    double total_response_time = 0;

    std::cout << "\n--- 프로세스별 결과 ---\n";
    for (const auto &p : completed_processes)
    {
        int turnaround_time = p.completion_time; // 도착 시간이 0이라고 가정
        int response_time = p.start_time;        // 도착 시간이 0이라고 가정

        total_turnaround_time += turnaround_time;
        total_response_time += response_time;

        std::cout << p.name << ":\n";
        std::cout << "  총 실행 시간: " << p.total_time << "s\n";
        std::cout << "  완료 시각: " << p.completion_time << "s\n";
        std::cout << "  반환 시간: " << turnaround_time << "s\n";
        std::cout << "  응답 시간: " << response_time << "s\n";
    }

    int num_completed_processes = completed_processes.size();
    if (num_completed_processes > 0)
    {
        double avg_turnaround_time = total_turnaround_time / num_completed_processes;
        double avg_response_time = total_response_time / num_completed_processes;
        std::cout << std::fixed << std::setprecision(2); // 소수점 2자리까지 표시
        std::cout << "\n평균 반환 시간: " << avg_turnaround_time << "s\n";
        std::cout << "평균 응답 시간: " << avg_response_time << "s\n";
    }
    else
    {
        std::cout << "완료된 프로세스가 없습니다.\n";
    }
}

int main()
{
    std::vector<Process> processes_1 = {
        Process("A", 10),
        Process("B", 5),
        Process("C", 8)};

    round_robin_scheduler(processes_1, 3);

    std::cout << "\n"
              << std::string(50, '=') << "\n\n";

    std::vector<Process> processes_2 = {
        Process("P1", 7),
        Process("P2", 3),
        Process("P3", 10)};
    round_robin_scheduler(processes_2, 1);

    return 0;
}