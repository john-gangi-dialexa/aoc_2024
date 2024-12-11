#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// Declaration of the isSafe function
bool isSafe(int a, int b, int c, int d, int e);

// Test cases for the isSafe function
void test_isSafe() {
    // Add test cases here
    assert(isSafe(23, 20, 17, 14, 13) == true);
    assert(isSafe(67, 69, 70, 72, 73) == true);
    assert(isSafe(3, 6, 7, 10, 12) == true);
    assert(isSafe(3, 6, 7, 10, 14) == false);
    assert(isSafe(6, 6, 7, 10, 14) == false);
    assert(isSafe(1, 2, 3, 3, 3) == false);
    // Add more test cases based on the provided data
}

int main() {
    test_isSafe();
    printf("All tests passed!\n");
    return 0;
}