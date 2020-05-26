#include <stdio.h>
#include <stdlib.h>

#define N 10
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

void discretize_values(int ages[], int groups[]) {
    for(int i = 0; i < N; i++) {
        int age = ages[i];

        if(age <= 14) {
            groups[SUB14]++;
        } else if(age <= 24) {
            groups[SUB24]++;
        } else if(age <= 64) {
            groups[SUB64]++;
        } else {
            groups[OLD]++;
        }
    }
}

int main() {
    int ages[N];
    int groups[4];

    init_groups(groups);
    init_ages_array(ages);
    discretize_values(ages, groups);

    for(int i=0; i<N; i++) {
        printf("%d ", ages[i]);
    }
    printf("\n");

    printf("There are %d sub 14\n", groups[SUB14]);
    printf("There are %d sub 24\n", groups[SUB24]);
    printf("There are %d sub 64\n", groups[SUB64]);
    printf("There are %d old\n", groups[OLD]);


}