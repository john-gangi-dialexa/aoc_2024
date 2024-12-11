#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool is_safe_row(int *row, int length) {
    fprintf(stdout, "Row: %d %d %d %d %d\n", row[0], row[1], row[2], row[3], row[4]);
    for (int i = 1; i < length; i++) {
        int diff = row[i] - row[i - 1];
        if (abs(diff) > 3 || diff == 0) {
            printf("Row is not safe \n");
            return false;
        }
    }

    bool increasing = true, decreasing = true;
    for (int i = 1; i < length; i++) {
        if (row[i] > row[i - 1]) {
            decreasing = false;
        } else if (row[i] < row[i - 1]) {
            increasing = false;
        }
    }
    bool result = (increasing && !decreasing) || (!increasing && decreasing);
    printf("Row is %s\n", result ? "safe" : "not safe");
    return result;
}

#ifndef TESTING
int main() {
    int good = 0;

    FILE *file = fopen("inputs/unusual_data", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[512];
    int total_rows = 0;
    int failed_cases = 0;
    int row_index = 0;
    int failed_indices[1000]; // Assuming a maximum of 512 rows for simplicity

    while (fgets(line, sizeof(line), file)) {
        total_rows++;

        // Count the number of integers in the line
        int count = 0;
        char *ptr = line;
        while (*ptr) {
            if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
                count++;
                while (isdigit(*ptr) || *ptr == '-') ptr++;
            } else {
                ptr++;
            }
        }

        // Allocate memory for the row
        int *row = (int *)malloc(count * sizeof(int));
        if (row == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        // Parse the integers into the row array
        ptr = line;
        for (int i = 0; i < count; i++) {
            sscanf(ptr, "%d", &row[i]);
            while (isdigit(*ptr) || *ptr == '-') ptr++;
            while (*ptr && !isdigit(*ptr) && *ptr != '-') ptr++;
        }

        printf("Processing row %d\n", row_index);
        if (is_safe_row(row, count)) {
            good++;
        } else {
            failed_cases++;
            failed_indices[failed_cases - 1] = row_index; // Store the index of the failed row
        }
        row_index++;

        // Free the allocated memory
        free(row);
    }

    // Print the indices of the failed rows
    printf("Indices of failed rows: ");
    for (int i = 0; i < failed_cases; i++) {
        printf("%d ", failed_indices[i]);
    }
    printf("\n");

    // Reopen the file to read the lines again
    fclose(file);
    file = fopen("inputs/unusual_data", "r");
    if (file == NULL) {
        perror("Error reopening file");
        return EXIT_FAILURE;
    }

    int fixer_upper_rows = 0;
    for (int i = 0; i < failed_cases; i++) {
        int target_index = failed_indices[i];
        int current_index = 0;
        rewind(file); // Reset file pointer to the beginning
        while (fgets(line, sizeof(line), file)) {
            if (current_index == target_index) {
                // Count the number of integers in the line
                int count = 0;
                char *ptr = line;
                while (*ptr) {
                    if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
                        count++;
                        while (isdigit(*ptr) || *ptr == '-') ptr++;
                    } else {
                        ptr++;
                    }
                }

                // Allocate memory for the row
                int *row = (int *)malloc(count * sizeof(int));
                if (row == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return EXIT_FAILURE;
                }

                // Parse the integers into the row array
                ptr = line;
                for (int j = 0; j < count; j++) {
                    sscanf(ptr, "%d", &row[j]);
                    while (isdigit(*ptr) || *ptr == '-') ptr++;
                    while (*ptr && !isdigit(*ptr) && *ptr != '-') ptr++;
                }

                // Iterate through the possible permutations with one element removed
                for (int j = 0; j < count; j++) {
                    int *new_row = (int *)malloc((count - 1) * sizeof(int));
                    if (new_row == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        free(row);
                        return EXIT_FAILURE;
                    }

                    // Create the new row with one element removed
                    for (int k = 0, l = 0; k < count; k++) {
                        if (k != j) {
                            new_row[l++] = row[k];
                        }
                    }

                    // Check if the new row is safe
                    if (is_safe_row(new_row, count - 1)) {
                        fixer_upper_rows++;
                        free(new_row);
                        break;
                    }
                    free(new_row);
                }

                free(row);
                break;
            }
            current_index++;
        }
    }
    printf("Number of fixer upper rows: %d\n", fixer_upper_rows);
    fclose(file);

    printf("Number of good reports: %d\n", good);

    int fixersplusgood = fixer_upper_rows + good;
    printf("Number of fixer upper rows plus good reports: %d\n", fixersplusgood);
    printf("Total failed cases: %d\n", failed_cases);
    printf("Total rows: %d\n", total_rows);

    fclose(file);
    return EXIT_SUCCESS;
}
#endif
