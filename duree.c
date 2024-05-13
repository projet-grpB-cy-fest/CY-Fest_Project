#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct tm constructeur_date(struct tm date){//fonction qui demande à l'utilisateur le jour, l'heure et la minute du début ou de la fin de l'activité
//sturct tm date: structure contenant les informations nécessaire pour déterminer le temps
    
    do{//vérifie que la valeur entrée est correct
        printf("\nJour: ");
        scanf("%d",&date.tm_mday);
    }while(date.tm_mday<1 || date.tm_mday>31);

    do{//vérifie que la valeur entrée est correct
        printf("\nHeure: ");
        scanf("%d",&date.tm_hour);
    }while(date.tm_hour<0 || date.tm_hour>23);

    do{//vérifie que la valeur entrée est correct
        printf("\nMinute: ");
        scanf("%d",&date.tm_min);
    }while(date.tm_min<0 || date.tm_min>59);

    //initialise les autres valeurs à 0
    date.tm_year=0;
    date.tm_mon=0;
    date.tm_sec=0;
    return date;
}

void affiche_date(struct tm date){//fonction qui affiche la date entré
    printf("\nle %d à %d:%d\n",date.tm_mday,date.tm_hour,date.tm_min);
}

void validation_date(struct tm date){//fonction afficher pour l'utilisateur, s'assure si le choix de l'utilisateur lui convient
    int date_correct;
    while(date_correct!=1){//continue jusqu'à ce que la date convient à l'utilisateur
        constructeur_date(date);//fonction pour créer la date
        printf("\nCette date vous correspond elle?: ");
        affiche_date(date);//affiche la date entrée par l'utilisateur
        do{
            printf("\n 1|OUI     2|NON\n");
            scanf("%d",&date_correct); 
        }while(date_correct<1 || date_correct>2);//recommence si la valeur entrée ne correspond pas aux choix
    }

}

int duree_activite(struct tm fin, struct tm instant_t){//Indique la fin des reservation, retourne 1 si le concert est fini/commencé, dans ce cas aucune réservation n'est possible puisque le concert est fini/commencé. Sinon retourne 0.
//instant_t pourrait étre la valeur entrez par l'utilisateur pour indiquer l'heure de reservation 
    if(instant_t.tm_mday>=fin.tm_mday || instant_t.tm_hour>=fin.tm_hour || instant_t.tm_min>=fin.tm_min){
        printf("fin");
        return 1;
    }
    else{
        printf("libre");
        return 0;
    }

}

int main( ){
    struct tm *date_debut;
    struct tm *date_fin;
    struct tm *instant;//structure de date

    //l'utilisateur rentre le début et la fin de l'activité
    

    //demande à l'utilisateur la date de réservation (inserer une fonction pour comparer la date avec celle de l'activité choisie)
    validation_date(&instant);

    //vérifie si la réservation est possible
    duree_activite(date_fin,instant);

    return 0;
} 
//source: http://sdz.tdct.org/sdz/ime-h-et-ses-fonctions.html
//        https://koor.fr/C/ctime/ctime.wp
