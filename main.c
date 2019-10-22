#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct maillon_t
{
  int valeur;
  struct maillon_t* suivant;
}maillon_t;

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char instruction[11];
        scanf("%s", instruction);
    }

    // Write an action using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    printf("answer\n");

    return 0;
}
