#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    file = fopen("TaskSpec.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fclose(file);
}