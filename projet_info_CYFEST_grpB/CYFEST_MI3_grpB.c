#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
//Appele fichier.h du programme fnct_choix_menu.c
#include "entete_choix_menu.h"

//Couleur
#define couleur(param) printf("\033[%sm", param)

//Fonction pour afficher un message de bienvenue
void afficherMessageBienvenue() {
    //Violet et gras
    couleur("1;35"); 
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*  _       __     __                             *\n");
    printf("* | |     / /__  / /________  ____ ___  ___      *\n");
    printf("* | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\     *\n");
    printf("* | |/ |/ /  __/ / /__/ /_/ / / / / /  __/     *\n");
    printf("* |__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/      *\n");
    printf("*                                                *\n");
    printf("*      Bienvenue dans notre grand festival !     *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    //Réinitialisation de la couleur
    couleur("0"); 
}

int main( ){
    //Appele fonction afficherMessageBienvenue
    afficherMessageBienvenue();
    //Appele fonction choixmenu du programme fnct_choix_menu.c
    choixmenu();
 
    return 0;
}
