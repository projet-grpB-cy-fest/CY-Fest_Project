#include <stdio.h>
#include <time.h>
#include <unistd.h>


struct tm constructeur_date(struct tm date);//fonction qui demande à l'utilisateur le jour, l'heure et la minute de la fin du concert
void affiche_date(struct tm date);//fonction qui affiche la date entré
struct tm validation_date( );//fonction qui s'assure si le choix de l'utilisateur lui convient
int duree_activite(struct tm fin, struct tm instant_t);//Indique la fin des reservation, retourne 1 si le concert est fini/commencé, dans ce cas aucune réservation n'est possible puisque le concert est fini/commencé. Sinon retourne 0.