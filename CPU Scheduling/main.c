#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50
#define TIME_QUANTUM 4
void FCFS(char tasks[][3], int arrival[], int burst[], int count);
void RR(char tasks[][3], int arrival[], int burst[], int count);
FILE *fWrite;

int main() {
    char tasks[MAX][3];
    int arrival[MAX];
    int burst[MAX];
    char buffer[100];
    int count = 0;

    FILE *file;
    file = fopen("TaskSpec.txt", "r");

    // Open output file
    fWrite = fopen("Output.txt", "w");

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
    fprintf(fWrite, "FCFS:\n");
    int holder = 0;
    int total = 0;
    int fcfsStart[MAX];
    int fcfsEnd[MAX];
    
    // Copy original arrays -> calculation arrays
    memcpy(fcfsStart, arrival, sizeof(int) * count);
    memcpy(fcfsEnd, burst, sizeof(int) * count);

    // Calculate waiting times and turnaround times
    for (int i = 1; i < count; i++) {
        fcfsStart[i] = fcfsEnd[i - 1];
        fcfsEnd[i] += fcfsEnd[i - 1];
    }

    for (int i = 0; i < count; i++) {
        fprintf(fWrite, "%s\t", tasks[i]);
        fprintf(fWrite, "%d\t", fcfsStart[i]);
        fprintf(fWrite, "%d\n", fcfsEnd[i]);
    }

    // Calculate total waiting time
    for (int i = 0; i < count; i++) {
        holder = fcfsStart[i] - i;
        total += holder;
        fprintf(fWrite, "Waiting Time %s: %d\n", tasks[i], holder);
    }

    float avgAnswer = (float)total / count;
    fprintf(fWrite, "Average Waiting Time: %.2f\n", avgAnswer);
}

void RR(char tasks[][3], int arrival[], int burst[], int count) {
    fprintf(fWrite, "\nRR: \n");

    int remBurst[MAX];
    int waitTime[MAX] = {0};
    int time = 0;
    int completed = 0;
    int totalWait = 0;
    
    // Queue for RR
    int queue[MAX];
    int front = 0, rear = 0;
    bool inQueue[MAX] = {false};

    // Create remaining burst time array based on original burst times
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

        // Dequeue for execution
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

        fprintf(fWrite, "%s\t", tasks[idx]);
        fprintf(fWrite, "%d\t", time - execTime);
        fprintf(fWrite, "%d\n", time);
    }
    

    // Calculate total waiting time
    for (int i = 0; i < count; i++) {
        totalWait += waitTime[i];
        fprintf(fWrite, "Waiting Time %s: %d\n", tasks[i], waitTime[i]);
    }

    float avgWait = (float)totalWait / count;
    fprintf(fWrite, "Average Waiting Time: %.2f\n", avgWait);
}