#include <stdio.h>

void allocation(int block[], int m, int process[], int n, int type)
{
    int i, j, index;

    // Heading
    if(type == 1)
        printf("\n--- First Fit ---\n");
    else if(type == 2)
        printf("\n--- Best Fit ---\n");
    else
        printf("\n--- Worst Fit ---\n");

    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < n; i++)
    {
        index = -1;

        for(j = 0; j < m; j++)
        {
            if(block[j] >= process[i])
            {
                // First Fit
                if(type == 1)
                {
                    index = j;
                    break;
                }

                // Best Fit
                if(type == 2)
                {
                    if(index == -1 || block[j] < block[index])
                        index = j;
                }

                // Worst Fit
                if(type == 3)
                {
                    if(index == -1 || block[j] > block[index])
                        index = j;
                }
            }
        }

        if(index != -1)
        {
            printf("%d\t\t%d\t\t%d\n", i+1, process[i], index+1);
            block[index] -= process[i];
        }
        else
        {
            printf("%d\t\t%d\t\tNot Allocated\n", i+1, process[i]);
        }
    }
}

int main()
{
    int m, n, i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int b[m], b1[m], b2[m], b3[m];

    printf("Enter sizes of %d memory blocks:\n", m);

    for(i = 0; i < m; i++)
    {
        scanf("%d", &b[i]);
        b1[i] = b2[i] = b3[i] = b[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[n];

    printf("Enter sizes of %d processes:\n", n);

    for(i = 0; i < n; i++)
        scanf("%d", &p[i]);

    allocation(b1, m, p, n, 1); // First Fit
    allocation(b2, m, p, n, 2); // Best Fit
    allocation(b3, m, p, n, 3); // Worst Fit

    return 0;
}
