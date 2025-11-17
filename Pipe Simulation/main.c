#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINES 80

int main() {
    char input[MAX_LINES];
    char *args[MAX_LINES / 2 + 1];
    int flag = 1;
    int wait_status;
    int fd[2];

    while (flag) {
        printf("Please Enter Your Sentence: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        if (strcmp(input, "exit") == 0) {
            flag = 0;
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        }
        else if (pid == 0) {
            // Child process
        }
        else {
            wait(&wait_status);
        }

    }
}