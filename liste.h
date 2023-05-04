void addNoeud(struct noeud** n, int number, double prob);
void createLists(FILE *f, struct noeud *liste[], int fVector[], int numberLine);
void Multiply(struct noeud* liste[], double vecteur[], double Result[],  int numberLine);
double norme(double vecteur[], int numberLine);
void diffVec(double vecteur[], double vecteur2[], double Result[], int numberLine);
void pageRank(int fVector[] , double vecXP[], double vecteur[], float alpha, int numberLine, double result[]);
void vectGenerator(double vecteur[], int numberLine);
void suppSommet(struct noeud *liste[], int* numberLine);