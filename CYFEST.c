#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#define couleur(param) printf("\033[%sm", param)
#define TAILLE 50
#define NB_LIGNES 8
#define NB_COLONNES 8

// Structure pour représenter un siège
typedef struct {
    int numero;
    char statut; // 'O' pour libre, 'X' pour réservé
    char categorie;
} Siege;

// Structure pour représenter une salle
typedef struct {
    char nom_salle[TAILLE];
    char groupe[TAILLE];
    int nb_siege;
    int nb_siege_reserves;
    int prixSieges[3];  // Prix pour les sièges avant, milieu et arrière
    Siege sieges[NB_LIGNES][NB_COLONNES]; // Tableau de sièges pour la salle
    int fosse;
    struct tm heure_fin;
} Salle;

// Fonction pour afficher un message de bienvenue
void afficherMessageBienvenue() {
    couleur("1;35"); // Violet et gras
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*  _       __     __                             *\n");
    printf("* | |     / /__  / /________  ____ ___  ___      *\n");
    printf("* | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\     *\n");
    printf("* | |/ |/ /  __/ / /__/ /_/ / / / / /  __/     *\n");
    printf("* |__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/      *\n");
    printf("*                                                *\n");
    printf("*      Bienvenue dans notre grand festival !     *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    couleur("0"); // Réinitialisation de la couleur
}

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

struct tm constructeur_date(struct tm date){//fonction qui demande à l'utilisateur le jour, l'heure et la minute de la fin du concert
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

struct tm validation_date( ){//fonction afficher pour l'utilisateur, s'assure si le choix de l'utilisateur lui convient
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

int duree_activite(struct tm fin, struct tm instant_t){//Indique la fin des reservation, retourne 1 si le concert est fini/commencé, dans ce cas aucune réservation n'est possible puisque le concert est fini/commencé. Sinon retourne 0.
//instant_t pourrait étre la valeur entrez par l'utilisateur pour indiquer l'heure de reservation 
    if(instant_t.tm_mday>=fin.tm_mday){
        if(instant_t.tm_hour>=fin.tm_hour){
            if(instant_t.tm_min>=fin.tm_min){
                return 1;
            }
        }
    }
    return 0;

}

// Fonction pour initialiser une salle
void initialiserSalle(Salle *salle) {
    int numero = 1;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            salle->sieges[i][j].numero = numero++;
            salle->sieges[i][j].statut = 'O'; // Tous les sièges sont libres au début
            if (i < 3) {
                salle->sieges[i][j].categorie = 'A'; // Première rangée, catégorie A
            } else if (i < 6) {
                salle->sieges[i][j].categorie = 'B'; // Deuxième rangée, catégorie B
            } else {
                salle->sieges[i][j].categorie = 'C'; // Dernière rangée, catégorie C
            }
        }
    }
}

// Fonction pour afficher le plan d'une salle
void afficherSalle(Salle salle, int fosse) {
    printf("Plan de la salle %s :\n", salle.nom_salle);
    printf("     01 02 03 04 05 06 07 08\n");
    printf("    +-----------------------+\n");
    for (int i = 0; i < NB_LIGNES; i++) {
        printf("%02d | ", i + 1);
        for (int j = 0; j < NB_COLONNES; j++) {
            if (fosse == 0 && i < 3) {
                printf("   "); // Affiche un espace vide pour la fosse
            } else {
                if (salle.sieges[i][j].statut == 'O') {
                    if (salle.sieges[i][j].categorie == 'A') {
                        couleur("0;34"); // Bleu pour les sièges de catégorie A
                    } else if (salle.sieges[i][j].categorie == 'B') {
                        couleur("0;33"); // Jaune pour les sièges de catégorie B
                    } else if (salle.sieges[i][j].categorie == 'C') {
                        couleur("0;35"); // Magenta pour les sièges de catégorie C
                    }
                    printf("%02d ", salle.sieges[i][j].numero);
                } else {
                    couleur("0;31"); // Rouge pour les sièges réservés
                    printf("X  "); // Affichage d'une croix rouge pour un siège réservé
                }
            }
            couleur("0"); // Réinitialisation de la couleur
        }
        printf("|\n");
    }
    printf("+----------------------------+\n");
}

// Fonction pour scanner une chaîne de caractères
int better_scan(char *message, char *result, int size) {
    printf("%s", message);
    fgets(result, size, stdin);
    // Remplacer le '\n' final par '\0'
    if (result[strlen(result) - 1] == '\n') {
        result[strlen(result) - 1] = '\0';
    }
    return 1; // Retourner toujours 1, car fgets ne retourne pas d'erreur ici
}

// Fonction pour scanner un entier
int better_scan_int(char *message) {
    int value;
    printf("%s", message);
    scanf("%d", &value);
    while (getchar() != '\n')
        ; // Vider le buffer d'entrée
    return value;
}

// Fonction pour calculer le ratio de réservation
double calculerRatio(int nb_sieges_reserves, int nb_sieges_total) {
    return (double)nb_sieges_reserves / nb_sieges_total * 100;
}

// Fonction pour créer une salle (Mode Manager)
Salle constructeur_Salle() {
    Salle salle;
    better_scan("Saisir le nom de la salle : ", salle.nom_salle, TAILLE);
    better_scan("Saisir le nom du groupe de musique : ", salle.groupe, TAILLE);
    salle.nb_siege = NB_LIGNES * NB_COLONNES; // Fixé à 64 sièges pour toutes les salles
    salle.nb_siege_reserves = 0; // Initialisation du nombre de sièges réservés
    salle.prixSieges[0] = better_scan_int("Saisir le prix des sièges avant : ");
    salle.prixSieges[1] = better_scan_int("Saisir le prix des sièges milieu : ");
    salle.prixSieges[2] = better_scan_int("Saisir le prix des sièges arrière : ");
    printf("\nFosse ? (1-OUI 2-NON) : ");
    scanf("%d",&salle.fosse);
    while (salle.fosse <1 || salle.fosse>2) {
        printf("Choix invalide. Veuillez saisir 1 ou 2 : ");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
    }
    printf("\nFin du concert:\n");
    salle.heure_fin=validation_date();
    sauvegarde_donnee_salle(salle.nom_salle, salle.groupe, salle.nb_siege, salle.prixSieges[0], salle.prixSieges[1], salle.prixSieges[2], salle.fosse, salle.heure_fin);
    initialiserSalle(&salle);
    return salle;
}

//Fonction pour modifier la configuration d'une salle
Salle configuration_Salle(Salle *salle) {
    salle->prixSieges[0] = better_scan_int("Saisir le prix des sièges avant : ");
    salle->prixSieges[1] = better_scan_int("Saisir le prix des sièges milieu : ");
    salle->prixSieges[2] = better_scan_int("Saisir le prix des sièges arrière : ");
    printf("\nFosse ? (1-OUI 2-NON) : ");
    printf("\nFosse ? (1-OUI 2-NON) : ");
    scanf("%d",&salle->fosse);
    while (salle->fosse <1 || salle->fosse>2) {
        printf("Choix invalide. Veuillez saisir 1 ou 2 : ");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
    }
    printf("\nFin du concert:\n");
    salle->heure_fin=validation_date();
    sauvegarde_donnee_salle_modif(salle->nom_salle, salle->groupe, salle->nb_siege, salle->prixSieges[0], salle->prixSieges[1], salle->prixSieges[2], salle->fosse, salle->heure_fin);
    initialiserSalle(salle);
    return *salle;
}

void gestionFestivalier(Salle salles[]) {
    int numeroSiege;
    int j=0;
    //Demande l'heure de reservation 
    printf("\nA quel heure voulez vous assistez aux concerts? :\n");
    struct tm heure_reservation=validation_date();
    // Affichage des salles disponibles, des groupes qui y jouent et des prix des billets
    printf("Salles disponibles :\n");
    for(int i=0; i<100; i++){
        if(duree_activite(salles[i].heure_fin, heure_reservation)==0){
            j++;
            if(salles[i].fosse==1){
                printf("%d. %s\n   Groupe : %s\n   Fosse : OUI\n   Prix du billet (avant/milieu/arrière) : %d/%d/%d euros\n\n",
               j, salles[i].nom_salle, salles[i].groupe,
               salles[i].prixSieges[0], salles[i].prixSieges[1],
               salles[i].prixSieges[2]);
            }
            else{
                printf("%d. %s\n   Groupe : %s\n   Fosse : OUI\n   Prix du billet (avant/milieu/arrière) : %d/%d/%d euros\n\n",
               j, salles[i].nom_salle, salles[i].groupe,
               salles[i].prixSieges[0], salles[i].prixSieges[1],
               salles[i].prixSieges[2]);
            }
            
        }
    }

    // Demande à l'utilisateur de choisir une salle
    int choix;
    printf("Dans quelle salle voulez-vous aller ? (1-4) : ");
    while (scanf("%d", &choix) != 1 || choix < 1 || choix > 4) {
        printf("Choix invalide. Veuillez choisir une salle valide (1-4) : ");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
    }
    Salle *salleChoisie = &salles[choix - 1];

    int prix_a_payer = 0;
    if (salleChoisie->fosse == 0) {
        // L'utilisateur choisit la fosse
        prix_a_payer = 2 * salleChoisie->prixSieges[0];
        printf("Vous avez choisi la fosse. Le prix à payer est de %d euros.\n", prix_a_payer);
    } else {
        // Affichage de la salle choisie
        afficherSalle(*salleChoisie, salleChoisie->fosse);

        // Réservation de sièges par le festivalier
        int reserver;
        int numeroSiege;
        printf("Voulez-vous réserver un siège ? (1-OUI, 2-NON) : ");
        while (scanf("%d", &reserver) != 1 || (reserver != 2 && reserver != 1)) {
            printf("Choix invalide. Veuillez saisir 1 pour OUI ou 2 pour NON : ");
            while (getchar() != '\n')
                ; // Vider le tampon d'entrée
        }

        while (reserver == 1) {
            // Demande à l'utilisateur de choisir un siège
            
            printf("Quel siège voulez-vous ? (01-64) : ");
            while (scanf("%d", &numeroSiege) != 1 || numeroSiege < 1 || numeroSiege > 64) {
                printf("Siège invalide. Veuillez choisir un siège valide : ");
                while (getchar() != '\n')
                    ; // Vider le tampon d'entrée
            }

            // Conversion du numéro de siège en indices de ligne et de colonne
            int ligne = (numeroSiege - 1) / 8;
            int colonne = (numeroSiege - 1) % 8;

            // Vérification de la disponibilité du siège
            if (salleChoisie->sieges[ligne][colonne].statut == 'X') {
                printf("Ce siège est déjà réservé.\n");
            } else {
                // Réservation du siège
                salleChoisie->sieges[ligne][colonne].statut = 'X';
                salleChoisie->nb_siege_reserves++;

                // Calcul du prix en fonction de la catégorie
                if (salleChoisie->sieges[ligne][colonne].categorie == 'A') {
                    prix_a_payer += salleChoisie->prixSieges[0];
                } else if (salleChoisie->sieges[ligne][colonne].categorie == 'B') {
                    prix_a_payer += salleChoisie->prixSieges[1];
                } else {
                    prix_a_payer += salleChoisie->prixSieges[2];
                }

                // Affichage du plan de la salle après réservation du siège
                afficherSalle(*salleChoisie, salleChoisie->fosse);

                // Demande si l'utilisateur veut réserver un autre siège
                printf("Voulez-vous réserver un autre siège ? (1-OUI, 0-NON) : ");
                while (scanf("%d", &reserver) != 1 || (reserver != 0 && reserver != 1)) {
                    printf("Choix invalide. Veuillez saisir 1 pour OUI ou 0 pour NON : ");
                    while (getchar() != '\n')
                        ; // Vider le tampon d'entrée
                }
            }
        }

        // Affichage du prix total à payer
        printf("Le prix total à payer est de %d euros.\n", prix_a_payer);
    }
    sauvegarde_donnee_reservation(salleChoisie->nom_salle, salleChoisie->groupe, numeroSiege, prix_a_payer, salleChoisie->fosse, heure_reservation);
    
    // Remerciement
    printf("Merci pour votre réservation !\n");
}

int choixmenu(){
    int mode,choix_manager,choix_festivalier,choix_salles,i=0,j=0;
    Salle *salles_concert=malloc(100*sizeof(Salle));

    if(salles_concert==NULL){
        printf("\nerreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
 
//entrez le mode:
    printf("\n1-MANAGER \n2-FESTIVALIER \n3-QUITTER");

//boucle vérifie si la valeur entrez est correct
    do{
        printf("\n\nEntrez votre choix: ");
        scanf("%d",&mode);
    }while(mode<1||mode>3);

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
                if(j>100){
                    printf("\nplus de salle disponible\n");
                    choixmenu();
                }
                salles_concert[j-1]=constructeur_Salle();
                choixmenu();
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
                *(salles_concert+(choix_salles-1))=configuration_Salle(&salles_concert[choix_salles-1]);            
                choixmenu();
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
                choixmenu();
            break;

            default:
                //message d'erreur ou cas ou
                printf("\nerreur saisie");
                choixmenu();
            break;
        }
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
            choixmenu();
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
        free(salles_concert);
        return 1;
    }
    
}

int main(){
    afficherMessageBienvenue();
    if(choixmenu()==1){
        printf("\n");
    }

    return 0;
}
