#include <stdio.h>
#include <stdlib.h>

void choixmenu(){
    int mode,choix_manager,choix_festivalier;

//entrez le mode:
    printf("\n1-MANAGER \n2-FESTIVALIER ");

//boucle vérifie si la valeur entrez est correct
    do{
        printf("\n\nEntrez votre choix: ");
        scanf("%d",&mode);
    }while(mode<1||mode>2);

//mode manager:
    if(mode==1){

    //menu
        printf("\n1-Creer une salle \n2-Reserver une salle \n3-Modifier la configuration d'une salle \n4-Etat de la salle \n5-Retour au menu principal ");
    
    //boucle vérifie si la valeur entrez est correct
        do{
            printf("\n\nEntrez votre choix: ");
            scanf("%d",&choix_manager);
        }while(choix_manager<1||choix_manager>5);
    
    //boucle switch case pour chaque valeur entrez
        switch(choix_manager){
            case 5:
                //retour menu principal
                choixmenu();
            break;

            case 1:
                //Creer une salle
                printf("\nCreation salle: ");
                //appelle fonction correspondante
            break;

            case 2:
                //Reserver salle
                printf("\nReservation salle: ");
                //appelle fonction correspondante
            break;

            case 3:
                //Configurer salle
                printf("\nConfiguration salle: ");
                //appelle fonction correspondante
            break;

            case 4:
                //Etat de la salle
                printf("\nEtat salle: ");
                //appelle fonction correspondante
            break;

            default:
                //message d'erreur ou cas ou
                printf("\nerreur saisie");
            break;
        }
    }

//mode festivalier:
    if(mode==2){

    //menu
        printf("\n1-Afficher les salles \n2-Reservation \n3-Retour menu principal ");
   
    //boucle vérifie si la valeur entrez est correct
        do{
            printf("\n\nEntrez votre choix: ");
            scanf("%d",&choix_festivalier);
        }while(choix_festivalier<1||choix_festivalier>3);
    
    //boucle switch case pour chaque valeur entrez
        switch(choix_festivalier){
            case 3:
                //retour menu principal
                choixmenu();
            break;
            
            case 1:
                //Afficher les salles
                printf("\nAffichage salles: ");
                //appelle fonction correspondante
            break;
            
            case 2:
                //Réservation
                printf("\nReservation siege: ");
                //appelle fonction correspondante
            break;
            
            default:
                //message d'erreur ou cas ou
                printf("\nerreur saisie");
            break;
        }
    }

}

int main(){
//appele fonction
choixmenu();
return 0;
}