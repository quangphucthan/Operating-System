#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_WORDS 80

int main() {
    char input[MAX_WORDS];
    char *args[MAX_WORDS / 2 + 1];
    int flag = 1;
    int wait_status;
    int fd1[2];
    int fd2[2];

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

        if (pipe(fd1) == -1)  {
            perror("pipe");
            exit(1);
        }

        if (pipe(fd2) == -1) {
            perror("pipe");
            exit(1);
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        else if (pid > 0) {
            // Parent process
            close(fd1[0]);

            write(fd1[1], input, strlen(input) + 1);
            close(fd1[1]);

            wait(&wait_status);

            close(fd2[1]);
        }
        else {
            // Child process
            close(fd1[1]);
            
            char sentString[MAX_WORDS];
            read(fd1[0], sentString, MAX_WORDS);


            for (int i = 0; i < strlen(sentString); i++) {
                char a = sentString[i];
                a ^= 32;
                sentString[i] = a;
            }

            sentString[strlen(sentString)] = '\0';

            close(fd1[0]);
            close(fd2[0]);

    }
}