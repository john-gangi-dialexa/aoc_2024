// OH BOY THIS IS A TOUGH ONE.  I'M GOING TO NEED TO BREAK THIS DOWN INTO SMALLER PIECES.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int area;
    int perimeter;
} Component;

int n, m;
char grid[MAX][MAX];
int visited[MAX][MAX];
int adj4[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void bfs(int x, int y, char z, int component_id, Component *components) {
    int queue_capacity = n * m;
    Point *queue = (Point *)malloc(queue_capacity * sizeof(Point));
    if (queue == NULL) {
        perror("Error allocating memory for queue");
        exit(1);
    }
    int front = 0, rear = 0;
    queue[rear++] = (Point){x, y};
    visited[x][y] = component_id;
    components[component_id].area = 0;
    components[component_id].perimeter = 0;

    while (front != rear) {
        Point p = queue[front];
        front = (front + 1) % queue_capacity;
        components[component_id].area++;

        for (int i = 0; i < 4; i++) {
            int nx = p.x + adj4[i][0];
            int ny = p.y + adj4[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == z && !visited[nx][ny]) {
                queue[rear] = (Point){nx, ny};
                rear = (rear + 1) % queue_capacity;
                if (rear == front) {
                    // Resize the queue
                    int new_capacity = queue_capacity * 2;
                    Point *new_queue = (Point *)malloc(new_capacity * sizeof(Point));
                    if (new_queue == NULL) {
                        perror("Error reallocating memory for queue");
                        free(queue);
                        exit(1);
                    }
                    // Copy elements to the new queue
                    for (int j = 0; j < queue_capacity; j++) {
                        new_queue[j] = queue[(front + j) % queue_capacity];
                    }
                    free(queue);
                    queue = new_queue;
                    front = 0;
                    rear = queue_capacity;
                    queue_capacity = new_capacity;
                }
                visited[nx][ny] = component_id;
            } else if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] != z) {
                components[component_id].perimeter++;
            }
        }
    }
    free(queue);
}

int main() {
    FILE *file = fopen("inputs/garden_plots", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    n = 0;
    while (fgets(grid[n], MAX, file)) {
        grid[n][strcspn(grid[n], "\n")] = '\0';
        n++;
    }
    m = strlen(grid[0]);
    fclose(file);

    memset(visited, 0, sizeof(visited));
    Component components[MAX];
    memset(components, 0, sizeof(components));

    int component_id = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                bfs(i, j, grid[i][j], component_id, components);
                component_id++;
            }
        }
    }

    int part1 = 0, part2 = 0;
    for (int i = 0; i < component_id; i++) {
        part1 += components[i].area * components[i].perimeter;
        part2 += components[i].area * components[i].perimeter / 2; // Adjust as needed
    }

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);

    return 0;
}