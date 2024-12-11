#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    FILE *file = fopen("inputs/corrupt_mem", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = malloc(length + 1);
    if (!data) {
        perror("Failed to allocate memory");
        fclose(file);
        return 1;
    }
    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    printf("File content:\n%s\n", data); // Debug print

    regex_t regex;
    regmatch_t matches[3];
    const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        perror("Failed to compile regex");
        free(data);
        return 1;
    }

    char *cursor = data;
    int total = 0;
    printf("Matching pattern: %s\n", pattern);
    while (regexec(&regex, cursor, 3, matches, 0) == 0) {
        // This loop will continue to execute as long as the regex pattern matches a substring in the cursor position.
        // The regexec function returns 0 if a match is found, and non-zero if no match is found.
        // The matches array will contain the positions of the matched substrings.
        printf("Match found at position: %ld\n", cursor - data);
        if (matches[1].rm_so != -1 && matches[2].rm_so != -1) {
            // Extract and print the matched numbers
            printf("Matched strings: %.*s, %.*s\n", (int)(matches[1].rm_eo - matches[1].rm_so), cursor + matches[1].rm_so, (int)(matches[2].rm_eo - matches[2].rm_so), cursor + matches[2].rm_so);
            char num1[16], num2[16];
            snprintf(num1, sizeof(num1), "%.*s", (int)(matches[1].rm_eo - matches[1].rm_so), cursor + matches[1].rm_so);
            snprintf(num2, sizeof(num2), "%.*s", (int)(matches[2].rm_eo - matches[2].rm_so), cursor + matches[2].rm_so);
            printf("Matched numbers: %s, %s\n", num1, num2);

            // Convert to integers and print the result
            int n1 = atoi(num1);
            int n2 = atoi(num2);
            printf("Converted numbers: %d, %d\n", n1, n2);

            // Perform multiplication and add to total
            int product = n1 * n2;
            printf("Product of %d and %d: %d\n", n1, n2, product);
            total += product;
            printf("Current total: %d\n", total);
        }

        // Move cursor to the end of the current match
        cursor += matches[0].rm_eo;
        printf("Cursor moved to position: %ld\n", cursor - data);
    }

    printf("Total sum of multiplications: %d\n", total);

    regfree(&regex);
    free(data);
    return 0;
}