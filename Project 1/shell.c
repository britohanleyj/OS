#include <stdio.h>
#include <unistd.h>  
#include <string.h> 
#include <stdlib.h>  
#include <sys/wait.h>  

int main() {
    char line[100];  // buffer for input line
    char *argv[10];  // the array to store arguments | limites to 10
    char *token;
    int status;     

    printf("MiniShell$> "); // initial print statement $

    while (fgets(line, sizeof(line), stdin) != NULL) {
        // remove new lines \n 
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            printf("MiniShell$> ");
            continue;
        }

        // Tokenize input into argv[]
        int argc = 0;
        token = strtok(line, " \t");
        while (token != NULL && argc < 9) {
            argv[argc++] = token;
            token = strtok(NULL, " \t");
        }
        argv[argc] = NULL;  // Null-terminate

        pid_t pid = fork();
        if (pid == 0) {
            // execvp
            if (execvp(argv[0], argv) == -1) {
                perror("execvp");
                exit(1);  // Exit if execvp fails
            }
        } else if (pid > 0) {
            // Parent process
            wait(&status);  // wait for the child to finish
        } else {
            // for if it fails
            perror("fork");
        }

        
        printf("MiniShell$> "); // Print the prompt again for next command
    }

    return 0;
}