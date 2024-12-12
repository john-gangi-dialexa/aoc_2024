#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 140

char grid[ROWS][ROWS+1];

int main() {
    FILE* f = fopen("inputs/xmas", "r");
    for (int i = 0; i < ROWS; i++) {
        fscanf(f, "%s ", grid[i]);
    }

    int count = 0;
    // Loop through each cell in the grid, except for the last two rows and columns
    // because we are checking for a 3x3 pattern.
    for (int i = 0; i <= ROWS-3; i++) {
        for (int j = 0; j <= ROWS-3; j++) {
            int valid = 0;
            // Check if the center of the 3x3 block is 'A'
            if (grid[i+1][j+1] == 'A') {
                valid = 1;
                // Check the diagonals of the 3x3 block
                // Top-left to bottom-right diagonal
                if (!((grid[i][j] == 'M' && grid[i+2][j+2] == 'S') || (grid[i][j] == 'S' && grid[i+2][j+2] == 'M'))) {
                    valid = 0;
                }
                // Bottom-left to top-right diagonal
                if (!((grid[i+2][j] == 'M' && grid[i][j+2] == 'S') || (grid[i+2][j] == 'S' && grid[i][j+2] == 'M'))) {
                    valid = 0;
                }
            }
            // If both diagonals are valid, increment the count
            count += valid;
        }
    }

    printf("Found %d instances of 'MAS' as a diagonal X\n", count);

}