#include <stdio.h>
#include <limits.h> // For INT_MAX

#define MAX_PROCESSES 10
 struct Process {
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} ;

void calculate_srtf(struct Process proc[], int n) {
    int time = 0;
    int completed = 0;
    int min_index;
    int i, j;
    int is_process_available = 0;

    while (completed < n) {
        min_index = 0;
        int min_remaining_time = 9999999;

        // Find the process with the shortest remaining time that is ready to execute
        for (i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
                is_process_available = 1;
                if (proc[i].remaining_time < min_remaining_time) {
                    min_remaining_time = proc[i].remaining_time;
                    min_index = i;
                }
            }
        }

        if (is_process_available == 0) {
            time++;
            continue;
        }

        // Execute the process with the shortest remaining time
        proc[min_index].remaining_time--;
        if (proc[min_index].remaining_time == 0) {
            proc[min_index].completion_time = time + 1;
            proc[min_index].turnaround_time = proc[min_index].completion_time - proc[min_index].arrival_time;
            proc[min_index].waiting_time = proc[min_index].turnaround_time - proc[min_index].burst_time;
            completed++;
        }
        time++;
        is_process_available = 0;
    }
}

void print_process_info(struct Process processes[], int num_processes) {
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
            i + 1,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);
    }
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int num_processes;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    for (int i = 0; i < num_processes; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculate_srtf(processes, num_processes);
    print_process_info(processes, num_processes);

    return 0;
}
