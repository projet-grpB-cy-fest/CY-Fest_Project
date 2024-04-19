#include <stdio.h>
#include <time.h>
#include <unistd.h>

void constructeur_date(struct tm date){//fonction qui demande à l'utilisateur le jour, l'heure et la minute du début ou de la fin de l'activité
//sturct tm date: structure contenant les informations nécessaire pour déterminer le temps
    
    do{//vérifie que la valeur entrée est correct
        printf("\nJour: ");
        scanf("%d",date.tm_mday);
    }while(date.tm_mday<1 || date.tm_mday>31);

    do{//vérifie que la valeur entrée est correct
        printf("\nHeure: ");
        scanf("%d",date.tm_hour);
    }while(date.tm_hour<0 || date.tm_hour>23);

    do{//vérifie que la valeur entrée est correct
        printf("\nMinute: ");
        scanf("%d",date.tm_min);
    }while(date.tm_min<0 || date.tm_min>59);

    //initialise les autres valeurs à 0
    date.tm_year=0;
    date.tm_mon=0;
    date.tm_sec=0;
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

int duree_activite(struct tm debut, struct tm fin, struct tm instant_t){//Affiche le temps d'attente entre le date rentrée au début et celle à la fin de l'activité, le compte à rebours commence quand la date du début correspond à celle du systéme
    int duree;
    duree=((fin.tm_min-debut.tm_min)*60)+((fin.tm_hour-debut.tm_hour)*3600)+((fin.tm_mday-debut.tm_mday)*86400);//temps d'attente entre le début et la fin de l'activité
    if(debut.tm_mday==instant_t.tm_mday && debut.tm_hour==instant_t.tm_hour && debut.tm_min==instant_t.tm_min){//Compte à rebour commence si le début correspond à l'instant t
        while(duree!=0){
            duree-=1;
            printf("%d",duree);
            sleep(1);// retire 1 toute les secondes jusqu'à la fin du temps d'attente
        };
        printf("\nfin");
    }
}

int main( ){
    struct tm date_debut;
    struct tm date_fin;
    struct tm instant;//structure de date
    time_t t;//time_t: variable qui indique le nombre de seconde

    //l'utilisateur rentre le début et la fin de l'activité
    validation_date(date_debut);
    validation_date(date_fin);

    //détermine l'instant t de l'ordinateur
    time(&t);//renvoie le nombre de seconde écoulé depuis le 01/01/1970
    instant=*localtime(&t);//localtime: utilise time pour remplir struct tm

    duree_activite(date_debut,date_fin,instant);//minuteur

    return 0;
} 
//source: http://sdz.tdct.org/sdz/ime-h-et-ses-fonctions.html
//        https://koor.fr/C/ctime/ctime.wp