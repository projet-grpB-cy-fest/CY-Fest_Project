#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TAILLE 50

typedef enum { 
    concert,
    jeux,
    cirque,
    art,
    artifice
} Activite;

typedef struct {
    char nom_salle[TAILLE];
    int nb_siege;
    Activite activite;
} Salle;


int better_scan(char *message, char *result, int size) {
    printf("%s", message);
    fgets(result, size, stdin);
    // Remplacer le '\n' final par '\0'
    if (result[strlen(result) - 1] == '\n') {
        result[strlen(result) - 1] = '\0';
    }
    return 1; // Retourner toujours 1, car fgets ne retourne pas d'erreur ici
}
int better_scan_int(char *message) {
    int value;
    printf("%s", message);
    scanf("%d", &value);
    while(getchar() != '\n'); // Vider le buffer d'entrée
    return value;
}

Activite string_to_activite(char *str){
    if (strcmp(str, "concert") == 0) return concert;
    else if (strcmp(str, "jeux") == 0) return jeux;
    else if (strcmp(str, "cirque") == 0) return cirque;
    else if (strcmp(str, "art") == 0) return art;
    else if (strcmp(str, "artifice") == 0) return artifice;
    else return -1; // Valeur d'activité non valide
}

Salle constructeur_Salle() {
    Salle salle;
    better_scan("Saisir le nom de la salle : ", salle.nom_salle, TAILLE);
    salle.nb_siege = better_scan_int("Saisir le nombre de sieges de la salle : ");
    char activite_str[TAILLE];
    better_scan("Saisir l'activite souhaitee : ", activite_str, TAILLE);
    salle.activite = string_to_activite(activite_str);
    return salle;
}

int main() {
Salle ma_salle = constructeur_Salle();
printf("\nNom de la salle : %s\n", ma_salle.nom_salle);
printf("Nombre de sieges : %d\n", ma_salle.nb_siege);
printf("Activite : %d\n", ma_salle.activite);

struct tm date;

date=constructeur_date(date);

return 0;
}
