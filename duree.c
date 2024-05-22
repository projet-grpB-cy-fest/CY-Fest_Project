#include <stdio.h>
#include <time.h>
#include <unistd.h>

//fonction qui demande à l'utilisateur le jour, l'heure et la minute du début ou de la fin de l'activité
//sturct tm date: structure contenant les informations nécessaire pour déterminer le temps
struct tm constructeur_date(struct tm date){

    //vérifier que la valeur entrée est correct
    do{
        printf("\nJour: ");
        scanf("%d",&date.tm_mday);
    }while(date.tm_mday<1 || date.tm_mday>31);

    //vérifier que la valeur entrée est correct
    do{
        printf("\nHeure: ");
        scanf("%d",&date.tm_hour);
    }while(date.tm_hour<0 || date.tm_hour>23);

    //vérifier que la valeur entrée est correct
    do{
        printf("\nMinute: ");
        scanf("%d",&date.tm_min);
    }while(date.tm_min<0 || date.tm_min>59);

    //initialiser les autres valeurs à 0
    date.tm_year=0;
    date.tm_mon=0;
    date.tm_sec=0;
    return date;
}

//fonction qui affiche la date entrée
void affiche_date(struct tm date){
    printf("\nle %d à %d:%d\n",date.tm_mday,date.tm_hour,date.tm_min);
}

//fonction afficher pour l'utilisateur, elle s'assure si le choix de l'utilisateur lui convient
struct tm validation_date( ){
    int date_correct;
    struct tm date;
    while(date_correct!=1){//continue jusqu'à ce que la date convient à l'utilisateur
        date=constructeur_date(date);//fonction pour créer la date
        printf("\nCette date vous correspond elle?: ");
        affiche_date(date);//affiche la date entrée par l'utilisateur
        do{
            printf("\n 1|OUI     2|NON\n");
            scanf("%d",&date_correct); 
        }while(date_correct<1 || date_correct>2);//recommence si la valeur entrée ne correspond pas aux choix
    }
    return date;

}

//Indique la fin des reservations, retourne 1 si le concert est fini/commencé, dans ce cas aucune réservation n'est possible puisque le concert est fini/commencé. Sinon retourne 0.
//instant_t pourrait étre la valeur entreé par l'utilisateur pour indiquer l'heure de reservation 
int duree_activite(struct tm fin, struct tm instant_t){
    if(instant_t.tm_mday>=fin.tm_mday){
        if(instant_t.tm_hour>=fin.tm_hour){
            if(instant_t.tm_min>=fin.tm_min){
                printf("fin");
                return 1;
            }
        }
    }
    printf("libre");
    return 0;

}

int main( ){
    struct tm date_fin;
    struct tm instant; //structure de date

    //l'utilisateur entre l'heure de fin de l'activité
    printf("\nfin:\n");
    date_fin=validation_date();

    //demande à l'utilisateur la date de réservation (inserer une fonction pour comparer la date avec celle de l'activité choisie)
    printf("\ninstant\n");
    instant=validation_date();

    //vérifier si la réservation est possible
    duree_activite(date_fin,instant);

    return 0;
} 
//source: http://sdz.tdct.org/sdz/ime-h-et-ses-fonctions.html
//        https://koor.fr/C/ctime/ctime.wp
// CHATGPT 
