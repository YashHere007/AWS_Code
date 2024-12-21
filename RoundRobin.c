#include <stdio.h>

struct Process {
    int pid; 
    int burst_time; 
    int remaining_time; 
    int waiting_time;
    int turnaround_time; 
};

void calculate(struct Process proc[], int n, int quantum) {
    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                    proc[i].turnaround_time = time;
                    completed++;
                }
            }
        }
    }

    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage waiting time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
    }
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    calculate(proc, n, quantum);
    return 0;
}
