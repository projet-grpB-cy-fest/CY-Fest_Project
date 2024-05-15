#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int nbsiege;
    float prix;
    int numero;
    int nbsiege_indispo;
} Siege;

typedef struct {
    int nom[50];
    Siege categorieA;
    Siege categorieB;
    Siege categorieC;
} Salle;


void configuration_salle(Salle *salle) {
    printf("Entrez le nombre de sièges pour la catégorie A : ");
    scanf("%d", &salle->categorieA.nbsiege);
    printf("Entrez le prix par siège pour la catégorie A : ");
    scanf("%f", &salle->categorieA.prix);

    printf("Entrez le nombre de sièges pour la catégorie B : ");
    scanf("%d", &salle->categorieB.nbsiege);
    printf("Entrez le prix par siège pour la catégorie B : ");
    scanf("%f", &salle->categorieB.prix);

  printf("Entrez le nombre de sièges pour la catégorie C : ");
      scanf("%d", &salle->categorieC.nbsiege);
      printf("Entrez le prix par siège pour la catégorie C : ");
      scanf("%f", &salle->categorieC.prix);
  }


float calculerRatio(Salle salle){
    return (salle.categorieA.nbsiege_indispo + salle.categorieB.nbsiege_indispo + salle.categorieC.nbsiege_indispo)/(salle.categorieA.nbsiege + salle.categorieB.nbsiege + salle.categorieC.nbsiege);
}

int main(){
Salle s;
configuration_salle(s);
calculerRatio(s);
return 0;
}
