#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define N 10000
#define SUB14 0
#define SUB24 1
#define SUB64 2
#define OLD 3

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

void discretize_values(int ages[], int groups[], int rank, int num_tasks, int sndcounts[], int displ[]) {
    int local_groups[4], process_index;
    int local_ages[N];

    init_groups(local_groups);
    MPI_Scatterv(ages, sndcounts, displ, MPI_INT, local_ages, sndcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < sndcounts[rank]; i++) {
        int age = local_ages[i];

        if(age <= 14) {
            local_groups[SUB14]++;
        } else if(age <= 24) {
            local_groups[SUB24]++;
        } else if(age <= 64) {
            local_groups[SUB64]++;
        } else {
            local_groups[OLD]++;
        }
    }

    MPI_Reduce(local_groups, groups, 4, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
}

int main(int argc, char** argv) {
    int ages[N];
    int groups[4], sndcounts[4], displ[4];
    clock_t start, end;
    float seconds;
    int rank, numtasks;
    int elements_to_process, leftover_elements;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Calculate buffer size of each process
    elements_to_process = N / numtasks;
    leftover_elements = N % numtasks;
    for(int i = 0; i < 4; i++) {
        if (i < 3) {
            sndcounts[i] = elements_to_process;
        } else {
            sndcounts[i] = elements_to_process + leftover_elements;
        }
        displ[i] = i * elements_to_process;
    }

    if(rank == 0) {
        init_groups(groups);
        init_ages_array(ages);
        start = clock();
    }

    discretize_values(ages, groups, rank, numtasks, sndcounts, displ);
    MPI_Finalize();

    if(rank == 0) { 
        seconds = (float)(clock() - start) / CLOCKS_PER_SEC;

        printf("\n");
        printf("There are %d sub 14\n", groups[SUB14]);
        printf("There are %d sub 24\n", groups[SUB24]);
        printf("There are %d sub 64\n", groups[SUB64]);
        printf("There are %d old\n", groups[OLD]);
        printf("The parallel mpi algorithm took %f", seconds);
    }  
}