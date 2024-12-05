
#include "stdlib.h"
#include "time.h"
#include "random.h"


#include <stdlib.h>    // For srand() and rand()
#include <sys/time.h>  // For struct timeval and gettimeofday()

void generateSRand() {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srand(tm.tv_sec + tm.tv_usec * 1000000ul);
}

int random(int min, int max) {
    int result = rand() % (max - min + 1) + min;
    return result;
}