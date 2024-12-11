#include <stdio.h>
#include <string.h>

int main() {
    char line[100];  // Buffer for input line
    char *token;
    char *input;  // Temporary pointer for strtok handling

    // Read input from stdin, line by line
    while (fgets(line, sizeof(line), stdin)) {
        // Make a modifiable copy of the input line
        input = line;

        // Remove newline character at the end of the line if present
        // line[strcspn(line, "\n")] = 0;

        // Use strsep() to split the line into tokens
        while ((token = strsep(&input, " \t")) != NULL) {
            if (*token == '\0') continue;  // Skip empty tokens
            printf("%s\n", token);  // Print each token on a new line
        }
    }

    return 0;
}