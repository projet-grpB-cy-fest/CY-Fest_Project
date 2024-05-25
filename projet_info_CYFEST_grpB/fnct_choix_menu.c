#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
//Appele fichier.h du programme fnct_principal.c
#include "entete_fnct_principal.h"

//Appele fonctions du programme
void choixmenu();
void choixmenu_mode(int mode);
void afficherListeSalles(Salle salles[], int nb_salles);
void initialiserlisteSalles();
//Appele structure liste de salles
Salle salles_concert[NB_SALLES];

//Fonction pour initialiser la liste des salles créée
void initialiserlisteSalles() {
    for (int i = 0; i < NB_SALLES; i++) {
        strcpy(salles_concert[i].nom_salle, ""); // Initialiser les noms de salle à une chaîne vide
    }
}

//Fonction pour afficher la liste des salles créées
void afficherListeSalles(Salle salles[], int nb_salles) {
    printf("\nListe des salles créées:\n");
    for (int i = 0; i < nb_salles; i++) {
        if (strcmp(salles[i].nom_salle, "") != 0) {
            printf("%d. %s\n", i + 1, salles[i].nom_salle);
        }
    }
}

//Fonction pour afficher le menu selon le mode choisi
void choixmenu_mode(int mode){
    int choix_manager,choix_festivalier,choix_salles,i=0;
    //Mode manager
    if(mode==1){

        //Menu du mode manager
        printf("\nMode MANAGER: \n1-Creer une salle \n2-Modifier la configuration d'une salle \n3-Etat de la salle \n4-Retour au menu principal \n");
    
        //Boucle qui vérifie si la valeur entrée est correct
        do{
            choix_manager=better_scan_int("\n\nEntrez votre choix (1-4): ");
        }while(choix_manager<1||choix_manager>4); 
    
        //Boucle switch case pour chaque valeur entrez
        switch(choix_manager){
            case 4:
                //Retour au menu principale
                printf("\nRetour au menu principale\n");
                choixmenu();
            break;

            case 1:
                //Créer de salle
                printf("\nCréation de salle: \n");
                //Création d'une salle, appele de la fonction constructeur_Salle du programme fnct_principal.c
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") == 0) {
                        printf("\nCréation de la salle %d\n", i +1);
                        salles_concert[i] = constructeur_Salle();
                        break;
                    }
                }
                
                afficherListeSalles(salles_concert, NB_SALLES);
                //Retour au menu manager 
                choixmenu_mode(1);
                
            break;

            case 2:
                //Configurer salle
                printf("\nConfiguration salle: \n");
                //Configuration d'une salle, appele de la fonction configuration_Salle du programme fnct_principal.c
                afficherListeSalles(salles_concert,NB_SALLES);
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") != 0){
                        do{
                            choix_salles=better_scan_int("\nQuelle salle voulez-vous modifier: "); 
                        }while(choix_salles<=0||choix_salles>NB_SALLES);
                        Salle salle_modifier=configuration_Salle(salles_concert[choix_salles-1]);
                        salles_concert[choix_salles-1]=salle_modifier;
                        //Retour au menu manager 
                        choixmenu_mode(1); 
                    }
                    //Retour au menu manager
                    else{
                        printf("\nAucune salle encore créée, veuillez en créer une\n"); 
                        choixmenu_mode(1);
                    }
                }
                
                         
            break;

            case 3:
                //Ratio salle
                printf("\nÉtat salle: \n");
                //Ratio des salles créées (nombre de siége réservé sur nombre de siége qui est de 64), appele de la fonction calculerRatio du programme fnct_principal.c
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") != 0){
                        printf("%d) %s: %.2f%%\n", i+1, salles_concert[i].nom_salle, calculerRatio(salles_concert[i].nb_siege_reserves, salles_concert[i].nb_siege));
                    }
                    else{
                        printf("\nAucune salle encore créée, veuillez en créer une\n");
                        //Retour au menu manager
                        choixmenu_mode(1);
                    }
                }
                //Retour au menu manager
                choixmenu_mode(1);
            break;

            default:
                //Message d'erreur
                printf("\nerreur saisie\n");
                //Retour au menu manager
                choixmenu_mode(1);
            break;
        }
    }

    //Mode festivalier:
    if(mode==2){
       //Menu du mode festivalier
        printf("\nMenu FESTIVALIER: \n1-Réservation \n2-Retour au menu principal \n");
    
        //Boucle qui vérifie si la valeur entrez est correct
        do{
            choix_festivalier=better_scan_int("\n\nEntrez votre choix (1-2): ");
        }while(choix_festivalier<1||choix_festivalier>2);

        //Réservation d'un siége, appele de la fonction gestionFestivalier du programme fnct_principal.c
        if(choix_festivalier==1){
            printf("\nRéservation: \n");
            gestionFestivalier(salles_concert);
            //Retour au menu manager
            choixmenu_mode(2);
        }
        //Retour au menu principale
        else if(choix_festivalier==2){
            
            printf("\nRetour au menu principale\n");
            choixmenu();
        }
    }

    //Quitter le programme:
    if(mode==3){
        printf("\nLe feu d'artifice va commencer !\n");
    
        //Compte à rebours de 10 à 0
        for (int i = 10; i >= 0; i--) {
            //Retour au début de la ligne et affichage du chiffre
            printf("\r%d ", i); 
        //Forcer le terminal à afficher le texte immédiatement
            fflush(stdout); 
        //Pause d'une seconde
            sleep(1);
        }

        //Animation pour signaler le début du feu d'artifice
        printf("\rBOUM !%s","\U0001f387");
        fflush(stdout);
        sleep(1);
        printf("\r         ");
        fflush(stdout);
        sleep(1);
 
        printf("\n  %s Aurevoir %s   \n","\U0001f386","\U0001f386");
        //Fin du programme
        exit(1);
        
    }
    exit(1);
}

//Fonction pour afficher le menu principale
void choixmenu(){
    int mode;
 
    //Entrez le mode:
    printf("\nMODE: \n1-MANAGER \n2-FESTIVALIER \n3-QUITTER\n");

    //Boucle qui vérifie si la valeur entrez est correct
    do{
        mode=better_scan_int("\n\nEntrez votre choix (1-3): ");
    }while(mode<1||mode>3);

    //Accéder au mode choisi
    choixmenu_mode(mode);
}