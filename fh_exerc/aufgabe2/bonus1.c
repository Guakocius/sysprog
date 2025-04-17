#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Bubblesort liest ganze Zahlen ein und sortiert sie aufsteigend.*/
int main(int argc, const char *argv[]) {

    srand((unsigned int) time(NULL));
    int n = 100000000;
    int* a = malloc(n * sizeof(int));

    if (a == NULL) {
        fprintf(stderr, "Error: a wurde kein Speicher zugewiesen");
    }

    for (int i = 0; i < n; ++i) {
        int r = rand() % n;
        a[r] = r;
    }

    free(a);
    return 0;
}
