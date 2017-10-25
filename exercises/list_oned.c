#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROZ 45

struct film
{
    char tytul[ROZ];
    int ocena;
    struct film *nast;
};

char *wczytaj(char *z, int ile);

int main(void)
{
    struct film *glowny = NULL;
    struct film * poprz, *biezacy;
    char wejscie[ROZ];

    puts("Podaj pierwszy tytul");

    while(wczytaj(wejscie, ROZ) != NULL && wejscie[0] != '\0')
    {
        biezacy = (struct film *) malloc(sizeof(struct film));
        if(glowny == NULL)
            glowny=biezacy;
        else
            poprz->nast = biezacy;
        biezacy->nast = NULL;
        strcpy(biezacy->tytul, wejscie);
        puts("Podaj ocene");
        scanf("%d", &biezacy->ocena);
        while(getchar() != '\n')
            continue;
        puts("Podaj kolejny tytul");
        poprz=biezacy;
    }
    if (glowny == NULL)
        printf("Nie wpisano zadnych danych");
    else
        printf("Oto lista filmow\n");
    biezacy = glowny;
    while(biezacy != NULL)
    {
        printf("%s ocenal %d\n", biezacy->tytul, biezacy->ocena);
        biezacy = biezacy->nast;
    }
    biezacy = glowny;
    while(biezacy != NULL)
    {
        poprz = biezacy;
        biezacy = poprz->nast;
        free(poprz);
    }
    return 0;
}

char *wczytaj(char *z, int ile)
{
    char *wynik;
    char *tutaj;

    wynik = fgets(z, ile, stdin);
    if(wynik)
        tutaj = strchr(z, '\n');
        if(tutaj)
            *tutaj = '\0';
        else
            while (getchar() != '\n')
                continue;

    return wynik;
}
