#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "lib.c"


/*
traveling salesman 
n - number of cities (make sure get cities matches this)
*/
int main(int argc, char* argv[]) { 
    if (argc < 2) {
        printf("Usage: %s <num1>,<num2> [<num3>,<num4> ...]\n", argv[0]);
        return 1;
    }

    int n = argc-1; // -1 to account for program name as argument

    clock_t start, end;
    city cities[n];
    _get_cities(argc, argv, cities);
    double rdistance = 0.0;
    int rpath[n];
    start = clock();
    tsp(&rdistance, rpath, cities, n);
    end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double distances[n*n];
    get_distances(distances, cities, n);

    print_output(rdistance, cities, rpath, n, cpu_time_used);
    return 0; 
}


