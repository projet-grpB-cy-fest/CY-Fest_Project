#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 
#include <errno.h>

//fonction sauvegarde données de créations de salles
void sauvegarde_donnee_salle(char* nom_salle, char* nom_groupe, int n_siege, int prix_avant, int prix_millieu, int prix_arriere, int fosse, struct tm heure_fin){
	//ouverture fichier.txt
	FILE* f=NULL;
	f=fopen("sauvgarde_salle.txt","a+");
	//verifier si le fichier est non null
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	//enregistre les données dans le fichier texte
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%s ",nom_groupe);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d %d %d",prix_avant, prix_millieu, prix_arriere);
	fprintf(f,"%d %d:%d\n",heure_fin.tm_mday,heure_fin.tm_hour,heure_fin.tm_min);
	
	fclose(f); 
}

//fonction sauvegarde données de modification de salles
void sauvegarde_donnee_salle_modif(char* nom_salle, char* nom_groupe, int n_siege, int prix_avant, int prix_millieu, int prix_arriere, int fosse, struct tm heure_fin){
	FILE* f=NULL;
	f=fopen("sauvgarde_salle.txt","a+");
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%s ",nom_groupe);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d %d %d",prix_avant, prix_millieu, prix_arriere);
	fprintf(f,"%d %d:%d\n",heure_fin.tm_mday,heure_fin.tm_hour,heure_fin.tm_min);
	
	fclose(f);
}

//fonction sauvegarde données de reservation siege
void sauvegarde_donnee_reservation(char* nom_salle, char* nom_groupe, int n_siege, int prix, int fosse, struct tm heure_reservation){
	//ouverture fichier.txt
	FILE* f=NULL;
	f=fopen("sauvgarde_reservation.txt","a+");
	//verifier si le fichier est non null
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	//enregistre les données dans le fichier texte
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%s ",nom_groupe);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%f ",prix);
	fprintf(f,"%d %d:%d\n",heure_reservation.tm_mday,heure_reservation.tm_hour,heure_reservation.tm_min);
	
	fclose(f); 
}

