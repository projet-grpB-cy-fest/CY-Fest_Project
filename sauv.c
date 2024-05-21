#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>


void sauvegarde_donnee(char* nom_salle, int n_siege, int activite){
	FILE* f=NULL;
	f=fopen("sauvgarde_salle.txt","a+");
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d\n",activite);
	
	fclose(f);
}
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
