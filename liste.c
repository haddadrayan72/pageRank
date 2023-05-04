#include <stdlib.h>
#include "stdio.h"
#include <math.h>
#include "structure.h"
#include <time.h>

// Fait la différence entre vecteur - vecteur2 = Result
void diffVec(double *vecteur, double *vecteur2, double *Result, int numberLine)
{

    for (int i = 0; i < numberLine; i++)
    {
        Result[i] = vecteur[i] - vecteur2[i];
    }
}

// calcule la norme du vecteur
double norme(double *vecteur, int numberLine)
{
    double norme = 0;
    for (int i = 0; i < numberLine; i++)
    {
        // printf("vecteur i :%lf\n", vecteur[i]);
        norme = norme + vecteur[i] * vecteur[i];
        // printf("norme %d: %lf\n\n", i, norme);
    }
    return sqrt(norme);
}

// multiplication d'une matrice "liste" avec vecteur, résultat dans Result
void Multiply(struct noeud *liste[], double *vecteur, double *Result, int numberLine)
{
    for (int i = 0; i < numberLine; i++)
    {
        Result[i] = 0;
    }

    for (int i = 0; i < numberLine; i++)
    {
        struct noeud *current = liste[i + 1];

        while (current != NULL)
        {
            Result[i] = Result[i] + current->prob * vecteur[current->number - 1];
            current = current->next;
        }
    }
}

// ajout d'un noeud dans la liste chainé n
void addNoeud(struct noeud **n, int number, double prob)
{
    if (*n == NULL)
    {
        *n = malloc(sizeof(struct noeud));
        (*n)->number = number;
        (*n)->prob = prob;
        (*n)->next = NULL;
    }
    else
    {
        struct noeud *nouveau = malloc(sizeof(struct noeud));
        nouveau->number = number;
        nouveau->prob = prob;
        nouveau->next = *n;
        *n = nouveau;
    }
}
// crée les listes chainé représentant une matrice
void createLists(FILE *f, struct noeud *liste[], int *fVector, int numberLine)
{
    int read;
    for (int i = 1; i < numberLine + 1; i++)
    {
        int numLigne;
        int number;
        double prob;
        fscanf(f, "%d", &numLigne); // lit le numéro de la ligne

        fscanf(f, "%d", &read); // lit le nombre d'arc
        if (read == 0)
            fVector[numLigne - 1] = 1;
        else
            fVector[numLigne - 1] = 0;

        for (int i = 0; i < read; i++)
        {
            fscanf(f, "%d", &number);
            fscanf(f, "%lf", &prob);
            addNoeud(&liste[number], numLigne, prob);
        }
    }
}

void pageRank(int fVector[], double vecXP[], double vecteur[], float alpha, int numberLine, double result[])
{
    double *e = malloc(sizeof(double) * numberLine);
    double *e2 = malloc(sizeof(double) * numberLine);
    double fe = 0;
    for (int i = 0; i < numberLine; i++)
    {
        vecXP[i] = vecXP[i] * alpha; // vecXP = alpha*XP
    }

    // ft * e
    for (int i = 0; i < numberLine; i++)
    {
        fe += fVector[i]; //
    }
    // printf("xf =%lf\n", xf);
    //(xf*alpha) / N
    fe = fe * alpha;
    fe = fe / (double)numberLine;

    for (int i = 0; i < numberLine; i++)
    {
        e[i] = fe * vecteur[i];
        e2[i] = (1 - alpha) / (double)numberLine;
        result[i] = vecXP[i] + e[i] + e2[i];
    }
}
/*

void vecGenerator(double vecteur[], int numberLine){

    float x;
    for (int i = 0; i < numberLine; i++) {

        x = 0.1 + (float)rand() / ((float)RAND_MAX/(0.2-0.1));// generation d'un flottant aleatoire entre min = 0.1 et max = 0,2
        vecteur[i] = x;
    }
    // affichage du vecteur pour verification
    for (int i = 0; i < numberLine; i++) {

        printf("%lf   ",vecteur[i]);
    }

}*/
/**
 * @brief fonction qui genere une vecteur avec les valeur [1/numberline]
 *
 * @param vecteur
 * @param numberLine
 */
void vectGenerator(double *vecteur, int numberLine)
{

    for (int i = 0; i < numberLine; i++)
    {
        vecteur[i] = 1 / (double)numberLine;
        // printf("%lf\n", vecteur[i]);
    }
}

void suppSommet(struct noeud *liste[], int *numberLine)
{

    int random = rand() % *numberLine;
    printf("Le random est %d\n", random);
    struct noeud *deleted = liste[random];
    liste[random] = liste[*numberLine - 1];

    struct noeud *current;
    struct noeud *previous = NULL;
    for (int i = 0; i < *numberLine - 1; i++)
    {
        int debut = 0;
        current = liste[i];

        while (current != NULL)
        {
            if (current->number == random + 1)
            {
                if (debut == 0)
                {
                    liste[i] = current->next;
                    current = liste[i];
                }
                else
                {
                    previous->next = current->next;
                    current = previous;
                    debut = 1;
                }
            }
            if (current->number == *numberLine)
            {
                current->number = random + 1;
            }
            previous = current;
            current = current->next;
        }
    }

    *numberLine = *numberLine - 1;
    // free(deleted);
}