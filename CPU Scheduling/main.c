#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50
#define TIME_QUANTUM 4
void FCFS(char tasks[][3], int arrival[], int burst[], int count);
void RR(char tasks[][3], int arrival[], int burst[], int count);

int main() {
    char tasks[MAX][3];
    int arrival[MAX];
    int burst[MAX];
    char buffer[100];
    int count = 0;

    FILE *file;
    file = fopen("TaskSpec.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read tasks, arrival times, and burst times from file
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%[^,],%d,%d", tasks[count], &arrival[count], &burst[count]);
        count++;
    }

    FCFS(tasks, arrival, burst, count);
    RR(tasks, arrival, burst, count);

    fclose(file);
    return 0;
}

void FCFS(char tasks[][3], int arrival[], int burst[], int count) {
    printf("FCFS:\n");
    int holder = 0;
    int total = 0;
    int fcfsArrival[MAX];
    int fcfsBurst[MAX];

    memcpy(fcfsArrival, arrival, sizeof(int) * count);
    memcpy(fcfsBurst, burst, sizeof(int) * count);

    for (int i = 1; i < count; i++) {
        fcfsArrival[i] = fcfsBurst[i - 1];
        fcfsBurst[i] += fcfsBurst[i - 1];
    }

    for (int i = 0; i < count; i++) {
        printf("%s\t", tasks[i]);
        printf("%d\t", fcfsArrival[i]);
        printf("%d\n", fcfsBurst[i]);
    }

    for (int i = 0; i < count; i++) {
        holder = fcfsArrival[i] - i;
        total += holder;
        printf("Waiting Time %s: %d\n", tasks[i], holder);
    }

    float avgAnswer = (float)total / count;
    printf("Average Waiting Time: %.2f\n", avgAnswer);
}

void RR(char tasks[][3], int arrival[], int burst[], int count) {
    printf("\nRR: \n");

    int remBurst[MAX];
    int waitTime[MAX] = {0};
    int time = 0;
    int completed = 0;
    int totalWait = 0;
    
    // Queue for RR
    int queue[MAX];
    int front = 0, rear = 0;
    bool inQueue[MAX] = {false};

    memcpy(remBurst, burst, sizeof(int) * count);

    // Push processes that arrive at time 0
    for(int i = 0; i < count; i++) {
        if (arrival[i] <= time && remBurst[i] > 0) {
            queue[rear % MAX] = i;
            rear++;
            inQueue[i] = true;
        }
    }

    while (completed < count) {
         // Queue empty
        if (front == rear) {
            time++;
            
            // Check for new arrivals at this new time
            for(int i = 0; i < count; i++) {
                if (arrival[i] <= time && remBurst[i] > 0 && !inQueue[i]) {
                    queue[rear % MAX] = i;
                    rear++;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front % MAX];
        front++;
        inQueue[idx] = false;

        int execTime = (remBurst[idx] > TIME_QUANTUM) ? TIME_QUANTUM : remBurst[idx];
        
        // Execute
        time += execTime;
        remBurst[idx] -= execTime;

        // Add arrivals that happened during execution
        for(int i = 0; i < count; i++) {
            if (arrival[i] <= time && remBurst[i] > 0 && !inQueue[i] && i != idx) {
                queue[rear % MAX] = i;
                rear++;
                inQueue[i] = true;
            }
        }

        // Re-queue if not finished
        if (remBurst[idx] > 0) {
            queue[rear % MAX] = idx;
            rear++;
            inQueue[idx] = true;
        }
        else {
            completed++;
            waitTime[idx] = time - arrival[idx] - burst[idx];
        }

        printf("%s\t", tasks[idx]);
        printf("%d\t", time - execTime);
        printf("%d\n", time);
    }
    

    for (int i = 0; i < count; i++) {
        totalWait += waitTime[i];
        printf("Waiting Time %s: %d\n", tasks[i], waitTime[i]);
    }

    float avgWait = (float)totalWait / count;
    printf("Average Waiting Time: %.2f\n", avgWait);
}