#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_WORDS 80

int main() {
    char input[MAX_WORDS];
    int flag = 1;
    int wait_status;
    int fd1[2];
    int fd2[2];

    while (flag) {
        printf("Please Enter Your Sentence: ");
        fflush(stdout);

        // Take user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        // Exit the program
        if (strcmp(input, "exit") == 0) {
            flag = 0;
            continue;
        }

        if (pipe(fd1) == -1)  {
            perror("pipe");
            exit(1);
        }

        if (pipe(fd2) == -1) {
            perror("pipe");
            exit(1);
        }

        printf("The String from Parent to Child is: %s\n", input);

        // Create a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        else if (pid > 0) {
            // Parent process
            char holder[MAX_WORDS];
            close(fd2[1]);
            close(fd1[0]);

            write(fd1[1], input, sizeof(input));

            wait(&wait_status);

            read(fd2[0], holder, sizeof(holder));
            printf("The String from Child to Parent is: %s\n", holder);

            close(fd2[0]);
            close(fd1[1]);
        }
        else {
            // Child process
            close(fd1[1]);
            close(fd2[0]);
            
            char holder[MAX_WORDS];
            read(fd1[0], holder, sizeof(holder));

            int length = strlen(holder);

            for (int i = 0; i < length; i++) {
                char a = holder[i];
                if (a == ' ') {
                    continue;  // Skip space
                }
                a ^= 32;
                holder[i] = a;
            }

            write(fd2[1], holder, sizeof(holder));

            close(fd1[0]);
            close(fd2[1]);

            exit(0);
        }
    }

    return 0;
}