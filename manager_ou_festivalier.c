 
 int main() {
    int a;
     do {
        printf("Veuillez choisir l'un des deux modes suivant (1.Manager, 2.Festivalier)\n");
        scanf("%d", &a);

        if (a == 1) {
            printf("Parfait, vous êtes en mode manager, c'est parti!\n");
        } else if (a == 2) {
            // Traitez le cas où l'utilisateur choisit l'option 2 ici si nécessaire
        } else {
            printf("Choix invalide. Veuillez saisir 1 ou 2.\n");
        }
    } while (a != 1 && a != 2);

    return 0;
 }
