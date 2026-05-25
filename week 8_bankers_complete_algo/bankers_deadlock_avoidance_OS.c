#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m;
int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
int avail[MAX];

// Safety function
bool isSafe() {
    int work[MAX], finish[MAX] = {0}, count = 0;

    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < m; j++)
                    if(need[i][j] > work[j])
                        break;

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if(!found) return false;
    }
    return true;
}

int main() {
    int request[MAX], p;

    printf("Enter processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter Max:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&avail[i]);

    // Need = Max - Allocation
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    if(!isSafe()) {
        printf("System is UNSAFE\n");
        return 0;
    }

    printf("System is SAFE\n");

    // -------- Request --------
    printf("\nEnter process number: ");
    scanf("%d",&p);

    printf("Enter request:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&request[i]);

    // Check conditions
    for(int i=0;i<m;i++) {
        if(request[i] > need[p][i]) {
            printf("Exceeds need\n");
            return 0;
        }
        if(request[i] > avail[i]) {
            printf("Not available\n");
            return 0;
        }
    }

    // Pretend allocation
    for(int i=0;i<m;i++) {
        avail[i] -= request[i];
        alloc[p][i] += request[i];
        need[p][i] -= request[i];
    }

    if(isSafe())
        printf("Request GRANTED\n");
    else
        printf("Request DENIED\n");

    return 0;
}
