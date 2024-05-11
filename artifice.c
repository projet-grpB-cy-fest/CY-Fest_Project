#include <stdio.h>
#include <unistd.h> // Pour la fonction sleep()
#include <stdlib.h> // Pour la fonction rand()

void afficherFeuDartifice() {
    printf("\n");
    printf("    *    \n");
    printf("   ***   \n");
    printf("  *****  \n");
    printf("    |    \n");
    printf("    |    \n");
    printf("    |    \n");
    printf("\n");
}

int main() {
    printf("Le feu d'artifice va commencer !\n");

    // Compte à rebours de 10 à 0
    for (int i = 10; i >= 0; i--) {
        printf("\r%d ", i); // Retour au début de la ligne et affichage du chiffre
        fflush(stdout); // Forcer le terminal à afficher le texte immédiatement
        sleep(1); // Pause d'une seconde
    }

    // Animation pour signaler le début du feu d'artifice
    printf("\rBOUM !");
    fflush(stdout);
    sleep(1);
    printf("\r         ");
    fflush(stdout);
    sleep(1);
    printf("\rLe feu d'artifice a commencé !\n");

    // Affichage du feu d'artifice
    afficherFeuDartifice();

    return 0;
}