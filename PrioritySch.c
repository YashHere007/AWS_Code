#include <stdio.h>

struct Process {
    int pid; 
    int burst_time; 
    int priority; 
    int waiting_time; 
    int turnaround_time; 
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void PriorityScheduling(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    int total_waiting_time = 0, total_turnaround_time = 0;

    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);

    printf("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage waiting time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround_time / n);
}


int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
        printf("Enter priority for process %d (lower number = higher priority): ", proc[i].pid);
        scanf("%d", &proc[i].priority);
    }

    PriorityScheduling(proc, n);
    return 0;
}
