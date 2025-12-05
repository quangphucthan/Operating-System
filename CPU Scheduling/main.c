#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define TIME_QUANTUM 4
void FCFS(char tasks[][3], int arrival[], int burst[], int count);

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

    fclose(file);
    return 0;
}

void FCFS(char tasks[][3], int arrival[], int burst[], int count) {
    printf("FCFS:\n");
    int holder = 0;
    int total = 0;

    for (int i = 1; i < count; i++) {
        arrival[i] = burst[i - 1];
        burst[i] += burst[i - 1];
    }

    for (int i = 0; i < count; i++) {
        printf("%s\t", tasks[i]);
        printf("%d\t", arrival[i]);
        printf("%d\n", burst[i]);
    }

    for (int i = 0; i < count; i++) {
        holder = arrival[i] - i;
        total += holder;
        printf("Waiting Time %s: %d\n", tasks[i], holder);
    }

    float avgAnswer = (float)total / count;
    printf("Average Waiting Time: %2f\n", avgAnswer);
}