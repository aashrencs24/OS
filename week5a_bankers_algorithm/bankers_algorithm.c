#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m; // n = processes, m = resources

    int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX];
    int work[MAX];
    bool finish[MAX];
    int safeSequence[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("Enter Maximum Demand Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Step 1: Initialize
    for(int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for(int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int count = 0;

    // Step 2 & 3: Find safe sequence
    while(count < n) {
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(finish[i] == false) {
                bool canExecute = true;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if(canExecute) {
                    // Work = Work + Allocation[i]
                    for(int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // Step 4: If no process found
        if(!found) {
            break;
        }
    }

    // Check safe state
    if(count == n) {
        printf("\nSystem is in a safe state.\n");
        printf("Safe sequence is: ");
        for(int i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if(i != n - 1)
                printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state (Deadlock may occur).\n");
    }

    return 0;
}
