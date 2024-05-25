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
#define NB_SALLES 300

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
    int creneaux;
} Salle;

void choixmenu();
void choixmenu_mode(int mode);
void afficherListeSalles(Salle salles[], int nb_salles);
int better_scan_int(char* message);
Salle salles_concert[NB_SALLES];

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

//Fonction pour sauvegarder les données de créations de salles
void sauvegarde_donnee_salle(char* nom_salle, char* nom_groupe, int n_siege, int prix_avant, int prix_millieu, int prix_arriere, int fosse, int creneaux){
	//Ouverture  du fichier.txt sauvgarde_salle
	FILE* f=NULL;
	f=fopen("sauvgarde_salle.txt","a+");
	//Verifie si le fichier est non null
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	//Enregistre les données dans le fichier texte
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%s ",nom_groupe);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d %d %d",prix_avant, prix_millieu, prix_arriere);
	fprintf(f,"%d \n",creneaux);
	
	fclose(f); 
}

//Fonction pour sauvegarder les données de modification de salles
void sauvegarde_donnee_salle_modif(char* nom_salle, char* nom_groupe, int n_siege, int prix_avant, int prix_millieu, int prix_arriere, int fosse, int creneaux){
	FILE* f=NULL;
	//Ouverture  du fichier.txt sauvgarde_salle
	f=fopen("sauvgarde_salle.txt","a+");
	//Verifie si le fichier est non null
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	//Enregistre les données dans le fichier texte
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%s ",nom_groupe);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%d %d %d",prix_avant, prix_millieu, prix_arriere);
	fprintf(f,"%d \n",creneaux);
	
	fclose(f);
}

//Fonction pour sauvegarde les données de reservation siege
void sauvegarde_donnee_reservation(char* nom_salle, char* nom_groupe, int n_siege, int prix, int fosse, int creneaux){
	//Ouverture du fichier.txt sauvgarde_reservation
	FILE* f=NULL;
	f=fopen("sauvgarde_reservation.txt","a+");
	//Verifie si le fichier est non null
	if (f==NULL){
    		printf("erreur ouverture fichier: \n");
    		printf("code d'erreur = %d \n", errno );
    		printf("Message d'erreur = %s \n", strerror(errno) );
    		exit(1);
	}
	//Enregistre les données dans le fichier texte
	fprintf(f,"%s ",nom_salle);
	fprintf(f,"%s ",nom_groupe);
	fprintf(f,"%d ",n_siege);
	fprintf(f,"%f ",prix);
	fprintf(f,"%d \n",creneaux);
	
	fclose(f); 
} 




//Fonction pour afficher les créneaux disponible
void afficher_creneaux_disponibles(char* creneaux[], int nb_creneaux) {
    printf("\nCreneaux horaires disponibles pour le 27 juin:\n");
    for (int i = 0; i < nb_creneaux; i++) {
        printf("%d. %s\n", i+1, creneaux[i]);
    }
}

//Fonction pour demander à l'utilisateur quel créneaux il souhaite
int demander_creneaux(){
    int choix;
    //Initialisation des créneaux horaires disponibles
    char* creneaux[] = {"9:00-10:00", "10:00-11:00", "11:00-12:00", "13:00-14:00", "14:00-15:00", "15:00-16:00"};
    int nb_creneaux = sizeof(creneaux) / sizeof(creneaux[0]);

    //Afficher les créneaux horaires disponibles
    afficher_creneaux_disponibles(creneaux, nb_creneaux);

    //Demande à l'utilisateur de choisir un créneau et vérifie si le choix est valide
    do{
        choix=better_scan_int("\nChoisissez un creneau horaire (1-6): ");
    }while(choix<1 || choix>nb_creneaux);
    printf("\nVous avez choisi le creneau horaire %s\n", creneaux[choix - 1]);
    return choix;
}






//Fonction pour initialiser une salle
void initialiserSalle(Salle *salle) {
    int numero = 1;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            salle->sieges[i][j].numero = numero++;
            salle->sieges[i][j].statut = 'O'; //Tous les sièges sont libres au début
            if (i < 3) {
                salle->sieges[i][j].categorie = 'A'; //Première rangée, catégorie A
            } else if (i < 6) {
                salle->sieges[i][j].categorie = 'B'; //Deuxième rangée, catégorie B
            } else {
                salle->sieges[i][j].categorie = 'C'; //Dernière rangée, catégorie C
            }
        }
    }
}

//Fonction pour afficher le plan d'une salle
void afficherSalle(Salle salle, int fosse) {
    printf("Plan de la salle %s :\n", salle.nom_salle);
    printf("     01 02 03 04 05 06 07 08\n");
    printf("    +-----------------------+\n");
    for (int i = 0; i < NB_LIGNES; i++) {
        printf("%02d | ", i + 1);
        for (int j = 0; j < NB_COLONNES; j++) {
            if (fosse == 1 && i < 3) {
                printf("   "); //  un espace vide pour la fosse
            } else {
                if (salle.sieges[i][j].statut == 'O') {
                    if (salle.sieges[i][j].categorie == 'A') {
                        couleur("0;34"); //Bleu pour les sièges de catégorie A
                    } else if (salle.sieges[i][j].categorie == 'B') {
                        couleur("0;33"); //Jaune pour les sièges de catégorie B
                    } else if (salle.sieges[i][j].categorie == 'C') {
                        couleur("0;35"); //Magenta pour les sièges de catégorie C
                    }
                    printf("%02d ", salle.sieges[i][j].numero);
                } else {
                    couleur("0;31"); //Rouge pour les sièges réservés
                    printf("X  "); //Affichage d'une croix rouge pour un siège réservé
                }
            }
            couleur("0"); //Réinitialisation de la couleur
        }
        printf("|\n");
    }
    printf("+----------------------------+\n");
}


//Fonction pour scanner une chaîne de caractères
int better_scan(char *message, char *result, int size) {
    printf("%s", message);
    fgets(result, size, stdin);
    // Remplacer le '\n' final par '\0'
    if (result[strlen(result) - 1] == '\n') {
        result[strlen(result) - 1] = '\0';
    }
    return 1; //Retourner toujours 1, car fgets ne retourne pas d'erreur ici
}

//Fonction pour scanner un entier
int better_scan_int(char *message) {
    int ret_var=0;
    int value=1;
    while(ret_var!=1){
        printf(message);
        ret_var=scanf("%d",&value);
        while(getchar()!='\n'){}
    }
    return value;
}

//Fonction pour calculer le ratio de réservation (Mode Manager)
double calculerRatio(int nb_sieges_reserves, int nb_sieges_total) {
    if (nb_sieges_total == 0) {
        return 0.0; // Pour éviter la division par zéro
    }
    return ((double)nb_sieges_reserves / nb_sieges_total) * 100;
}



//Fonction pour créer une salle (Mode Manager)
Salle constructeur_Salle() {
    Salle salle;
    better_scan("\nSaisir le nom de la salle: ", salle.nom_salle, TAILLE);
    getchar();
    better_scan("\nSaisir le nom du groupe de musique: ", salle.groupe, TAILLE);
    getchar();
    salle.nb_siege = NB_LIGNES * NB_COLONNES; //Fixé à 64 sièges pour toutes les salles
    salle.nb_siege_reserves = 0; //Initialisation du nombre de sièges réservés
    salle.prixSieges[0] = better_scan_int("\nSaisir le prix des sièges avant: ");
    salle.prixSieges[1] = better_scan_int("\nSaisir le prix des sièges milieu: ");
    salle.prixSieges[2] = better_scan_int("\nSaisir le prix des sièges arrière: ");
    do{
        salle.fosse=better_scan_int("\nFosse ? (1-OUI 2-NON): ");
    }while (salle.fosse<1 || salle.fosse>2);
    salle.creneaux=demander_creneaux();
    sauvegarde_donnee_salle(salle.nom_salle, salle.groupe, salle.nb_siege, salle.prixSieges[0], salle.prixSieges[1], salle.prixSieges[2], salle.fosse, salle.creneaux);
    initialiserSalle(&salle);
    return salle;
}

//Fonction pour modifier la configuration d'une salle (Mode Manager)
Salle configuration_Salle(Salle salle) {
    salle.prixSieges[0] = better_scan_int("\nSaisir le prix des sièges avant: ");
    salle.prixSieges[1] = better_scan_int("\nSaisir le prix des sièges milieu: ");
    salle.prixSieges[2] = better_scan_int("\nSaisir le prix des sièges arrière: ");
    do{
        salle.fosse=better_scan_int("\nFosse ? (1-OUI 2-NON): ");
    }while (salle.fosse<1 || salle.fosse>2);
    salle.creneaux=demander_creneaux();
    sauvegarde_donnee_salle_modif(salle.nom_salle, salle.groupe, salle.nb_siege, salle.prixSieges[0], salle.prixSieges[1], salle.prixSieges[2], salle.fosse, salle.creneaux);
    initialiserSalle(&salle);
    return salle;
}

//Fonction pour réserver un siége (Mode Festivalier)
void gestionFestivalier(Salle salles[]) {
    int numeroSiege;
    int j=0;
    //Demande l'heure de reservation 
    printf("\nA quel heure voulez vous assistez aux concerts?:\n");
    int reservation_creneaux=demander_creneaux();
    //Affichage des salles disponibles, des groupes qui y jouent et des prix des billets
    printf("\nSalles disponibles:\n");
    for(int i=0; i<NB_SALLES; i++){
        if(reservation_creneaux==salles[i].creneaux){
            j++;
            if(salles[i].fosse==1){
                printf("\n%d. %s   Groupe: %s   Fosse: OUI   Prix du billet (avant/milieu/arrière): %d/%d/%d euros\n",
               j, salles[i].nom_salle, salles[i].groupe,
               salles[i].prixSieges[0], salles[i].prixSieges[1],
               salles[i].prixSieges[2]);
            }
            else{
                printf("\n%d. %s   Groupe: %s   Fosse: NON   Prix du billet (avant/milieu/arrière): %d/%d/%d euros\n",
               j, salles[i].nom_salle, salles[i].groupe,
               salles[i].prixSieges[0], salles[i].prixSieges[1],
               salles[i].prixSieges[2]);
            }
            
        }
    }
    //Retour au menu festivalier si il y a aucune salle disponible
    if(j==0){
        printf("\nAucune salle disponible, veuillez reéssayer plus tard.\n");
        choixmenu_mode(2);
    }

    //Demande à l'utilisateur de choisir une salle
    int choix=better_scan_int("\nDans quelle salle voulez-vous aller ? : ");
    while (choix < 1 || choix > 4) {
        printf("\nChoix invalide. Veuillez choisir une salle valide: ");
        while (getchar() != '\n')
            ; //Vider le tampon d'entrée
    }
    Salle *salleChoisie = &salles[choix - 1];

    int prix_a_payer = 0; 
    //Affichage de la salle choisie
    afficherSalle(*salleChoisie, salleChoisie->fosse);

    //Réservation de sièges par le festivalier
    int reserver=better_scan_int("\nVoulez-vous réserver un siège ? (1-OUI, 2-NON): ");
        
    while (reserver>2 && reserver<1) {
        printf("\nChoix invalide. Veuillez saisir 1 pour OUI ou 2 pour NON: ");
        while (getchar() != '\n'); //Vider le tampon d'entrée
    }
    //Retour au menu festivalier
    if(reserver==2){
        choixmenu_mode(2);
    }

    do{
        //Demande à l'utilisateur de choisir un siège
        do{
            printf("\nQuel siège voulez-vous ? (01-64): ");
            scanf("%d",&numeroSiege);
        } while (numeroSiege<1||numeroSiege>64);

        //Conversion du numéro de siège en indices de ligne et de colonne
        int ligne = (numeroSiege - 1) / 8;
        int colonne = (numeroSiege - 1) % 8;

        //Vérification de la disponibilité du siège
        if (salleChoisie->sieges[ligne][colonne].statut == 'X') {
            printf("\nCe siège est déjà réservé.\n");
        } 
        else {
            //Réservation du siège
            salleChoisie->sieges[ligne][colonne].statut = 'X';
            salleChoisie->nb_siege_reserves++;

            //Calcul du prix en fonction de la catégorie
            if (salleChoisie->sieges[ligne][colonne].categorie == 'A') {
                //Si la salle choisi a une fosse, le prix des siéges avant double
                if(salleChoisie->fosse==1){
                    prix_a_payer += 2*salleChoisie->prixSieges[0];
                }
                else{
                    prix_a_payer += salleChoisie->prixSieges[0];
                }
            } 
            else if (salleChoisie->sieges[ligne][colonne].categorie == 'B') {
                prix_a_payer += salleChoisie->prixSieges[1];
            } 
            else {
                prix_a_payer += salleChoisie->prixSieges[2];
            }

            //Affichage du plan de la salle après réservation du siège
            afficherSalle(*salleChoisie, salleChoisie->fosse);

            //Demande si l'utilisateur veut réserver un autre siège
            do{
                reserver=better_scan_int("\nVoulez-vous réserver un autre siège ? (1-OUI, 2-NON): ");
            }while (reserver != 2 && reserver != 1);
        }
    }while(reserver!=2);

    //Affichage du prix total à payer
    printf("\nLe prix total à payer est de %d euros.\n", prix_a_payer);
    
    sauvegarde_donnee_reservation(salleChoisie->nom_salle, salleChoisie->groupe, numeroSiege, prix_a_payer, salleChoisie->fosse, salleChoisie->creneaux);
    
    //Remerciement 
    printf("\nMerci pour votre réservation !\n");
}

void initialiserlisteSalles() {
    for (int i = 0; i < NB_SALLES; i++) {
        strcpy(salles_concert[i].nom_salle, ""); // Initialiser les noms de salle à une chaîne vide
    }
}

//Fonction pour afficher la liste des salles créées
void afficherListeSalles(Salle salles[], int nb_salles) {
    printf("\nListe des salles créées:\n");
    for (int i = 0; i < nb_salles; i++) {
        if (strcmp(salles[i].nom_salle, "") != 0) {
            printf("%d. %s\n", i + 1, salles[i].nom_salle);
        }
    }
}

//Fonction pour afficher le menu selon le mode choisi
void choixmenu_mode(int mode){
    int choix_manager,choix_festivalier,choix_salles,i=0;
    //Mode manager
    if(mode==1){

        //Menu du mode manager
        printf("\nMode MANAGER: \n1-Creer une salle \n2-Modifier la configuration d'une salle \n3-Etat de la salle \n4-Retour au menu principal \n");
    
        //Boucle qui vérifie si la valeur entrée est correct
        do{
            choix_manager=better_scan_int("\n\nEntrez votre choix (1-4): ");
        }while(choix_manager<1||choix_manager>4); 
    
        //Boucle switch case pour chaque valeur entrez
        switch(choix_manager){
            case 4:
                //Retour au menu principale
                printf("\nRetour au menu principale\n");
                choixmenu();
            break;

            case 1:
                //Créer de salle
                printf("\nCréation de salle: \n");
                //Création d'une salle, appele de la fonction constructeur_Salle du programme fnct_principal.c
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") == 0) {
                        printf("\nCréation de la salle %d\n", i +1);
                        salles_concert[i] = constructeur_Salle();
                        break;
                    }
                }
                
                afficherListeSalles(salles_concert, NB_SALLES);
                //Retour au menu manager 
                choixmenu_mode(1);
                
            break;

            case 2:
                //Configurer salle
                printf("\nConfiguration salle: \n");
                //Configuration d'une salle, appele de la fonction configuration_Salle du programme fnct_principal.c
                afficherListeSalles(salles_concert,NB_SALLES);
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") != 0){
                        do{
                            choix_salles=better_scan_int("\nQuelle salle voulez-vous modifier: "); 
                        }while(choix_salles<=0||choix_salles>NB_SALLES);
                        Salle salle_modifier=configuration_Salle(salles_concert[choix_salles-1]);
                        salles_concert[choix_salles-1]=salle_modifier;
                        //Retour au menu manager 
                        choixmenu_mode(1); 
                    }
                    //Retour au menu manager
                    else{
                        printf("\nAucune salle encore créée, veuillez en créer une\n"); 
                        choixmenu_mode(1);
                    }
                }
                
                         
            break;

            case 3:
                //Ratio salle
                printf("\nÉtat salle: \n");
                //Ratio des salles créées (nombre de siége réservé sur nombre de siége qui est de 64), appele de la fonction calculerRatio du programme fnct_principal.c
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") != 0){
                        printf("%d) %s: %.2f%%\n", i+1, salles_concert[i].nom_salle, calculerRatio(salles_concert[i].nb_siege_reserves, salles_concert[i].nb_siege));
                    }
                    else{
                        printf("\nAucune salle encore créée, veuillez en créer une\n");
                        //Retour au menu manager
                        choixmenu_mode(1);
                    }
                }
                //Retour au menu manager
                choixmenu_mode(1);
            break;

            default:
                //Message d'erreur
                printf("\nerreur saisie\n");
                //Retour au menu manager
                choixmenu_mode(1);
            break;
        }
    }

    //Mode festivalier:
    if(mode==2){
       //Menu du mode festivalier
        printf("\nMenu FESTIVALIER: \n1-Réservation \n2-Retour au menu principal \n");
    
        //Boucle qui vérifie si la valeur entrez est correct
        do{
            choix_festivalier=better_scan_int("\n\nEntrez votre choix (1-2): ");
        }while(choix_festivalier<1||choix_festivalier>2);

        //Réservation d'un siége, appele de la fonction gestionFestivalier du programme fnct_principal.c
        if(choix_festivalier==1){
            printf("\nRéservation: \n");
            gestionFestivalier(salles_concert);
            //Retour au menu manager
            choixmenu_mode(2);
        }
        //Retour au menu principale
        else if(choix_festivalier==2){
            
            printf("\nRetour au menu principale\n");
            choixmenu();
        }
    }

    //Quitter le programme:
    if(mode==3){
        printf("\nLe feu d'artifice va commencer !\n");
    
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
 
        printf("\n  %s Aurevoir %s   \n","\U0001f386","\U0001f386");
        //Fin du programme
        exit(1);
        
    }
    exit(1);
}

//Fonction pour afficher le menu principale
void choixmenu(){
    int mode;
 
    //Entrez le mode:
    printf("\nMODE: \n1-MANAGER \n2-FESTIVALIER \n3-QUITTER\n");

    //Boucle qui vérifie si la valeur entrez est correct
    do{
        mode=better_scan_int("\n\nEntrez votre choix (1-3): ");
    }while(mode<1||mode>3);

    //Accéder au mode choisi
    choixmenu_mode(mode);
}


int main(){
    afficherMessageBienvenue();
    choixmenu();

    return 0;
}