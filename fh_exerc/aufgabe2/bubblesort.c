#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Bubblesort liest ganze Zahlen ein und sortiert sie aufsteigend.*/
int main(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Aufruf: gcc -o bubblesort bubblesort.c\n./bubblesort Anzahl\n");
        return 1;
    }
    srand((unsigned int) time(NULL));
    int random = rand();
    int n = atoi(argv[1]);
    int a[n];
    char (*ptr) [__INT_MAX__] = malloc(n * sizeof(int));
    int stdin;
    int len = (sizeof(a) / sizeof(a[0]));

    //---------------------------------------------------- Zahlen einlesen
    printf("Bitte %d ganze Zahlen eingeben: ", n);
    int k = 0;
    for (int i = 0; i < len && (scanf("%d", &stdin) > 0); ++i) {
        a[i] = scanf("%d", &stdin);
        ++k;
    }

    for (int i = k; i < len; ++i) {
        a[i] = random;
        printf("%d\n", a[i]);
    }

    //--------------------------------------------------- Zahlen sortieren
    for (int i = len; i > 1; --i) {
        // groessten Wert nach hinten schieben
        for (int j = 0; j < i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                // Werte tauschen
                int tmp = a [j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
            }
        }
    }

    //---------------------------------------------------- Zahlen ausgeben
    printf("Sortierte Zahlenfolge: \n");
    for (int m = 0; m < len; ++m) {
        printf("%d", m);
    }

    return 0;
}
