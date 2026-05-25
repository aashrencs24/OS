#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int bt;   // Burst Time (C)
    int dl;   // Deadline (EDF)
    int pr;   // Period (RMS)
    int ct;
    int wt;
    int tat;
} Process;

Process p[MAX];
int n;

// ----------- UTILIZATION CALCULATION -----------
float calculate_utilization() {
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)p[i].bt / p[i].pr;
    }
    return U;
}

// ----------- GANTT CHART FUNCTION -----------
void print_gantt(Process temp[]) {
    int time = 0;

    printf("\nGantt Chart:\n|");

    // Print process order
    for (int i = 0; i < n; i++) {
        printf(" P%d |", temp[i].id);
    }

    printf("\n0");

    // Print time markers
    for (int i = 0; i < n; i++) {
        time += temp[i].bt;
        printf("   %d", time);
    }
    printf("\n");
}

// ---------------- EDF ----------------
void edf() {
    Process temp[MAX];

    for (int i = 0; i < n; i++)
        temp[i] = p[i];

    // Sort by Deadline
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i].dl > temp[j].dl) {
                Process t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++) {
        time += temp[i].bt;
        temp[i].ct = time;
        temp[i].tat = temp[i].ct;
        temp[i].wt = temp[i].tat - temp[i].bt;
    }

    float U = calculate_utilization();

    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("Utilization (U) = %.3f\n", U);

    if (U <= 1)
        printf("Schedulable (U <= 1)\n");
    else
        printf("Not Schedulable (U > 1)\n");

    printf("\nID\tBT\tDeadline\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               temp[i].id, temp[i].bt, temp[i].dl,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }

    // Gantt Chart
    print_gantt(temp);
}

// ---------------- RMS ----------------
void rms() {
    Process temp[MAX];

    for (int i = 0; i < n; i++)
        temp[i] = p[i];

    // Sort by Period
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i].pr > temp[j].pr) {
                Process t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++) {
        time += temp[i].bt;
        temp[i].ct = time;
        temp[i].tat = temp[i].ct;
        temp[i].wt = temp[i].tat - temp[i].bt;
    }

    float U = calculate_utilization();

    float bound = n * (pow(2, (float)1/n) - 1);

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("Utilization (U) = %.3f\n", U);
    printf("RMS Bound = %.3f\n", bound);

    if (U <= bound)
        printf("Schedulable (U <= Bound)\n");
    else
        printf("Not Schedulable (U > Bound)\n");

    printf("\nID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               temp[i].id, temp[i].bt, temp[i].pr,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }

    // Gantt Chart
    print_gantt(temp);
}

// ---------------- MAIN ----------------
int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].dl);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].pr);
    }

    edf();
    rms();

    return 0;
}
