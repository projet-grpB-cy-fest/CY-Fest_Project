#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define couleur(param) printf("\033[%sm",param)

// Structure pour représenter un siège
typedef struct {
    int row;
    int column;
    char status; // 'O' pour libre, 'X' pour réservé
} Seat;

// Structure pour représenter une salle
typedef struct {
    char *name;
    char *band;
    int seatPrices[3]; // Prix pour les sièges avant, du milieu et arrière
    Seat seats[8][8]; // Tableau de sièges pour la salle
} Room;

void initializeRoom(Room *room) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            room->seats[i][j].row = i;
            room->seats[i][j].column = j;
            room->seats[i][j].status = 'O';
        }
    }

    // Réservation aléatoire de certains sièges
    for (int k = 0; k < 10; k++) { // Par exemple, réservation de 10 sièges
        int rand_row = rand() % 8;
        int rand_col = rand() % 8;
        room->seats[rand_row][rand_col].status = 'X';
    }
}

void displayRoom(Room room) {
    printf("Plan de la salle %s :\n", room.name);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (room.seats[i][j].status == 'O') {
                couleur("32"); // Vert pour les sièges libres
                printf("O ");
            } else {
                couleur("31"); // Rouge pour les sièges réservés
                printf("X ");
            }
        }
        printf("\n");
    }
    couleur("0"); // Réinitialisation de la couleur
}

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    printf("Bienvenue dans notre grand festival !\n");
    printf("\n");

    // Définition des salles avec des noms cool et des groupes de musique connus
    Room rooms[] = {
        {"The Electric Arena", "Led Zeppelin", {60, 45, 30}},
        {"The Groove Lounge", "The Rolling Stones", {50, 40, 35}},
        {"The Funky Den", "Queen", {70, 55, 40}},
        {"The Rock Pit", "AC/DC", {65, 50, 35}}
    };

    // Initialisation des salles
    for (int i = 0; i < sizeof(rooms) / sizeof(rooms[0]); i++) {
        initializeRoom(&rooms[i]);
    }

    // Affichage des salles disponibles, des groupes qui y jouent et des prix des billets
    printf("Salles disponibles :\n");
    for (int i = 0; i < sizeof(rooms) / sizeof(rooms[0]); i++) {
        printf("%d. %s - Groupe : %s - Prix du billet (avant/milieu/arriere) : %d/%d/%d euros\n", i + 1, rooms[i].name, rooms[i].band, rooms[i].seatPrices[0], rooms[i].seatPrices[1], rooms[i].seatPrices[2]);
    }

    // Demande au festivalier de choisir une salle
    int choice;
    printf("Dans quelle salle voulez-vous aller ? (1-%d) : ", sizeof(rooms) / sizeof(rooms[0]));
    scanf("%d", &choice);

    // Vérification de la validité du choix de la salle
    if (choice < 1 || choice > sizeof(rooms) / sizeof(rooms[0])) {
        printf("Choix invalide.\n");
        return 1;
    }

    // Le choix de la salle est valide
    Room chosenRoom = rooms[choice - 1];

    // Affichage de la salle choisie
    printf("Vous avez choisi d'aller a %s ou %s joue.\n", chosenRoom.name, chosenRoom.band);

    // Affichage du plan de la salle
    displayRoom(chosenRoom);

    // Demande au festivalier de choisir un siège
    int row, column;
    printf("Quel siege voulez-vous ? (ligne colonne) : ");
    scanf("%d %d", &row, &column);

    // Vérification de la validité du choix de siège
    if (row < 1 || row > 8 || column < 1 || column > 8) {
        printf("Siege invalide.\n");
        return 1;
    }

    // Le choix de siège est valide
    Seat chosenSeat = chosenRoom.seats[row - 1][column - 1];

    // Vérification de la disponibilité du siège
    if (chosenSeat.status == 'X') {
        printf("Ce siege est deja reserve.\n");
        return 1;
    }

    // Réservation du siège
    chosenSeat.status = 'X';

    // Affichage du plan de la salle après réservation du siège
    displayRoom(chosenRoom);

    // Calcul du prix du siège en fonction de son emplacement
    int price;
    if (row == 1 || row == 8) {
        price = chosenRoom.seatPrices[0]; // Siège avant ou arrière
    } else {
        price = chosenRoom.seatPrices[1]; // Siège du milieu
    }
    printf("Le prix du billet pour ce siege est de %d euros.\n", price);

    printf("Merci pour votre achat ! Profitez du concert !\n");

    return 0;
}