#include <stdio.h>
#include <unistd.h> 
#include <errno.h>  

int main(int argc, char *argv[]) {
    // Check if at least one argument is provided
    if (argc < 2) {
        printf("Usage: %s <program> [args...]\n", argv[0]);
        return 1;
    }

    // Extract the program name and arguments
    char *program = argv[1];  // The program to execute
    char **program_args = &argv[1];  // Arguments to the program, including the program name

    // Replace the current process with the new program
    if (execv(program, program_args) == -1) {
        // If execv returns, it means an error occurred
        perror("execv failed");
        return 1;
    }

    return 0;  // This will never be reached if execv is successful
}