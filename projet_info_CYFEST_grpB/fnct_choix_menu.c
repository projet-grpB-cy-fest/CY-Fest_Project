#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "entete_fnct_principal.h"

void choixmenu();
void choixmenu_mode(int mode);

void choixmenu_mode(int mode){
    int choix_manager,choix_festivalier,choix_salles,i=0,j=0;
        Salle *salles_concert=malloc(100*sizeof(Salle));
//mode manager:
    if(mode==1){

    //menu
        printf("\n1-Creer une salle \n2-Modifier la configuration d'une salle \n3-Etat de la salle \n4-Retour au menu principal ");
    
    //boucle vérifie si la valeur entrez est correct
        do{
            printf("\n\nEntrez votre choix: ");
            scanf("%d",&choix_manager);
        }while(choix_manager<1||choix_manager>4);
    
    //boucle switch case pour chaque valeur entrez
        switch(choix_manager){
            case 4:
                //retour menu principal
                choixmenu();
            break;

            case 1:
                //Creer une salle
                printf("\nCreation salle: ");
                //appelle fonction correspondante
                j++;
                *(salles_concert+(j-1))=constructeur_Salle();
                choixmenu_mode(1);
            break;

            case 2:
                //Configurer salle
                printf("\nConfiguration salle: ");
                //appelle fonction correspondante
                do{
                   for(i; i<j; i++){
                        printf("\n%d-%s %s",i+1,&salles_concert[i].nom_salle, &salles_concert[i].groupe);
                    }
                    printf("\nQuelle salle voullez-vous modifier? : ");
                    scanf("%d",choix_salles); 
                }while(choix_salles<=0||choix_salles>j);
                Salle salle_modifier=configuration_Salle(salles_concert[choix_salles-1]);  
                choixmenu_mode(1);          
            break;

            case 3:
                //Etat de la salle
                printf("\nEtat salle: ");
                //appelle fonction correspondante
                do{
                   for(i; i<j; i++){
                        printf("\n%d-%s %s",i+1,&salles_concert[i].nom_salle, &salles_concert[i].groupe);
                    }
                    printf("\nChoisissez une salle pour voir son ratio de siéges reservés sur le nombre de siéges total: ");
                    scanf("%d",choix_salles); 
                }while(choix_salles<=0||choix_salles>j);
                printf("\nRatio salle %s: %ld",salles_concert[choix_salles-1].nom_salle,calculerRatio(salles_concert[choix_salles-1].nb_siege_reserves, salles_concert[choix_salles-1].nb_siege));
                choixmenu_mode(1);
            break;

            default:
                //message d'erreur ou cas ou
                printf("\nerreur saisie");
                choixmenu_mode(1);
            break;
        }
        free(salles_concert);
    }

    //mode festivalier:
    if(mode==2){
       //menu
        printf("\n1-Réservation \n2-Retour au menu principal ");
    
    //boucle vérifie si la valeur entrez est correct
        do{
            printf("\n\nEntrez votre choix: ");
            scanf("%d",&choix_festivalier);
        }while(choix_festivalier<1||choix_festivalier>2);

        if(choix_festivalier==1){
            gestionFestivalier(salles_concert);
            choixmenu_mode(2);
        }
        else if(choix_festivalier==2){
        //retour menu principal
            choixmenu();
        }
    }
//Quitter le programme
    if(mode==3){
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
 
        printf("\n   Aurevoir    \n");
        return ;
    }

}

void choixmenu(){
    int mode;
 
//entrez le mode:
    printf("\n1-MANAGER \n2-FESTIVALIER \n3-QUITTER");

//boucle vérifie si la valeur entrez est correct
    do{
        printf("\n\nEntrez votre choix: ");
        scanf("%d",&mode);
    }while(mode<1||mode>3);

    choixmenu_mode(mode);

}
