#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct maillon_t
{
  int valeur;
  int tmp_1,tmp_2;
  struct maillon_t* suivant;
}maillon_t;

//Fonction permettant de verifier si la chaine de caractere est une lettre/mot
int is_alpha(char *str)
{
  int i = -1;
  while (str[++i])
    if (isalpha(str[i]))
      return (1);
  return (0);
}

//Fonction permettant de verifier si la chaine de caractere est un chiffre/nombre
int is_num(char *str)
{
  int i = -1;
  while (str[++i])
    if (isdigit(str[i]))
      return (1);
  return (0);
}

// Methode permettant d'exit avec affichage d'erreur
void my_error(char *str)
{
    fprintf(stderr, "%s\n", str); // Affichage sortie erreur
    exit(1);
}

// Fonction permettant la creation (et allocation de memoire) d'un seul maillon
maillon_t* create_maillon(int valeur, maillon_t* suivant)
{
    maillon_t* maillon = (maillon_t*)malloc(sizeof(maillon_t));
    if (maillon == NULL)
      my_error("Erreur : allocation de memoire");
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

// Fonction permettant d'inserer un maillon
maillon_t* insert_maillon(maillon_t* maillon, maillon_t* element)
{
  if (maillon == NULL)
  {
    element->suivant = NULL;
    return element;
  }
  element->suivant = maillon;
  return element;
}

// Fonction permettant d'afficher la liste des maillons
void show_maillon(maillon_t* maillon)
{
  if (maillon != NULL)
    {
      show_maillon(maillon->suivant);
      printf("%d -> ", maillon->valeur);
    }
  else
    printf("\n");
}

// Fonction permettant l'addition
maillon_t* my_add(maillon_t* maillon)
{
  printf("my_add\n");
  if (maillon == NULL || maillon->suivant == NULL)
    my_error("Erreur : pas assez d'element pour additionner");
  int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
  maillon_t* res = maillon->suivant->suivant;
  free(maillon->suivant);
  free(maillon);
  return (insert_maillon((res), create_maillon(value1 + value2, res)));
}

// Fonction permettant la soustraction
maillon_t* my_sub(maillon_t* maillon)
{
  if (maillon == NULL || maillon->suivant == NULL)
    my_error("Erreur : pas assez d'element pour soustraire");
  int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
  maillon_t* res = maillon->suivant->suivant;
  free(maillon->suivant);
  free(maillon);
  return (insert_maillon((res), create_maillon(value1 - value2, res)));
}

// Fonction permettant la multiplication
maillon_t* my_mul(maillon_t* maillon)
{
  if (maillon == NULL || maillon->suivant == NULL)
    my_error("Erreur : pas assez d'element pour multiplier");
  int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
  maillon_t* res = maillon->suivant->suivant;
  free(maillon->suivant);
  free(maillon);
  return (insert_maillon((res), create_maillon(value1 * value2, res)));
}

// Fonction permettant de verifier l'operateur
maillon_t* check_operateur(char *str, maillon_t* maillon)
{
  if (str != NULL)
  {
    if (!strcmp(str, "ADD")) // addtionner
      maillon = my_add(maillon);
    else if (!strcmp(str, "SUB")) // soustaire
      maillon = my_sub(maillon);
    else if (!strcmp(str, "MUL")) // multiplier
      maillon = my_mul(maillon);
    else if (!strcmp(str, "DIV")) //diviser
      printf("Il faut diviser\n");
    else if (!strcmp(str, "MOD")) // modulo
      printf("Il faut modulo\n");
    else if (!strcmp(str, "POP")) // retirer le dernier element de la pile
      printf("Il faut enlever le dernier element de la pile\n");
    else if (!strcmp(str, "DUP")) // depliquer le dernier element de la pile
      printf("Il faut dupliquer le dernier element de la pile\n");
    else if (!strcmp(str, "SWP")) // echanger les deux derniers elements de la pile
      printf("Il faut echanger les deux derniers elements de la pile\n");
    else
    my_error("Erreur : operateur inconnu");
  }
  return (maillon);
}

// Fonction principale
int main()
{
    int N;
    maillon_t* maillon = NULL;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        char instruction[11];
        scanf("%s", instruction);
        if (is_num(instruction))
          maillon = insert_maillon(maillon, create_maillon(atoi(instruction), maillon));
        if (is_alpha(instruction))
          maillon = check_operateur(instruction, maillon);
        show_maillon(maillon);
    }
    free_maillon(maillon);
    return 0;
}
