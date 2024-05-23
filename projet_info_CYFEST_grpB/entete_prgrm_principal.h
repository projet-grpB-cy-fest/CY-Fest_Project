#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <errno.h>
#include "entete_choix_menu.h"

#define couleur(param) printf("\033[%sm", param)

void afficherMessageBienvenue();// Fonction pour afficher un message de bienvenue