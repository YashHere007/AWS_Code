#include <stdio.h>

struct Process {
    int pid; 
    int burst_time; 
    int waiting_time; 
    int turnaround_time;
    int arrival_time;
};



void sortProcessesByBurstTime(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
           if (proc[i].burst_time > proc[j].burst_time) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}
void calculate(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    sortProcessesByBurstTime(proc,n);
    printf("\n Waiting Time Calculation Here ");
    int i,j,sum = 0;
    for(i=0;i<n;i++){
        int u = proc[i].burst_time-proc[i].arrival_time;
        sum+=u;
    }
    int sumfinal = 0;
    for(i=n-1;i>=0;i--){
        sum-=proc[i].burst_time;
        proc[i].waiting_time = sum;
        printf("\nWaiting Time for vP[%d] =  %d",i,proc[i].waiting_time);
        sumfinal+=sum;
    }
    int i,j,sumfinal = 0,k=0;int sum = 0;
    while(k<n)
    {
        sum+=proc[i].burst_time;
        sumfinal+=sum;
        proc[k].turnaround_time = sumfinal;
        ++k;
    }
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\tArrival Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time,proc[i].arrival_time);
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
        printf("Enter Arrival time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].arrival_time);
    }

    
    calculate(proc, n);

    return 0;
}
