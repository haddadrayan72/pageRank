#include "structure.h"
#include "stdio.h"
#include <stdlib.h>

//affichage d'une matrice (version liste chainée)
void affichage(struct noeud *liste[], int numberLine)
{
    
    for (int i = 1; i < numberLine + 1; i++)
    {
        struct noeud *current = liste[i];
        printf("Node %d : ", i);

        while (current != NULL)
        {
            printf(" <-%d ", current->number);
            printf("[%lf] ", current->prob);
            printf("\b");
            current = current->next;
        }
        printf("\n");
    }
}

//affichage du résultat d'une multiplication
//affichage du vecteur
void affichageMultiply(double* vecteur, int numberLine)
{
    printf("\n\n Vecteur Résultant: \n");
    printf("{");
    for (int i = 0; i < numberLine - 1; i++)
    {
        printf("%lf, ", vecteur[i]);
    }
    printf("%lf}\n", vecteur[numberLine - 1]);
}

//affichage du vecteur
void affichageVecteurInt(int* vecteur, int numberLine)
{
    printf("\n\n Vecteur Résultant: \n");
    printf("{");
    for (int i = 0; i < numberLine - 1; i++)
    {
        printf("%d, ", vecteur[i]);
    }
    printf("%d}\n", vecteur[numberLine - 1]);
}