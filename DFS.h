#ifndef DFS_H
#define DFS_H

struct grid;

void dfs(struct grid * grid);
struct grid * create_grid(int w, int h);
void free_grid(struct grid * grid);
void print_grid(struct grid * grid);
void print_visited(struct grid * grid);
void add_step(struct grid * grid, int x, int y);
void next_step(struct grid * grid);
void trace_step_back(struct grid * grid);


#endif //DFS_H