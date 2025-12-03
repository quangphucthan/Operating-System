#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

void main() {
    char tasks[MAX][3];
    int arrival[MAX];
    int burst[MAX];
    int timeQuantum = 4;
    char buffer[100];
    int count = 0;

    FILE *file;
    file = fopen("TaskSpec.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%[^,],%d,%d", tasks[count], &arrival[count], &burst[count]);
        count++;
    }

    for (int j = 0; j < count; j++) {
        printf("Task: %s, Arrival: %d, Burst: %d\n", tasks[j], arrival[j], burst[j]);
    }

    fclose(file);
}