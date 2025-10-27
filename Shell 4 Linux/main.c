#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINES 80
#define MAX_HISTORY 100

void message(int code);

// Message handler
void message(int code) {
    switch (code) {
        case 0:
            printf("No command in history!\n");
            break;
        case 1:
            printf("Such a command is NOT in history!\n");
            break;
        default:
            printf("Invalid code!\n");
            break;
    }
}

int main() {
    char input[MAX_LINES];
    char *args[MAX_LINES / 2 + 1];
    int flag = 1;
    int wait_status;
    char history[MAX_HISTORY][MAX_LINES];
    int historyCount = 0;

    while (flag) {
        printf("CSCI3120>");
        fflush(stdout);

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        // Check for history command
        if (strcmp(input, "history") == 0) {
            if (historyCount == 0) {
                message(0);
                continue;
            }

            for (int j = 0; j < historyCount; j++) {
                printf("%d %s\n", j + 1, history[j]);
            }
            continue;
        }
        
        /**
         * !! - execute last command
         * !n - execute nth command
         */
        if (strcmp(input, "!!") == 0) {
            if (historyCount == 0) {
                message(0);
                continue;
            }

            strcpy(input, history[historyCount - 1]);
            printf("%s\n", input);
        }
        else if (input[0] == '!' && input[1] >= '0' && input[1] <= '9') {
            int cmdNum = atoi(&input[1]);

            if (historyCount == 0) {
                message(0);
                continue;
            }
            else if (cmdNum <= 0 || cmdNum > historyCount) {
                message(1);
                continue;
            }

            strcpy(input, history[cmdNum - 1]);
            printf("%s\n", input);
        }

        // Check for exit command
        if (strcmp(input, "exit") == 0) {
            flag = 0;
            continue;
        }

        // Add command to history before executing
        if (historyCount < MAX_HISTORY) {
            strcpy(history[historyCount], input);
            historyCount++;
        }

        // Parse input into arguments
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_LINES / 2) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        }
        else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                // exec failed - invalid command
                message(2);
                exit(1);
            }
        }
        else {
            // Parent process
            wait(&wait_status);
        }
    }

    return 0;
}