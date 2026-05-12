#include <stdio.h>

#define MAX 100

typedef struct {
    int id, arrival, burst, remaining, type;
    int completion, turnaround, waiting;
} Process;

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = val;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

// Sort by arrival
void sort(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Process p[MAX];

    Queue systemQ, userQ;
    initQueue(&systemQ);
    initQueue(&userQ);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        p[i].id = i;

        printf("Enter arrival time: ");
        scanf("%d", &p[i].arrival);

        printf("Enter burst time: ");
        scanf("%d", &p[i].burst);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].remaining = p[i].burst;
    }

    sort(p, n);

    int time = 0, completed = 0, i = 0;
    int current = -1;

    int gantt[MAX * 10]; // stores process execution order
    int gindex = 0;

    while (completed < n) {

        // Add processes
        while (i < n && p[i].arrival <= time) {
            if (p[i].type == 0)
                enqueue(&systemQ, i);
            else
                enqueue(&userQ, i);
            i++;
        }

        // Preemption
        if (current != -1) {
            if (p[current].type == 1 && !isEmpty(&systemQ)) {
                enqueue(&userQ, current);
                current = -1;
            }
        }

        // Select process
        if (current == -1) {
            if (!isEmpty(&systemQ))
                current = dequeue(&systemQ);
            else if (!isEmpty(&userQ))
                current = dequeue(&userQ);
            else {
                gantt[gindex++] = -1; // idle
                time++;
                continue;
            }
        }

        // Record Gantt
        gantt[gindex++] = p[current].id;

        // Execute
        p[current].remaining--;
        time++;

        // Completion
        if (p[current].remaining == 0) {
            p[current].completion = time;
            p[current].turnaround = time - p[current].arrival;
            p[current].waiting = p[current].turnaround - p[current].burst;

            completed++;
            current = -1;
        }
    }

    // 🔷 Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gindex; i++) {
        if (gantt[i] == -1)
            printf(" Idle |");
        else
            printf(" P%d |", gantt[i]);
    }

    printf("\n0");
    for (int i = 1; i <= gindex; i++) {
        printf("    %d", i);
    }

    // 🔷 Table
    float totalWT = 0, totalTAT = 0;

    printf("\n\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               (p[i].type == 0) ? "System" : "User",
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].waiting,
               p[i].turnaround);

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
