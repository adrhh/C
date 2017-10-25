#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 100

int czytaj_calkowita(void);
int *utworz_tablice(int);
void drukuj_tablice(int *, int);
int *sortowanie_babelkowe(int *, int);
void zamien(int *, int *);
void zamien_na_losowe(int *, int);
int szukanie_liniowe_1(const int *, int, int);
int *szukanie_liniowe_2(const int *t, int, int, int *);
int szukanie_binarne(int *, int, int);
void menu(void);
char pobierz_wybor(char, char);
char pobierz_pierwszy();

int main(void)
{
    int rozmiar_tablicy;
    int *tablica_testowa;
    int *tablica_posortowana;
    int *wyniki;
    srand((unsigned int) time(0));
    int czy_jest_tablica = 0;
    int ile_wynikow = 0;
    int wybor;
    int szukany_indeks;
    int szuakna_wartosc;

    menu();
    while((wybor=pobierz_wybor('a', 'f'))!='q')
    {
        switch(wybor)
        {
        case 'a':
            {
                if(!czy_jest_tablica)
                {
                    puts("Podaj rozmiar tablicy");
                    rozmiar_tablicy = czytaj_calkowita();
                    czy_jest_tablica = 1;
                }
                else
                    fprintf(stderr, "tablica juz jest utworzona\n");

                break;
            }
        case 'b':
            {

                tablica_testowa=utworz_tablice(rozmiar_tablicy);
                puts("Podana tablica:");
                drukuj_tablice(tablica_testowa, rozmiar_tablicy);
                break;
            }
        case 'c':
            {
                // jak sprawdzi czy jest ?
                tablica_testowa=(int *)malloc(sizeof(int)*rozmiar_tablicy);
                zamien_na_losowe(tablica_testowa, rozmiar_tablicy);
                puts("Podana tablica:");
                drukuj_tablice(tablica_testowa, rozmiar_tablicy);
                break;
            }
        case 'd':
            {
                puts("Podaj szukana wartosc");
                szuakna_wartosc=czytaj_calkowita();
                szukany_indeks=szukanie_liniowe_1(tablica_testowa, rozmiar_tablicy, szuakna_wartosc);
                puts("W danej tablicy:");
                drukuj_tablice(tablica_testowa, rozmiar_tablicy);
                if(szukany_indeks!=-1)
                    printf("Wartosc %d ma indeks:%d\n", szuakna_wartosc, szukany_indeks);
                else
                    printf("Nie ma wartosci %d\n", szuakna_wartosc);
                break;
            }
        case 'e':
            {
                puts("Podaj szukana wartosc");
                szuakna_wartosc=czytaj_calkowita();
                wyniki = szukanie_liniowe_2(tablica_testowa, rozmiar_tablicy, szuakna_wartosc, &ile_wynikow);
                if(ile_wynikow)
                {
                    printf("%d wartosc wstepuje %d %s\n", szuakna_wartosc, ile_wynikow, (ile_wynikow>1)?"razy":"raz" );
                    printf("Tablca indeksow szukanej wartosci\n");
                    drukuj_tablice(wyniki, ile_wynikow);
                    free(wyniki);
                }
                else
                    puts("Brak wynikow");
                break;
            }
        case 'f':
            {
                puts("Podaj szukana wartosc");
                szuakna_wartosc=czytaj_calkowita();
                tablica_posortowana=sortowanie_babelkowe(tablica_testowa, rozmiar_tablicy);
                szukany_indeks=szukanie_binarne(tablica_posortowana, rozmiar_tablicy, szuakna_wartosc);
                puts("W danej tablicy:");
                drukuj_tablice(tablica_posortowana, rozmiar_tablicy);
                if(szukany_indeks!=-1)
                    printf("Wartosc %d ma indeks:%d\n", szuakna_wartosc, szukany_indeks);
                else
                    printf("Nie ma wartosci %d\n", szuakna_wartosc);
                break;
            }

        default:
            {
                fprintf(stderr, "Blad programu\n");
                exit(EXIT_FAILURE);
            }
        }
        szukany_indeks=-1;
        menu();
        fflush(stdin);
    }

    free(tablica_testowa);
    free(tablica_posortowana);

    return 0;
}

int czytaj_calkowita(void)
{
    int wynik;
    char ch;
    while(scanf("%d", &wynik)!=1)
    {
        while((ch=getchar())!='\n')
            putchar(ch);
        printf("Podaj prawdlowa liczbe calkowita");
    }
    return wynik;
}

int *utworz_tablice(int rozmiar)
{
    int i;
    int *wynik = (int *)malloc(sizeof(int)*rozmiar);

    for(i=0; i<rozmiar; i++)
    {
        printf("Podaj element o indeksie %d:\n", i);
        wynik[i] = czytaj_calkowita();
    }

    return wynik;
}

void drukuj_tablice(int *tablica, int rozmiar)
{
    int i;

    for(i=0; i<rozmiar; i++)
        printf("%d ", tablica[i]);
    putchar('\n');
}

void zamien(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int *sortowanie_babelkowe(int *tablica, int rozmiar)
{
    int i,j;
    int *posortowana = (int *)malloc(sizeof(int)*rozmiar);

    for(i=0;i<rozmiar;i++)
        posortowana[i]=tablica[i];

    for(i=0; i<rozmiar-1; i++)
        for(j=0; j<rozmiar-1; j++)
        {
            {
                if(posortowana[j] > posortowana[j+1])
                    zamien(&posortowana[j],&posortowana[j+1]);
            }
        }

    return posortowana;
}

void zamien_na_losowe(int *tablica, int rozmiar)
{
    int i;


    for(i=0;i<rozmiar;i++)
        tablica[i] = rand() % 100;

}

int szukanie_liniowe_1(const int *t, int n, int x)
{
    int i;
    int wynik = -1;

    for(i=0;i<n;i++)
        if(*(t+i)==x)
            wynik = i;

    return wynik;
}

int *szukanie_liniowe_2(const int *t, int n, int x, int *ilosc)
{
    int *tablica_wynikow = (int *)malloc(sizeof(int)*n);
    int ile=0;
    int i;

    for(i=0;i<n;i++)
        if(*(t+i)==x)
        {
            tablica_wynikow[ile]=i;
            ile++;
        }

    *ilosc=ile;
    tablica_wynikow = (int *)realloc(tablica_wynikow,ile*sizeof(int));

    return tablica_wynikow;
}

int szukanie_binarne(int *t, int n, int x)
{
    int left = 0;
    int right = n-1;
    int mid = 0;
    int wynik = -1;


    while(left <= right)
        {
            mid = left + (right - left) / 2;
            if(t[mid] == x)
            {
            wynik = mid;
            break;
            }
            else
            {
                if(t[mid] < x)
                    left = mid + 1;
                else
                    right = mid -1;
            }
   }

   return wynik;
}

void menu(void)
{
    printf("Wybierz jedna z dostepnych opcji:\n"
           "a)utworz tablice\n"
           "b)ustaw wartosci recznie\n"
           "c)ustaw wartosci losowo\n"
           "d)szukaj liniowo 1\n"
           "e)szukaj liniowo 2\n"
           "f)szukanie binarne\n"
           "q)zakoncz program\n");

}

char pobierz_wybor(char min, char max)
{
    int ch;
    ch = pobierz_pierwszy();
    while((ch < min || ch > max) && ch!='q')
    {
        printf("Wpisz znak z dostepnch: ");
        for(int i=min; i<=max;i++)
            printf("%c ", i);
        putchar('\n');
        ch = pobierz_pierwszy();
    }
    return ch;
}

char pobierz_pierwszy(void)
{
    int ch;
    ch=getchar();
    while(getchar()!='\n')
        continue;
    return ch;
}

