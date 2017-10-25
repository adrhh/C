#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

void pokazfilm(Pozycja pozycja);
char * wczytaj(char *z, int ile);

int main(void)
{
    Lista filmy;
    Pozycja tymcz;

    InicjujListe(&filmy);
    if(PelnaLista(&filmy))
    {
        fprintf(stderr, "brak pamieci, nara!\n");
        exit(1);
    }

    puts("Podaj pierwszy film:");

    while (wczytaj(tymcz.tytul, ROZT) != NULL && tymcz.tytul[0] != '\0')
    {
        puts("Podaj ocene:");
        scanf("%d", &tymcz.ocena);
        while(getchar() != '\n')
            continue;
        if (DodajPozycje(tymcz, &filmy) == false)
        {
            fprintf(stderr, "Blad alkocacji pamieci\n");
            break;
        }
        if (PelnaLista(&filmy))
        {
            puts("Lista pelna");
            break;
        }
        puts("Podaj kolejny tytul");
    }

    if(PustaLista(&filmy))
        printf("Nie podano zandego filmu\n");
    else
    {
        printf("Lista filmow:\n");
        Przejdz(&filmy, pokazfilm);
     }
     printf("Liczba wpsianych filmow: %d", LiczbaPozycji(&filmy));
     CzyscListe(&filmy);

    return 0;
}

void pokazfilm(Pozycja pozycja)
{
    printf("Filmy: %s Ocena: %d\n", pozycja.tytul, pozycja.ocena);
}

char * wczytaj(char *z, int ile)
{
    char *wynik;
    char *tutaj;
    wynik = fgets(z, ile, stdin);
    if(wynik)
    {
        tutaj = strchr(z, '\n');
        if(tutaj)
            *tutaj = '\0';
        else
            while(getchar() != '\n')
                continue;
    }
    return wynik;
}



