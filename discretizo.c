#include <stdio.h>
#include <stdlib.h>

#define N 100

void init_ages_array(int ages[]) {
    for(int i = 0; i < N; i++) {
        ages[i] = rand() % 96;
    }
}

int main() {
    int ages[N];

    init_ages_array(ages);

}