#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m; // n = processes, m = resources

    int allocation[MAX][MAX], request[MAX][MAX];
    int available[MAX];
    int work[MAX];
    bool finish[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Request Matrix
    printf("Enter Request Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Resources
    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Step 1: Initialize
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    // Step 2: Detection algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    // Work = Work + Allocation
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                }
            }
        }
    }

    // Step 3: Check for deadlock
    bool deadlock = false;

    printf("\nDeadlocked Processes: ");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock) {
        printf("None");
        printf("\nSystem is NOT in deadlock.\n");
    } else {
        printf("\nSystem is in DEADLOCK.\n");
    }

    return 0;
}
