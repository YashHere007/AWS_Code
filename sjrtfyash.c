#include <stdio.h>
#include <limits.h>


struct Process {
    int pid;              
    int burst_time;       
    int remaining_time;   
    int waiting_time;     
    int turnaround_time;  
    int arrival_time;
    int priority;   
};

// Function to calculate waiting and turnaround times using SRTF
void calculate(struct Process proc[], int n) {
    int time = 0;       // Current time
    int completed = 0;  // Number of completed processes
    int shortest = 0;   // Index of the shortest process
    int min_remaining = INT_MAX;
    int finish_time;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (completed < n) {
        // Find the process with the shortest remaining time
        min_remaining = INT_MAX;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time && proc[i].remaining_time > 0 && proc[i].remaining_time < min_remaining) {
                min_remaining = proc[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        // Execute the process for 1 time unit
        proc[shortest].remaining_time--;
        time++;

        // If process is completed
        if (proc[shortest].remaining_time == 0) {
            completed++;
            finish_time = time;
            proc[shortest].turnaround_time = finish_time - proc[shortest].arrival_time;
            proc[shortest].waiting_time = proc[shortest].turnaround_time - proc[shortest].burst_time;
        }
    }

    // Print results
    printf("\nProcess ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].arrival_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage waiting time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround_time / n);
}

// Main function
int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        proc[i].pid = i + 1;
    }

    // Run the SRTF scheduling algorithm
    calculate(proc, n);

    return 0;
}
