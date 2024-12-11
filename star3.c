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

    printf("Number of good reports: %d\n", good);
    printf("Total failed cases: %d\n", failed_cases);
    printf("Total rows: %d\n", total_rows);

    fclose(file);
    return EXIT_SUCCESS;
}
#endif
