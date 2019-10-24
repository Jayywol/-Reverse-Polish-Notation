#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct maillon_t
{
  int valeur;
  struct maillon_t* suivant;
}maillon_t;

//Fonction permettant de verifier si la chaine de caractere est une lettre/mot
int is_alpha(char *str)
{
  int i = 0;
  while (str[i++])
    if (isalpha(str[i]))
      return (1);
  return (0);
}

//Fonction permettant de verifier si la chaine de caractere est un chiffre/nombre
int is_num(char *str)
{
  int i = 0;
  while (str[i++])
    if (isdigit(str[i]))
      return (1);
  return (0);
}

// Methode permettant d'exit avec affichage d'erreur
void my_error()
{
    fprintf(stderr, "Erreur\n");
    exit(1);
}

// Fonction permettant la creation (et allocation de memoire) d'un seul maillon
maillon_t* create_maillon(int valeur, maillon_t* suivant)
{
    maillon_t* maillon = (maillon_t*)malloc(sizeof(maillon_t));
    if (maillon == NULL)
      my_error();
    maillon->valeur = valeur;
    maillon->suivant = suivant;
    return maillon;
}

// Methode permettant de liberer l'allocation de memoire pour le maillon
void free_maillon(maillon_t* maillon)
{
  if (maillon != NULL)
  {
    free_maillon(maillon->suivant);
    free(maillon);
  }
}

// Fonction principale
int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        char instruction[11];
        scanf("%s", instruction);
    }
    printf("answer\n");
    return 0;
}
