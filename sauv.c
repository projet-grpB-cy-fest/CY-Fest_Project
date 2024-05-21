#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>

//fonction sauvegarde données de créations de salles et reservation
void sauvegarde_donnee(char* nom_salle, int n_siege, int activite){
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
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d\n",activite);
	
	fclose(f);
}

//fonction sauvegarde données de modification de salles
void sauvegarde_donnee_modif(char* nom_salle, int n_siege, int activite){
	FILE* f=NULL;
	f=fopen("sauvgarde_salle.txt","a+");
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	
	fprintf(f,"modif: %s ",nom_salle);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d\n",activite);
	
	fclose(f);
}
