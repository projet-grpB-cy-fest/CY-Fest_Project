//Inclusions
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <errno.h>
//Appele fichier.h du programme fnct_choix_menu.c
#include "entete_choix_menu.h"

//Definitions
#define couleur(param) printf("\033[%sm", param)

//Fonctions
void afficherMessageBienvenue();//Fonction pour afficher un message de bienvenue