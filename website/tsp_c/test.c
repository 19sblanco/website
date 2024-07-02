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
/*
helper functions
////////////////////////////////////
*/

void test_remove_1() {
    printf("=== removing 3 ===\n");
    int n = 5;
    int arr[n];
    _range(arr, n);
    int new_arr[n-1];
    _remove(arr, new_arr, 3, n);
    print_array(arr, n);
    print_array(new_arr, n-1);
    printf("=== ===\n");
}

void test_remove_2() {
    printf("=== removing 1,2 ===\n");
    int n = 5;
    int arr[n];
    _range(arr, n);
    int new_arr0[n-1];
    int new_arr1[n-2];
    _remove(arr, new_arr0, 1, n);
    _remove(new_arr0, new_arr1, 2, n-1);
    print_array(arr, n);
    print_array(new_arr0, n-1);
    print_array(new_arr1, n-2);
    printf("=== ===\n");
}

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

void test_add_1() {
    printf("=== adding 3 ===\n");
    int n = 5;
    int arr[n];
    _range(arr, n);


    // void _add(int* original, int* new, int item, int n) {


    /// int* newarr = arr_add(arr, n, 3);
    int new_arr[n+1];
    _add(arr, new_arr, 3, n);



    ///
    print_array(arr, n);
    print_array(new_arr, n+1);
    printf("=== ===\n");
}

void test_cp_int_array_1() {
    printf("=== copy 0 elements ===\n");
    int n = 0;
    int arr[n];
    _range(arr, n);
    int newarr[n];
    _copy(arr, newarr, n);
    print_array(arr, n);
    print_array(newarr, n);
    printf("=== ===\n");
}

void test_equals_1() {
    printf("=== test 2 array equal ===\n");
    int n = 5;
    int arr1[n];
    _range(arr1, n);
    int arr2[n];
    _range(arr2, n);
    if (arr_equal(arr1, arr2, n) == 1) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }
    printf("=== ===\n");
}

void test_tsp_1() {
    printf("=== tsp1 ===\n");
    int n = 3;
    double true_distance = 12.0;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(0.0, 3.0);
    cities[2] = make_city(4.0, 0.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    if (rdistance == true_distance) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }
    printf("12.0 != %f\n", rdistance);
    printf("=== ===\n");
}


void test_tsp_2() {
    printf("=== tsp2 ===\n");
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

    if (rdistance == true_distance) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }
    printf("=== ===\n");
}


void test_tsp_3() {
    printf("=== tsp3 ===\n");
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

    if (rdistance == true_distance) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }
    printf("=== ===\n");
}


void test_tsp_4() {
    printf("=== tsp4 ===\n");
    int n = 3;
    double true_distance = 0;
    city cities[n];
    cities[0] = make_city(0.0, 0.0);
    cities[1] = make_city(0.0, 0.0);
    cities[2] = make_city(0.0, 0.0);
    double rdistance = 0.0;
    int rpath[n];
    tsp(&rdistance, rpath, cities, n);

    if (rdistance == true_distance) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }
    printf("=== ===\n");
}

void test_tsp_5() {
    printf("=== tsp5 ===\n");
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
    if (almost_equal(rdistance, true_distance) == 1) {
        printf("success!\n");
    }
    else {
        printf("fail!\n");
    }
    printf("=== ===\n");
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

void random_cities_1() {
    printf("=== random cities 1 ===\n");
    int n = 5;
    double threshold = .01;
    int order[n];
    _range(order, n);
    city cities[n];
    random_cities(cities, n, threshold);
    print_cities(cities, order, n);
    printf("=== ===\n");
}



int main() {
    test_tsp_1();
    test_tsp_2();
    test_tsp_3();
    test_tsp_4();
    test_tsp_5();
    test_remove_1();
    test_remove_2();
    test_almost_equal();
    test_add_1();
    test_cp_int_array_1();
    test_equals_1();
    random_cities_1();
    // test_tsp_memory();
}
