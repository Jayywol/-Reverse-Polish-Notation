#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct maillon_t
{
  int valeur;
  struct maillon_t* suivant;
}maillon_t;

void my_error()
{
    fprintf(stderr, "Erreur\n");
    exit(1);
}

maillon_t* create_maillon(int valeur, maillon_t* suivant)
{
    maillon_t* maillon = (maillon_t*)malloc(sizeof(maillon_t));
    if (maillon == NULL)
      my_error();
    maillon->valeur = valeur;
    maillon->suivant = suivant;
    return maillon;
}

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
