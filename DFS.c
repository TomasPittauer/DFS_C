#include "DFS.h"
#include "random.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct grid {
    int **grid;
    bool **visited;
    int **path;
    int step;
    int path_count;
    int w;
    int h;
};

struct grid *create_grid(int w, int h) {
    struct grid *temp = malloc(sizeof(struct grid));
    temp->w = w;
    temp->h = h;
    temp->step = 0;
    temp->path_count = 1;
    temp->path = malloc(1 * sizeof(int *));
    if(temp->path == NULL){
        exit(1);
    }
    temp->path[0] = malloc(2 * sizeof(int));
    if(temp->path[0] == NULL){
        exit(1);
    }

    temp->grid = malloc(w * sizeof(int *));
    for (int i = 0; i < w; i++) {
        temp->grid[i] = calloc(h, sizeof(int));
    }
    temp->visited = malloc(w * sizeof(bool *));
    for (int i = 0; i < w; i++) {
        temp->visited[i] = calloc(h, sizeof(bool));
    }
    return temp;
}

void free_grid(struct grid *grid) {
    for (int i = 0; i < grid->w; i++) {
        free(grid->visited[i]);
        free(grid->grid[i]);
    }
    free(grid->grid);
    free(grid->visited);
    free(grid);
}

void print_grid(struct grid *grid) {
    for (int i = 0; i < grid->w; i++) {
        for (int j = 0; j < grid->h; j++) {
            printf("%d ", grid->grid[i][j]);
        }
        printf("\n");
    }
}

void print_visited(struct grid *grid) {
    for (int i = 0; i < grid->w; i++) {
        for (int j = 0; j < grid->h; j++) {
            printf("%d ", grid->visited[i][j]);
        }
        printf("\n");
    }
}

void add_step(struct grid *grid, int x, int y) {
    int **temp = realloc(grid->path, (grid->step + 1) * sizeof(int *));
    if (temp == NULL) {
        fprintf(stderr, "Error reallocating memory for path\n");
        exit(1);
    }
    grid->path = temp;
    grid->path[grid->step] = malloc(2 * sizeof(int));
    if (grid->path[grid->step] == NULL) {
        fprintf(stderr, "Error allocating memory for path step\n");
        exit(1);
    }
    grid->path[grid->step][0] = x;
    grid->path[grid->step][1] = y;
    grid->step++;
}

void trace_step_back(struct grid *grid) {
    if (grid->step > 0) {
        // Decrement step first, then free the memory for the previous path
        grid->step--;
        free(grid->path[grid->step]);
    } else {
        fprintf(stderr, "Error: Attempted to backtrack when no steps remain\n");
        exit(1);  // Prevent infinite loops by terminating the program
    }
    grid->path_count++;
}



void next_step(struct grid *grid) {
    int x = grid->path[grid->step - 1][0];
    int y = grid->path[grid->step - 1][1];
    int directions = 0;
    int *possible_directions = malloc(4 * sizeof(int));

    // 0 nahoru, 1 doprava, 2 dole, 3 doleva
    if (y > 0 && grid->visited[x][y - 1] == false) {
        possible_directions[directions++] = 0;
    }
    if (x < grid->w - 1 && grid->visited[x + 1][y] == false) {
        possible_directions[directions++] = 1;
    }
    if (y < grid->h - 1 && grid->visited[x][y + 1] == false) {
        possible_directions[directions++] = 2;
    }
    if (x > 0 && grid->visited[x - 1][y] == false) {
        possible_directions[directions++] = 3;
    }

    if (directions > 0) {
        switch (possible_directions[random(0,directions)]) {
            case 0:
                add_step(grid, x, y - 1);
                grid->visited[x][y - 1] = true;
                grid->grid[x][y - 1] = grid->path_count;
                break;
            case 1:
                add_step(grid, x + 1, y);
                grid->visited[x + 1][y] = true;
                grid->grid[x + 1][y] = grid->path_count;
                break;
            case 2:
                add_step(grid, x, y + 1);
                grid->visited[x][y + 1] = true;
                grid->grid[x][y + 1] = grid->path_count;

                break;
            case 3:
                add_step(grid, x - 1, y);
                grid->visited[x - 1][y] = true;
                grid->grid[x - 1][y] = grid->path_count;
                break;
            default: next_step(grid);
                break;
        }
    } else {
        trace_step_back(grid);
    }

    free(possible_directions);
}

void dfs(struct grid *grid) {
    bool traced = false;
    add_step(grid, 0, 0);
    grid->visited[0][0] = true;
    grid->grid[0][0] = grid->path_count;

    print_grid(grid);

    while (!traced) {
        next_step(grid);
        printf("\n");
        print_grid(grid);
        printf("%d",grid->path_count);

        int unvisited = 0;
        for (int i = 0; i < grid->w; i++) {
            for (int j = 0; j < grid->h; j++) {
                if (!grid->visited[i][j]) {
                    unvisited++;
                    break;
                }
            }
            if (unvisited > 0) break;
        }
        if (unvisited == 0){
            traced = true;
            printf("q\n");
            print_grid(grid);
        }
    }
}