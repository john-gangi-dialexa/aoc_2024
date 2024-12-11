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
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);
    data[fsize] = '\0';

    regex_t regex;
    regmatch_t matches[5];
    regcomp(&regex, "mul\\(([0-9]+),([0-9]+)\\)|(do\\(\\))|(don't\\(\\))", REG_EXTENDED);

    int total1 = 0, total2 = 0;
    int enabled = 1;
    char *cursor = data;

    while (regexec(&regex, cursor, 5, matches, 0) == 0) {
        if (matches[3].rm_so != -1 || matches[4].rm_so != -1) {
            enabled = (matches[3].rm_so != -1);
        } else {
            int a = atoi(cursor + matches[1].rm_so);
            int b = atoi(cursor + matches[2].rm_so);
            int x = a * b;
            total1 += x;
            total2 += x * enabled;
        }
        cursor += matches[0].rm_eo;
    }

    regfree(&regex);
    free(data);

    printf("%d %d\n", total1, total2);
    return 0;
}