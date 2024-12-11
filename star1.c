#include <stdio.h>
#include <stdlib.h>

// function to compare integers for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    FILE *file = fopen("inputs/lists", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // create a struct to hold the data
    struct Data {
        int left;
        int right;
    };

    char line[256];
    int left_list[1000], right_list[1000];
    int left_count = 0, right_count = 0;

    while (fgets(line, sizeof(line), file)) {
        struct Data data;
        if (sscanf(line, "%d %d", &data.left, &data.right) == 2 || sscanf(line, "%d,%d", &data.left, &data.right) == 2) {
            left_list[left_count++] = data.left;
            right_list[right_count++] = data.right;
        } else {
            fprintf(stderr, "Error parsing line: %s", line);
        }
    }

    qsort(left_list, left_count, sizeof(int), compare);
    qsort(right_list, right_count, sizeof(int), compare);

    int total_distance = 0;
    for (int i = 0; i < left_count; i++) {
        int distance = abs(left_list[i] - right_list[i]);
        total_distance += distance;
        printf("Distance: %d\n", distance);
    }

    printf("Total Distance: %d\n", total_distance);

    printf("Sorted Left List: ");
    for (int i = 0; i < left_count; i++) {
        printf("%d ", left_list[i]);
    }
    printf("\n");

    printf("Sorted Right List: ");
    for (int i = 0; i < right_count; i++) {
        printf("%d ", right_list[i]);
    }
    printf("\n");

    fclose(file);
    return EXIT_SUCCESS;
}