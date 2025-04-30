#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void bubblesort(char* a) {
    for (long unsigned i = strlen(a); i > 1; --i) {
        // größten Wert nach hinten schieben
        for (long unsigned j = 0; j < i -1; ++j) {
            if (strcmp(&a[j], &a[j + 1]) > 0) {
                char * tmp = malloc(sizeof(a));
                tmp = &a[j + 1];
                a[j + 1] = a[j];
                a[j] = *tmp;
            }
        }
    } 
} // bubblesort

/**
 * main ist der Startpunkt des Programms.
 */
int main(int argc, const char *argv[]) {
    //--------------------------------------------- Arraygroesse bestimmen
    if (argc != 2) {
        fprintf(stderr, "Aufruf: ./stringsort Anzahl\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 1) {
        fprintf(stderr, "Anzahl muss mindestens 1 sein\n");
        return 1;
    }

    //--------------------------------------------------- Strings wuerfeln
    char* a = malloc(n * sizeof(char));

    if (a == NULL) {
        fprintf(stderr, "Error: a wurde kein Speicher zugewiesen");
    }

    srand((unsigned int) time(NULL));

    printf("Unsortiertes Array:\n");
    for (long unsigned i = 0; i < strlen(a); ++i) {
        
        //char** ptrArr = malloc(sizeof(a) * sizeof(&argv[1] + '\0'));
        /*a[i] = sprintf(malloc(sizeof(ptrArr)), "%c", r);
        printf("%c ", a[i]);
        free(ptrArr);*/
        a[i] = rand();
        //sprintf(malloc(sizeof(ptrArr)), "%s", &a[i]);
        printf("%s", &a[i]);
    }
    printf("\n");

    //-------------------------------------------------- Strings sortieren
    bubblesort(a);

    //--------------------------------------------------- Strings ausgeben
    printf("Sortiertes Array:\n");
    char* s = malloc(sizeof(a) * sizeof(a[0]));
    strcat(s, &a[0]);
    
    for (long unsigned i = 1; i < strlen(a); ++i) {
        if (strcmp(&a[i], &a[i - 1]) == 0) {
            strcat(s, "*");
        } else {
            strcpy(s, " ");
            strcat(s, &a[i]);
        }
    }

    printf("%s\n", s);
    free(a);
    return 0;
} // main
