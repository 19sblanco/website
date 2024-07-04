#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "lib.c"


/*
tsp_C:
  tsp written in python
    cities: 12
    time: 808.4938039779663

  tsp written in C (on heap)
    cities: 12
    time: 23.480295
    cities: 13
    time: 265.090176

  tsp written in C (on stack)
    cities: 12
    time: 13.547940
    cities:13
    time: 221.827008
*/




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
    start = clock();
    city cities[n];
    _get_cities(argc, argv, cities);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);
    end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double distances[n*n];
    get_distances(distances, cities, n);

    printf("=== output ===\n");
    printf("distance: %f\npath: ", rdistance);
    print_cities(cities, rpath, n);
    print_distances(distances, n);
    printf("Time used: %f seconds\n", cpu_time_used);
    return 0; 
}


