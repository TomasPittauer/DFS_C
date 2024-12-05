#include <stdio.h>
#include "DFS.h"
#include "time.h"
#include "stdlib.h"

#include <stdio.h>

#include "DFS.h"

int main(void) {
    srand(time(NULL));
    struct grid * a = create_grid(10,10);
    dfs(a);
    return 0;
}
