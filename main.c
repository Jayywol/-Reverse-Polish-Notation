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

// Gestion d'erreur
void my_error(char *str)
{
        printf("ERROR");
        fprintf(stderr, "%s\n", str); // Affichage raison erreur en canal sortie
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
void show_maillon(maillon_t* maillon, int i)
{
        if (maillon != NULL)
        {
                show_maillon(maillon->suivant, i + 1);
                printf("%d", maillon->valeur);
                if (i != 0)
                        printf(" ");
        }
}

/*
** FONCTION OPERATEURS DE STACK : POP, DUP, SWP, ROL
*/

// Fonction permettant de retirer le dernier element du maillon
maillon_t* my_pop(maillon_t* maillon)
{
        maillon_t* tmp = NULL;
        if (maillon != NULL)
        {
                tmp = maillon->suivant;
                free(maillon);
        }
        return tmp;
}

// Fonction permettant de dupliquer le dernier element du maillon
maillon_t* my_dup(maillon_t* maillon)
{
        if (maillon == NULL)
                return NULL;
        return insert_maillon(maillon, create_maillon(maillon->valeur, maillon));
}

// Fonction permettant d'echanger de place des deux derniers maillons
maillon_t* my_swap(maillon_t* maillon)
{
        if (maillon->suivant != NULL)
        {
                int tmp = maillon->valeur;
                maillon->valeur = maillon->suivant->valeur;
                maillon->suivant->valeur = tmp;
        }
        return (maillon);
}

// Fonction permettant de remonter l'element du maillon a une position i
int my_rol(maillon_t* previous, maillon_t* maillon, int i)
{
        if (i == 1)
        {
                maillon_t* tmp = maillon->suivant;
                int res = maillon->valeur;
                free(maillon);
                previous->suivant = tmp;
                return res;
        }
        else
                return my_rol(maillon, maillon->suivant,i - 1);
}

// Fonction permettant d'initialiser le nouveau maillon a creer en liberant la memoire des deux anciens maillons
maillon_t* my_init(maillon_t* maillon)
{
        maillon_t* tmp = maillon->suivant->suivant;
        free(maillon->suivant);
        free(maillon);
        return tmp;
}

// FONCTION OPERATEURS BASIQUE : ADD, SUB, MUL, DIV, MOD

// Fonction permettant l'addition
maillon_t* my_add(maillon_t* maillon)
{
        int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
        maillon_t* tmp = my_init(maillon);
        return (insert_maillon (tmp, create_maillon(value1 + value2, tmp)));
}

// Fonction permettant la soustraction
maillon_t* my_sub(maillon_t* maillon)
{
        int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
        maillon_t* tmp = my_init(maillon);
        return (insert_maillon (tmp, create_maillon(value1 - value2, tmp)));
}

// Fonction permettant la multiplication
maillon_t* my_mul(maillon_t* maillon)
{
        int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
        maillon_t* tmp = my_init(maillon);
        return (insert_maillon (tmp, create_maillon(value1 * value2, tmp)));
}

// Fonction permettant la division
maillon_t* my_div(maillon_t* maillon)
{
        int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
        if (!value1 || !value2) // Verification de la division par zero
        {
                maillon = my_pop(maillon);
                maillon = my_pop(maillon);
                show_maillon(maillon, 0);
                printf(" "); // Fix codingame
                my_error("Erreur : division par zero impossible");
        }
        maillon_t* tmp = my_init(maillon);
        return (insert_maillon (tmp, create_maillon(value1 / value2, tmp)));
}

// Fonction permettant le modulo
maillon_t* my_mod(maillon_t* maillon)
{
        int value1 = maillon->suivant->valeur, value2 = maillon->valeur;
        if (!value1 || !value2) // Verification de la division par zero
                my_error("Erreur : modulo par zero impossible");
        maillon_t* tmp = my_init(maillon);
        return (insert_maillon (tmp, create_maillon(value1 % value2, tmp)));
}

// Fonction permettant de verifier l'operateur
maillon_t* check_operateur(char *str, maillon_t* maillon)
{
        if (str != NULL)
        {
                if (maillon == NULL || maillon->suivant == NULL)
                        my_error("Erreur : pas assez d'element");
                if (!strcmp(str, "ADD")) // addtionner
                        maillon = my_add(maillon);
                else if (!strcmp(str, "SUB")) // soustaire
                        maillon = my_sub(maillon);
                else if (!strcmp(str, "MUL")) // multiplier
                        maillon = my_mul(maillon);
                else if (!strcmp(str, "DIV")) //diviser
                        maillon = my_div(maillon);
                else if (!strcmp(str, "MOD")) // modulo
                        maillon = my_mod(maillon);
                else if (!strcmp(str, "POP")) // retirer le dernier element de la pile
                        maillon = my_pop(maillon);
                else if (!strcmp(str, "DUP")) // dupliquer le dernier element de la pile
                        maillon = my_dup(maillon);
                else if (!strcmp(str, "SWP")) // echanger les deux derniers elements de la pile
                        maillon = my_swap(maillon);
                else if (!strcmp(str, "ROL")) // remonter l'element du maillon a la position i
                {
                        int i = maillon->valeur;
                        maillon = my_pop(maillon);
                        i = my_rol(maillon, maillon->suivant, i - 1);
                        maillon = insert_maillon(maillon, create_maillon(i, maillon));
                }
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
        }
        show_maillon(maillon, 0);
        free_maillon(maillon);
        return 0;
}
