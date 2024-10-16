#include <math.h>
#include <time.h>
#include <float.h>
#include <string.h>

/*
Cities and distances
*/
typedef struct
{
    double x;
    double y;
} city;

city make_city(double x, double y)
{
    city c;
    c.x = x;
    c.y = y;
    return c;
}

void print_cities(city* cities, int* order, int n) {
    printf("'points': [\n");
    for (int i = 0; i < n; i++) {
        city c = cities[order[i]];
        printf("{\n'x':%f,\n'y':%f\n},", c.x, c.y);
    }
    city c = cities[order[0]];
    printf("{\n'x':%f,\n'y':%f\n}", c.x, c.y);
    printf("],\n");
}

void print_output(double rdistance, city* cities, int* rpath, int n, double cpu_time_used) {
    printf("{ 'distance': %f,\n", rdistance);
    print_cities(cities, rpath, n);
    printf("'cpu_time': %f}\n", cpu_time_used);
}

/*
given the program arguments of the city coordiantes
return a list of cities structs
*/
void _get_cities(int argc, char* argv[], city* cities) {
    for (int i = 1; i < argc; i++) {
        char* str = argv[i];
        char* token = strtok(str, ",");
        
        if (token != NULL) {
            double first_num = (double)atoi(token);
            token = strtok(NULL, ",");
            
            if (token != NULL) {
                double second_num = (double)atoi(token);
                // printf("String %d: First number = %f, Second number = %f\n", i, first_num, second_num);
       
                cities[i-1] = make_city(first_num, second_num);
            } else {
                printf("Invalid format for string %d\n", i);
                printf("1");
            }
        } else {
            printf("Invalid format for string %d\n", i);
        }
    }
}


double get_distance(city c1, city c2)
{
    return pow(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2), .5);
}

void get_distances(double *distances, city *cities, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double dist = get_distance(cities[i], cities[j]);
            distances[(i * n) + j] = dist;
        }
    }
}

void print_distances(double *distances, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", distances[(i * n) + j]);
        }
        printf("\n\n");
    }
}

/*
code for random cities
*/

/*
check whether or not a city is withing the threshold distance of
the other cities
*/
int within_range(city *cities, int n, city c, double threshold)
{
    for (int i = 0; i < n; i++)
    {
        double dist = get_distance(c, cities[i]);
        if (dist < threshold)
        {
            return 1;
        }
    }
    return 0;
}

/*
creates random cities and stores them in the cities array
if the cities are withing a certain distance of one another,
create another random city and try again
*/
void random_cities(city *cities, int n, double threshold)
{
    srand(time(NULL));
    int x, y, in_range;
    city c;
    for (int i = 0; i < n; i++)
    {
        while (1)
        {
            x = rand();
            y = rand();
            c = make_city(x, y);
            in_range = within_range(cities, i, c, threshold);
            if (in_range == 0)
            {
                break;
            }
        }
        cities[i] = c;
    }
}

/*
receive the number of cities that the user wants
*/
int input_random_cities()
{
    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);
    return number;
}

/*
bit operation functions
*/

/*
set available cities where each bit represents if a city
has been visited or not. A bit of:
    1 represents a city being available to visit
    0 represents a city not being avaiable to visit
*/
unsigned int set_available_cities(unsigned int n)
{
    int ret = 0;
    for (int i = 1; i < n; i++)
    {
        ret |= (1 << i);
    }
    return ret;
}

/*
mark city as visited
*/
unsigned int mark(unsigned int n, unsigned int position)
{
    unsigned int mask = ~(1 << position);
    unsigned int new_n = n & mask;
    return new_n;
}

void printBinary(unsigned int num)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf(" (%u)\n", num);
}

void print_memo(double **memo, int cc, int ac)
{
    for (int i = 0; i < cc; i++)
    {
        for (int j = 0; j < ac; j++)
        {
            printf("%f, ", memo[i][j]);
        }
        printf("\n");
    }
}

double **make_memo(int cc, int ac)
{
    double **memo = (double **)malloc(cc * sizeof(double *));
    for (int i = 0; i < cc; i++)
    {
        memo[i] = (double *)malloc(ac * sizeof(double));
        for (int j = 0; j < ac; j++)
        {
            memo[i][j] = 0.0;
        }
    }
    return memo;
}

// global variables for the tsp and tsp_helper functions below
double best_so_far;
int fc = 0;        // first city will always have an id of 0
double *distances; // distance matrix for each city
int n;             // number of cities
double **memo;
double **memo_path;

/*
The dynamic programming tsp function
This uses bit masking
*/
double tsp_helper(unsigned int cc, unsigned int ac)
{
    if (ac == 0)
    {
        memo[cc][0] = distances[(cc * n) + 0];
        return distances[(cc * n) + 0];
    }
    if (memo[cc][ac] != 0)
    {
        return memo[cc][ac];
    }
    double best_dist = -1;
    double next_city = -1;
    for (int i = 0; i < n; i++)
    {
        if (ac & (1 << i))
        {
            int new_ac = mark(ac, i);
            double potential_best = tsp_helper(i, new_ac) + distances[(cc * n) + i];
            if ((best_dist == -1) || (potential_best < best_dist))
            {
                best_dist = potential_best;
                next_city = i;
            }
        }
    }
    memo_path[cc][ac] = next_city;
    memo[cc][ac] = best_dist;
    return best_dist;
}


void get_path(int *path) {
    int cc = 0;
    int ac = set_available_cities(n);
    path[0] = 0;
    for (int i = 1; i < n; i++)
    {
        cc = memo_path[cc][ac];
        path[i] = cc;
        ac = mark(ac, cc);
    }
}

void print_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n-1) {
            printf("%d, ", arr[i]);
        }
        else {
            printf("%d\n", arr[i]);
        }
    }
}

void print_path()
{
    int cc = 0;
    int ac = set_available_cities(n);
    printf("0 -> ");
    for (int i = 0; i < n - 1; i++)
    {
        cc = memo_path[cc][ac];
        printf("%d -> ", cc);
        ac = mark(ac, cc);
    }
    printf("0\n");
}

/*
given n city coordinates
return the shortest path and the distance of that path
*/
void tsp(double *rdistance, int *rpath, city *cities, int num_cities)
{
    // set globals
    best_so_far = DBL_MAX;
    n = num_cities;
    double d[n * n];
    distances = d;
    get_distances(distances, cities, n);
    memo = (double **)make_memo(n, 1 << n);
    memo_path = (double **)make_memo(n, 1 << n);

    unsigned int available_cities = set_available_cities(n);
    unsigned int current_city = 0;
    double distance = tsp_helper(current_city, available_cities);
    get_path(rpath);
    *rdistance = distance;
}
