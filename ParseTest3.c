#include <stdio.h>
#include <string.h>
#include <ctype.h>

void tensor(const char* input) {
    int is_nested = 0;
    int outer_count = 0;
    int inner_count = 0;
    int max_inner_count = 0;
    int number_count = 0;

    // Check if it's a nested statement
    if (strstr(input, "[[") != NULL) {
        is_nested = 1;
    }

    if (!is_nested) {
        // Process single-level statement
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ',') {
                number_count++;
            }
        }
        number_count++; // Add 1 for the last number

        printf("length %d\n", number_count);

        // Print individual numbers
        char* input_copy = strdup(input);  // Create a copy of input
        char* token = strtok(input_copy, "[,] ");
        while (token != NULL) {
            if (isdigit(*token)) {  // Check if token is a number
                printf("%s ", token);
            }
            token = strtok(NULL, "[,] ");
        }
        
        printf("\n");
    } else {
        // Process nested statement
        int bracket_depth = 0;
        int max_depth = 0;
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '[') {
                bracket_depth++;
                if (bracket_depth > max_depth) {
                    max_depth = bracket_depth;
                }
                if (bracket_depth == 2) {
                    outer_count++;
                    inner_count = 0;
                }
            } else if (input[i] == ']') {
                if (bracket_depth == 2) {
                    if (inner_count > max_inner_count) {
                        max_inner_count = inner_count - 1;
                    }
                }
                bracket_depth--;
            } else if (bracket_depth == 2) {
                if (isdigit(input[i]) || input[i] == '-') {
                    if (i == 0 || !isdigit(input[i-1])) {
                        inner_count++;
                    }
                }
            }
        }
        max_inner_count++; // Increment to account for the last number in each inner array

        printf("width %d\n", max_inner_count);
        printf("height %d\n", outer_count);

        // Print numbers in each innermost bracket
        bracket_depth = 0;
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '[') {
                bracket_depth++;
            } else if (input[i] == ']') {
                if (bracket_depth == max_depth) {
                    printf("\n");
                }
                bracket_depth--;
            } else if (isdigit(input[i]) || input[i] == '-') {
                if (bracket_depth == max_depth) {
                    int j = i;
                    while (isdigit(input[j]) || input[j] == '-') j++;
                    printf("%.*s ", j-i, &input[i]);
                    i = j - 1;
                }
            }
        }
    }
}

// Example usage:
int main() {
    printf("Command:\n");  
    printf("a = tensor(\"[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]\") \n");
    tensor("[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]");
    printf("b = tensor(\"[[1,2], [3,4], [5,6]]\") \n");
    tensor("[[1,2], [3,4], [5,6]]");
    printf("c = tensor(\"[[1, 2, 3], [4, 5, 6]]\") \n");
    tensor("[[1, 2, 3], [4, 5, 6]]");
    printf("d = tensor(\"[[1, 2, 3], [4, 5, 6], [7, 8, 9]]\") \n");
    tensor("[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");
    printf("e = tensor(\"[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]\")\n");
    tensor("[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]");
return 0;
}
