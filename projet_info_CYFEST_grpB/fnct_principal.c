#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
//Appele fichier.h du programme fnct_heure.c et fnct_sauv_donnee.c
#include "entete_heure.h"
#include "entete_sauv_donnee.h"

//Couleur
#define couleur(param) printf("\033[%sm", param)
#define TAILLE 50
#define NB_LIGNES 8
#define NB_COLONNES 8
#define NB_SALLES 3

//Structure pour représenter un siège
typedef struct {
    int numero;
    char statut; //'O' pour libre, 'X' pour réservé
    char categorie;
} Siege;

//Structure pour représenter une salle
typedef struct {
    char nom_salle[TAILLE];
    char groupe[TAILLE];
    int nb_siege;
    int nb_siege_reserves;
    int prixSieges[3];  //Prix pour les sièges avant, milieu et arrière
    Siege sieges[NB_LIGNES][NB_COLONNES]; //Tableau de sièges pour la salle
    int fosse;
    int creneaux;
} Salle;

//Fonction pour initialiser une salle
void initialiserSalle(Salle *salle) {
    int numero = 1;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            salle->sieges[i][j].numero = numero++;
            salle->sieges[i][j].statut = 'O'; //Tous les sièges sont libres au début
            if (i < 3) {
                salle->sieges[i][j].categorie = 'A'; //Première rangée, catégorie A
            } 
            else if (i < 6) {
                salle->sieges[i][j].categorie = 'B'; //Deuxième rangée, catégorie B
            } 
            else {
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
            if (fosse == 0 && i < 3) {
                printf("   "); //  un espace vide pour la fosse
            } 
            else {
                if (salle.sieges[i][j].statut == 'O') {
                    if (salle.sieges[i][j].categorie == 'A') {
                        couleur("0;34"); //Bleu pour les sièges de catégorie A
                    } 
                    else if (salle.sieges[i][j].categorie == 'B') {
                        couleur("0;33"); //Jaune pour les sièges de catégorie B
                    } 
                    else if (salle.sieges[i][j].categorie == 'C') {
                        couleur("0;35"); //Magenta pour les sièges de catégorie C
                    }
                    printf("%02d ", salle.sieges[i][j].numero);
                } 
                else {
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

//Fonction pour afficher le ratio de réservation pour chaque salle (Mode Manager)
void afficherRatioReservation(Salle salles[], int nb_salles) {
    printf("\nRatio de réservation pour chaque salle:\n");

    for (int i = 0; i < nb_salles; i++) {
        double ratio = calculerRatio(salles[i].nb_siege_reserves, salles[i].nb_siege);
        printf("%s : %.2f%%\n", salles[i].nom_salle, ratio);
    }
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
    //Si aucune salle est disponible, retour au menu festivalier
    if(j==0){
        printf("\nAucune salle disponible, veuillez reéssayer plus tard.\n");
        return ;
    }

    //Demande à l'utilisateur de choisir une salle
    int choix=better_scan_int("\nDans quelle salle voulez-vous aller ? (1-3): ");
    while (choix < 1 || choix > 3) {
        printf("\nChoix invalide. Veuillez choisir une salle valide (1-3): ");
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

    //Retour au menu festivalier si l'utilisateur ne veut pas réserver
    if(reserver==2){
        return ;
    }

    else if(reserver == 1) {
        //Demande à l'utilisateur de choisir un siège
        do{
            numeroSiege==better_scan_int("\nQuel siège voulez-vous ? (01-64): ");
        } while (numeroSiege < 1 || numeroSiege > 64);

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
                prix_a_payer += salleChoisie->prixSieges[0];
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
                reserver=better_scan_int("\nVoulez-vous réserver un autre siège ? (1-OUI, 0-NON): ");
            }while (reserver != 0 && reserver != 1);
        }
    }

    //Affichage du prix total à payer
    if (salleChoisie->fosse == 0) {
        //L'utilisateur choisit la fosse
        prix_a_payer = 2 * salleChoisie->prixSieges[0];
        printf("\nVous avez choisi la fosse. Le prix à payer est de %d euros.\n", prix_a_payer);
    }
    else{
        printf("\nLe prix total à payer est de %d euros.\n", prix_a_payer);
    }

    sauvegarde_donnee_reservation(salleChoisie->nom_salle, salleChoisie->groupe, numeroSiege, prix_a_payer, salleChoisie->fosse, salleChoisie->creneaux);
    
    //Remerciement 
    printf("\nMerci pour votre réservation !\n");
}