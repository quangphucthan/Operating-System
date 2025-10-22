#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINES 80

int main() {
    char *args[MAX_LINES / 2 + 1];
    int should_run = 1;
    int wait_status;

    while (should_run) {
        printf("CSCI3120>");
        fflush(stdout);

        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            exit(1);
        }
        else if (pid == 0) {
            if (fgets(args[0], sizeof(args[0]), stdin) == NULL) {
                exit(0);
            }

            
        }
        else {
            wait(&wait_status);
            printf("Child process completed\n");
        }
    }

    return 0;
}