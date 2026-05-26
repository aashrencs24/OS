#include <stdio.h>
#define MAX 50
// Function to check if page is present
int isPresent(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}
// FIFO Page Replacement
void FIFO(int pages[], int n, int capacity)
{
    int frames[MAX], index = 0, faults = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, capacity, pages[i]))
        {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", faults);
}
// LRU Page Replacement
void LRU(int pages[], int n, int capacity)
{
    int frames[MAX], recent[MAX], faults = 0;

    // Initialize frames and recent arrays
    for (int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        // Check if page already exists
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                recent[j] = i; // update recent use
                break;
            }
        }

        // If page not found
        if (!found)
        {
            int empty = -1;

            // First check for empty frame
            for (int j = 0; j < capacity; j++)
            {
                if (frames[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            // If empty frame exists
            if (empty != -1)
            {
                frames[empty] = pages[i];
                recent[empty] = i;
            }
            else
            {
                // Find Least Recently Used page
                int lru = 0;

                for (int j = 1; j < capacity; j++)
                {
                    if (recent[j] < recent[lru])
                        lru = j;
                }

                frames[lru] = pages[i];
                recent[lru] = i;
            }

            faults++;
        }

        // Display frames
        printf("Page %d -> ", pages[i]);

        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}
void Optimal(int pages[], int n, int capacity)
{
    int frames[MAX], faults = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, capacity, pages[i]))
        {
            int replace = -1, farthest = i + 1;

            for (int j = 0; j < capacity; j++)
            {
                int k;

                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        if (k > farthest)
                        {
                            farthest = k;
                            replace = j;
                        }
                        break;
                    }
                }

                if (k == n)
                {
                    replace = j;
                    break;
                }
            }

            if (replace == -1)
                replace = 0;

            frames[replace] = pages[i];
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

// Main Function
int main()
{
    int pages[MAX], n, capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}
