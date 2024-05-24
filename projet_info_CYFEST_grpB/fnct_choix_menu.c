#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
//Appele fichier.h du programme fnct_principal.c
#include "entete_fnct_principal.h"

//Appele fonctions du programme
void choixmenu();
void choixmenu_mode(int mode);
void afficherListeSalles(Salle salles[], int nb_salles);

//Fonction pour afficher la liste des salles créées pour la configuration
void afficherListeSalles(Salle salles[], int nb_salles) {
    printf("Liste des salles créées :\n");
    for (int i = 0; i < nb_salles; i++) {
        printf("%d. %s\n", i + 1, salles[i].nom_salle);
    }
}

//Fonction pour afficher le menu selon le mode choisi
void choixmenu_mode(int mode){
    int choix_manager,choix_festivalier,choix_salles,i=0,j=0;
    Salle salles_concert[NB_SALLES];
    //Mode manager
    if(mode==1){

        //Menu du mode manager
        printf("\n1-Creer une salle \n2-Modifier la configuration d'une salle \n3-Etat de la salle \n4-Retour au menu principal ");
    
        //Boucle qui vérifie si la valeur entrée est correct
        do{
            choix_manager=better_scan_int("\n\nEntrez votre choix: ");
        }while(choix_manager<1||choix_manager>4); 
    
        //Boucle switch case pour chaque valeur entrez
        switch(choix_manager){
            case 4:
                //Retour au menu principale
                choixmenu();
            break;

            case 1:
                //Créer une salle
                printf("\nCreation salle: ");
                
                //Création de salle, appele de la fonction constructeur_Salle du programme fnct_principal.c
                for (int i = 0; i < NB_SALLES; i++) {
                    printf("Création de la salle %d\n", i + 1);
                    salles_concert[i] = constructeur_Salle();
                }
                afficherListeSalles(salles_concert,NB_SALLES);
                //Retour au menu manager
                choixmenu_mode(1);
                
            break;

            case 2:
                //Configurer salle
                printf("\nConfiguration salle: ");
                //Configuration d'une salle, appele de la fonction configuration_Salle du programme fnct_principal.c
                do{
                    afficherListeSalles(salles_concert,NB_SALLES);
                    choix_salles=better_scan_int("Quelle salle voulez-vous modifier: "); 
                }while(choix_salles<=0||choix_salles>NB_SALLES);
                Salle salle_modifier=configuration_Salle(salles_concert[choix_salles-1]);  
                //Retour au menu manager
                choixmenu_mode(1);          
            break;

            case 3:
                //Etat de la salle
                printf("\nEtat salle: ");
                //Ratio d'une salle, appele de la fonction calculerRatio du programme fnct_principal.c
                afficherRatioReservation(salles_concert,NB_SALLES); 
                //Retour au menu manager
                choixmenu_mode(1);
            break;

            default:
                //Message d'erreur
                printf("\nerreur saisie");
                //Retour au menu manager
                choixmenu_mode(1);
            break;
        }
    }

    //Mode festivalier:
    if(mode==2){
       //Menu du mode festivalier
        printf("\n1-Réservation \n2-Retour au menu principal ");
    
        //Boucle qui vérifie si la valeur entrez est correct
        do{
            choix_festivalier=better_scan_int("\n\nEntrez votre choix: ");
        }while(choix_festivalier<1||choix_festivalier>2);

        //Réservation d'un siége, appele de la fonction gestionFestivalier du programme fnct_principal.c
        if(choix_festivalier==1){
            gestionFestivalier(salles_concert);
            //Retour au menu manager
            choixmenu_mode(2);
        }
        else if(choix_festivalier==2){
            //Retour au menu principal
            choixmenu();
        }
    }

    //Quitter le programme:
    if(mode==3){
        printf("Le feu d'artifice va commencer !\n");
    
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
        printf("\rLe feu d'artifice a commencé !\n");
 
        printf("\n  %s Aurevoir %s   \n","\U0001f386","\U0001f386");
        //Fin du programme
        return ;
    }

}

//Fonction pour afficher le menu principale
void choixmenu(){
    int mode;
 
    //Entrez le mode:
    printf("\n1-MANAGER \n2-FESTIVALIER \n3-QUITTER");

    //Boucle qui vérifie si la valeur entrez est correct
    do{
        mode=better_scan_int("\n\nEntrez votre choix: ");
    }while(mode<1||mode>3);

    //Accéder au mode choisi
    choixmenu_mode(mode);

}