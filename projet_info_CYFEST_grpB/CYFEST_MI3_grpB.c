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
    printf("*%s%s%sBienvenue dans notre grand festival !%s%s%s*\n","\U0001f91f","\U0001f60e","\U0001f91f","\U0001f91f","\U0001f60e","\U0001f91f";)
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

 //source: https://stackoverflow.com/questions/73173217/how-do-i-add-an-emoji-on-my-printing-text-using-c-language
 //https://www.developpez.net/forums/d311883/c-cpp/c/smiley-langage-c/
 //https://unicode.org/emoji/charts/full-emoji-list.html
