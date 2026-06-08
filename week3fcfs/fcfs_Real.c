#include <stdio.h>

#define MAX 100

void fcfs(int n, int at[], int bt[])
{
    int wt[MAX], tat[MAX], ct[MAX], rt[MAX];
    int time = 0;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++)
    {
        // CPU idle if process has not arrived yet
        if (time < at[i])
        {
            time = at[i];
        }

        // Response Time = Start Time - Arrival Time
        rt[i] = time - at[i];

        // Waiting Time = Start Time - Arrival Time
        wt[i] = time - at[i];

        // Execute process
        time += bt[i];

        // Completion Time
        ct[i] = time;

        // Turnaround Time
        tat[i] = ct[i] - at[i];

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\n===== FCFS Scheduling =====\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i],
               rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Response Time = %.2f\n", total_rt / n);
}

int main()
{
    int n;
    int at[MAX], bt[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i + 1);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);
    }

    fcfs(n, at, bt);

    return 0;
}
