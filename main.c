#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "liste.h"
#include "affichage.h"
#include <time.h>
// free la mémoire
void freeMemory(struct noeud *liste[], int numberLine)
{
    struct noeud *tmp;

    for (int i = 1; i < numberLine + 1; i++)
    {
        while (liste[i] != NULL)
        {
            tmp = liste[i];
            liste[i] = liste[i]->next;
            free(tmp);
        }
    }
}
// main
int main()
{
    srand(time(NULL));
    int score = 0;
    double nor;
    FILE *f = fopen("web1.txt", "r");
    // Variables locales
    int numberArc;  // nombres d'arcs
    int numberLine; // nombres de lignes
    int read;       // variable de lecture

    fscanf(f, "%d", &read); // lit le nombre de lignes du fichier
    numberLine = read;
    printf("numberLine = %d\n", numberLine);
    printf("Début des malloc\n");

    int *fVector = malloc(numberLine * sizeof(double));
    double *vecteur = malloc(numberLine * sizeof(double));
    double *result = malloc(numberLine * sizeof(double));
    double *result2 = malloc(numberLine * sizeof(double));
    double *result3 = malloc(numberLine * sizeof(double));

    vectGenerator(vecteur, numberLine);

    // affichage du vecteur
    // affichageMultiply(vecteur, numberLine);

    struct noeud **liste = malloc(sizeof(struct noeud *) * (read)); // tableau pour stocker nos listes

    // Initialisation à NULL
    for (int i = 1; i < numberLine + 1; i++)
    {
        liste[i] = NULL;
    }

    fscanf(f, "%d", &numberArc); // lecture du nombres d'arcs
    // Création des listes
    createLists(f, liste, fVector, numberLine);

    // affichage
    printf("\naffichage de la structure de matrice\n");
    affichage(liste, numberLine);
    suppSommet(liste, &numberLine);
    printf("\naffichage de la structure de matrice après suppression\n");
    affichage(liste, numberLine);
    printf("\n");
    // affichageVecteurInt(fVector);
    // affichageVecteurInt(fVector, numberLine);
    // Multiplication
    Multiply(liste, vecteur, result, numberLine);
    // Affichage Résultat
    printf("affichage du résultat de xP");
    affichageMultiply(result, numberLine);
    printf("\n");
    // norme
    nor = norme(result, numberLine);
    printf("norme au début %lf\n", nor);
    // Boucle
    for (int i = 0; i < numberLine; i++)
    {
        result[i] = vecteur[i];
    }

    affichageMultiply(result, numberLine);

    do
    {

        Multiply(liste, result, result2, numberLine); // result2 = xP

        pageRank(fVector, result2, result, 0.85, numberLine, result2); // result2 = xG

        diffVec(result2, result, result3, numberLine);
        for (int i = 0; i < numberLine; i++)
        {
            result[i] = result2[i];
        }
        nor = norme(result3, numberLine);
        printf("%lf##\n\n\n", nor);
        score++;

    } while (nor > 0.000000001);

    printf("\nscore: %d\n\n", score);

    // free Mémoire alloué
    freeMemory(liste, numberLine);
    return 0;
}