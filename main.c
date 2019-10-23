#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
** Structure d'une liste chainee
*/

typedef struct maillon_t
{
  int valeur;
  struct maillon_t* suivant;
}maillon_t;

/*
** Methode permettant d'exit avec affichage d'erreur
*/

void my_error()
{
    fprintf(stderr, "Erreur\n");
    exit(1);
}

/*
** Fonction permettant la creation d'un seul maillon
*/

maillon_t* create_maillon(int valeur, maillon_t* suivant)
{
    maillon_t* maillon = (maillon_t*)malloc(sizeof(maillon_t));
    if (maillon == NULL)
      my_error();
    maillon->valeur = valeur;
    maillon->suivant = suivant;
    return maillon;
}

/*
** Fonction principale (main)
*/

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char instruction[11];
        scanf("%s", instruction);
    }
    printf("answer\n");
    return 0;
}
