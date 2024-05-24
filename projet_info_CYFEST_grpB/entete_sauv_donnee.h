#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>  
#include <errno.h>

 
void sauvegarde_donnee_salle(char* nom_salle, char* nom_groupe, int n_siege, int prix_avant, int prix_millieu, int prix_arriere, int fosse, int creneaux);//fonction sauvegarde données de créations de salles
void sauvegarde_donnee_salle_modif(char* nom_salle, char* nom_groupe, int n_siege, int prix_avant, int prix_millieu, int prix_arriere, int fosse, int creneaux);//fonction sauvegarde données de modification de salles
void sauvegarde_donnee_reservation(char* nom_salle, char* nom_groupe, int n_siege, int prix, int fosse, int creneaux);//fonction sauvegarde données de reservation siege
