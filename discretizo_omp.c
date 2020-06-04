#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 10000
#define SUB14 0
#define SUB24 1
#define SUB64 2
#define OLD 3
#define NTHREADS 4

void init_ages_array(int ages[]) {
    for(int i = 0; i < N; i++) {
        ages[i] = rand() % 96;
    }
}

void init_groups(int groups[]) {
    for(int i = 0; i < 4; i++) {
        groups[i] = 0;
    }
}

void discretize_values(int ages[], int groups[]) {
    # pragma omp parallel 
    {
        # pragma omp sections 
        {
            # pragma omp section 
            {
                for(int i = 0; i < N; i++) {
                    if(ages[i] <= 14) {
                        groups[SUB14]++;
                    }
                }
            }
            # pragma omp section 
            {
                for(int i = 0; i < N; i++) {
                    if(ages[i] > 14 && ages[i] <= 24) {
                        groups[SUB24]++;
                    }
                }
            }
            # pragma omp section 
            {
                for(int i = 0; i < N; i++) {
                    if(ages[i] > 24 && ages[i] <= 64) {
                        groups[SUB64]++;
                    }
                }
            }
            # pragma omp section 
            {
                for(int i = 0; i < N; i++) {
                    if(ages[i] > 64) {
                        groups[OLD]++;
                    }
                }
            }
        }
    }
}

int main() {
    int ages[N];
    int groups[4];
    clock_t start, end;
    float seconds;

    omp_set_num_threads(NTHREADS);

    init_groups(groups);
    init_ages_array(ages);

    start = clock();
    discretize_values(ages, groups);
    seconds = (float)(clock() - start) / CLOCKS_PER_SEC;

    printf("There are %d sub 14\n", groups[SUB14]);
    printf("There are %d sub 24\n", groups[SUB24]);
    printf("There are %d sub 64\n", groups[SUB64]);
    printf("There are %d old\n", groups[OLD]);
    printf("The parallel algorithm took %f", seconds);
}