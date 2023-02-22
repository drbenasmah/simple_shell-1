#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

   int main(int argc, char *argv[], char *envp[]) {
    char *input;
    char *command;
    char buffer[BUFFER_SIZE];
    pid_t pid;
    int status;

    while (1) {
        // Display prompt and read input
        printf("$ ");
        input = fgets(buffer, BUFFER_SIZE, stdin);

        // Check for end of file
        if (input == NULL) {
            printf("\n");
            break;
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Fork and execute command
        pid = fork();
        if (pid == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            command = strtok(input, " ");
            if (command == NULL) {
                // Empty command
                exit(EXIT_SUCCESS);
            } else {
                // Execute command
                execve(command, &command, envp);
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

