
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define couleur(param) printf("\033[%sm",param)

int main() {
    couleur("46");
    couleur("0");
    couleur("46");
    couleur("0");
    couleur("46");
    couleur("0");
    couleur("46");
    couleur("0");

    int tab[10][10]; // Correction: le tableau est de taille 10*10

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Initialisation du tableau à zéro
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tab[i][j] = 0;
        }
    }

    // Placement aléatoire des "X"
    for (int i = 0; i < 10; i++) {
        int random_column = rand() % 10;
        tab[i][random_column] = 1;
    }

    // Affichage de la salle avec les numéros de place
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (tab[i][j] == 0)
                printf("%d ", i * 10 + j + 1);
            else
                printf("X ");
        }
        printf("\n");
    }

    return 0;
}


