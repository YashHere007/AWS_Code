#include<stdio.h>
#include<stdlib.h>
void fcfswait(int *burst_time,int arrtime,int n)
{
    printf("\n Waiting Time Calculation Here ");
    int i,j,sum = 0;
    for(i=0;i<n;i++){
        int u = burst_time[i]-arrtime;
        sum+=u;
    }
    int sumfinal = 0;
    printf("\n Sum is %d",sum);
    for(i=n-1;i>=0;i--){
        sum-=burst_time[i];
        printf("\nWaiting Time for P[%d] =  %d",i,sum);
        sumfinal+=sum;
    }
    printf("\n Total Waiting Time is %d",sumfinal);
    printf("\n Average Waiting Time is %d",(sumfinal/n));
}
void fcfsturn(int *arr,int arrtime,int n)
{
    printf("\n Waiting Time Calculation Here ");
    int i,j,sumfinal = 0,k=0;int sum = 0;
    while(k<n)
    {
        sum+=arr[k];
        sumfinal+=sum;
        printf("\n Sum is %d",sumfinal);
        ++k;
    }
    printf("\n Total Turn Around Time is %d",sumfinal);
    printf("\n Average Turn Around Time is %d",sumfinal/n);
}
int main()
{
    int n;
    int *arr;
    printf("Enter the Number of Elements  :");
    scanf("%d",&n);
    arr = (int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        printf("Enter the P[%d] Data -> ",i);
        scanf("%d",&arr[i]);
    }
    fcfswait(arr,0,n);
    fcfsturn(arr,0,n);
    return 0;
}