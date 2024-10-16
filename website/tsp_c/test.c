#include <stdio.h> 
#include <stdlib.h>

#include "lib.c"


/*
////////////////////////////////////
helper functions
*/
void get_cities(city* cities, int n) {
    city c0 = make_city(0.0, 0.0);
    city c1 = make_city(-1.0, 2.0);
    city c2 = make_city(1.0, 4.0);
    city c3 = make_city(-1.0, 8.0);
    city c4 = make_city(1.0, 12.0);
    city c5 = make_city(100.0, 12.0);
    city c6 = make_city(12.0, 12.0);
    city c7 = make_city(-13.0, -13.0);
    city c8 = make_city(-130.0, -13.0);
    city c9 = make_city(690.0, 42.0);
    city c10 = make_city(100.0, 42.0);
    city c11 = make_city(6.0, 142.0);
    cities[0] = c0;
    cities[1] = c1;
    cities[2] = c2;
    cities[3] = c3;
    cities[4] = c4;
    cities[5] = c5;
    cities[6] = c6;
    cities[7] = c7;
    cities[8] = c8;
    cities[9] = c9;
    cities[10] = c10;
    cities[11] = c11;
}

void get_cities3(city* cities, int n) {
    city c0 = make_city(0.0, 0.0);
    city c1 = make_city(-1.0, 2.0);
    city c2 = make_city(1.0, 4.0);
    cities[0] = c0;
    cities[1] = c1;
    cities[2] = c2;
}

int arr_equal(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

double rando() {
    double rand_double = (double)rand() / RAND_MAX;
    return rand_double;
}

int almost_equal(double a, double b) {
    double threshold = .1;
    if ((a > (b-threshold)) && (a < (b+threshold))) {
        return 1;
    }
    else return 0;
}

void assert_equal(int n, double expected, double got, int *rpath, int path_len) {
    printf("=== %d ===\n", n);
    if (almost_equal(expected, got)) {
        printf("success!\n");
        print_array(rpath, path_len);
        // printf("success!:\nexpected: %f\ngot: %f\n", expected, got);
    } else {
        printf("fail:\nexpected: %f\ngot: %f\n", expected, got);
    }
    printf("===  ===\n");

}
/*
helper functions
////////////////////////////////////
*/

void test_almost_equal() {
    printf("=== almost equal===\n");
    double n0 = 5.0;
    double n1 = 5.001;
    if (almost_equal(n0, n1) == 1) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }

    printf("=== ===\n");
}


/*
tsp tests
*/
void test_tsp_1() {
    int n = 3;
    double true_distance = 12.0;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(0.0, 3.0);
    cities[2] = make_city(4.0, 0.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    assert_equal(1, true_distance, rdistance, rpath, n);
}


void test_tsp_2() {
    int n = 4;
    double true_distance = 3 + 6 + pow(97, .5) + 4;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(0.0, 3.0);
    cities[2] = make_city(4.0, 0.0);
    cities[3] = make_city(0.0, 9.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    assert_equal(2, true_distance, rdistance, rpath, n);
}


void test_tsp_3() {
    int n = 4;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(-1.0, 1.0);
    cities[2] = make_city(1.0, 1.0);
    cities[3] = make_city(0.0, -1.0);
    double true_distance = pow(2, .5) + 2 + get_distance(cities[3], cities[2]) + 1;
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    assert_equal(3, true_distance, rdistance, rpath, n);
}


void test_tsp_4() {
    int n = 3;
    double true_distance = 0;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(0.0, 0.0);
    cities[2] = make_city(0.0, 0.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    assert_equal(4, true_distance, rdistance, rpath, n);
}

void test_tsp_5() {
    int n = 5;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(-1.0, 2.0);
    cities[2] = make_city(1.0, 4.0);
    cities[3] = make_city(-1.0, 8.0);
    cities[4] = make_city(1.0, 12.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    double true_distance = 24.831310;
    assert_equal(5, true_distance, rdistance, rpath, n);
}

void test_tsp_6() {
    int n = 10;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(0.0, 1.0);
    cities[2] = make_city(0.0, 2.0);
    cities[3] = make_city(0.0, 3.0);
    cities[4] = make_city(0.0, 4.0);
    cities[5] = make_city(0.0, 5.0);
    cities[6] = make_city(0.0, 6.0);
    cities[7] = make_city(0.0, 7.0);
    cities[8] = make_city(0.0, 8.0);
    cities[9] = make_city(0.0, 9.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);
    
    double true_distance = 18.0;
    assert_equal(6, true_distance, rdistance, rpath, n);
}

void test_tsp_memory() {
    printf("=== memory stress test 12 cities ===\n");
    int n = 12;
    city cities[n];
    city c0 = make_city(0.0, 0.0);
    city c1 = make_city(-1.0, 2.0);
    city c2 = make_city(1.0, 4.0);
    city c3 = make_city(-1.0, 8.0);
    city c4 = make_city(1.0, 12.0);
    city c5 = make_city(100.0, 12.0);
    city c6 = make_city(12.0, 12.0);
    city c7 = make_city(-13.0, -13.0);
    city c8 = make_city(-130.0, -13.0);
    city c9 = make_city(690.0, 42.0);
    city c10 = make_city(100.0, 42.0);
    city c11 = make_city(6.0, 142.0);
    cities[0] = c0;
    cities[1] = c1;
    cities[2] = c2;
    cities[3] = c3;
    cities[4] = c4;
    cities[5] = c5;
    cities[6] = c6;
    cities[7] = c7;
    cities[8] = c8;
    cities[9] = c9;
    cities[10] = c10;
    cities[11] = c11;
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);
    printf("sucess!\n");
    printf("=== ===\n");
}


int main() {
    test_tsp_1();
    test_tsp_2();
    test_tsp_3();
    test_tsp_4();
    test_tsp_5();
    test_tsp_6();
    // test_tsp_memory();
}
