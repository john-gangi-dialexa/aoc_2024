#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 141
#define COLS 141

char grid[ROWS][COLS];

void load_grid_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ROWS; i++) {
        if (fgets(grid[i], COLS + 1, file) == NULL) {
            break;
        }
        // Remove newline character if present
        grid[i][strcspn(grid[i], "\n")] = '\0';
        // Print each row for observability
        printf("Loaded row %d: %s\n", i, grid[i]);
    }
    fclose(file);
}

int find_xmas_in_direction(int row, int col, int row_dir, int col_dir) {
    char *target = "XMAS";
    int len = strlen(target);
    for (int i = 0; i < len; i++) {
        int r = row + i * row_dir;
        int c = col + i * col_dir;
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS || grid[r][c] != target[i]) {
            return 0;
        }
    }
    return 1;
}

int find_xmas() {
    int count = 0;
    int directions[8][2] = {
        {0, 1}, {1, 0}, {1, 1}, {1, -1},
        {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}
    };
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            for (int d = 0; d < 8; d++) {
                if (find_xmas_in_direction(row, col, directions[d][0], directions[d][1])) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    load_grid_from_file("inputs/xmas");
    int count = find_xmas();
    printf("Found %d instances of 'XMAS'\n", count);
    return 0;
}