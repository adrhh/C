#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SKOLUMNY 2 //samoodowrtone 2 [1^a1 2^a2]

int ilejesttypow(int s);
int **utworztablice(int n, int m);
void wypelnijtablicesamoodw(int **t, int n);
void wydrukujtab(int **t, int n);
long ilejestsmoodw(int **t, int n);
long silnia(int n);
long potegowanie(int a, int b);
void zamien(int *t, int a, int b);
void perm(int *t, int n, int i);
char pobierzwybor(char min, char max);
char pobierzpierwszy(void);
void menu(void);
int pobierzint(void);

int main()
{
    int wybor;
    int n;
    int ile;
    int **tablicasamo;
    int *tabpermutacji;

    menu();
    while((wybor=pobierzwybor('a', 'b'))!='q')
    {

        switch(wybor)
        {
        case 'a':
            {
            printf("Podaj S:\n");
            n=pobierzint();
            ile=ilejesttypow(n);
            tablicasamo=utworztablice(n,SKOLUMNY);
            wypelnijtablicesamoodw(tablicasamo,n);
            wydrukujtab(tablicasamo, ile);
            printf("W S%d jest %ld samoodwrotnych permutacji.\n", n, ilejestsmoodw(tablicasamo, ile));
            free(tablicasamo);
            break;
            }
        case 'b':
            {
            printf("Podaj S:\n");
            n=pobierzint();
            tabpermutacji = (int *)malloc(n * sizeof(int));
            for(int i=0;i<n;i++)
                tabpermutacji[i]=i+1;
            perm(tabpermutacji,n,0);
            free(tabpermutacji);
            break;
            }
        default:
            puts("Blad programu");
            exit(EXIT_FAILURE);
        }
        menu();
        fflush(stdin);
    }
    return 0;
}

int ilejesttypow(int s)
{
    int ilejest=0;
    float tempalfadwa;

    for(int i=0;i<=s;i++)
    {
      tempalfadwa = (s-i) / 2.0;
      if (roundf(tempalfadwa) == tempalfadwa)  //czy calkowita ?
          ilejest++;
    }

    return ilejest;
}

int **utworztablice(int n, int m)
{
    int **tablica;

    tablica = (int **)malloc(n * sizeof(int *));
    for (int i=0;i<n;i++)
        tablica[i] = (int *)malloc(m * sizeof(int));

    return tablica;
}

void wypelnijtablicesamoodw(int **t, int n)
{
    int alfadwa; //alfajeden = i;
    int l=0;     //iterator wierszy tablicy;
    float tempalfadwa;

    for(int i=0;i<=n;i++)
    {
        tempalfadwa = (n-i) / 2.0;
        if (roundf(tempalfadwa) == tempalfadwa)  //czy calkowita ?
            {
                alfadwa = (int) tempalfadwa;
                t[l][0] = i;
                t[l][1] = alfadwa;
                l++;
            }
    }
    realloc(t, l*sizeof(int *));
}


void wydrukujtab(int **t, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<SKOLUMNY;j++)
            printf("%d ", t[i][j]);
        putchar('\n');
    }
}

long ilejestsmoodw(int **t, int n)
{
    long wynik=0;
    int s = t[0][0] + 2*t[0][1];

    for(int i=0;i<n;i++)
        wynik += silnia(s) / ( potegowanie(1,t[i][0]) * potegowanie(2,t[i][1]) * silnia(t[i][0]) * silnia(t[i][1]) );

    return wynik;
}

long silnia(int n)
{return (n==0)?1:n*silnia(n-1);}

long potegowanie(int a, int b) // mozna uzyc pow z math.h ale pow dzialna na double co nie jest potrzebne.
{
    long wynik=1;

    for(int i=1;i<=b;i++)
        wynik*=a;

    return wynik;
}

void zamien(int *t, int a, int b)
{
    int temp = t[a];

    t[a] = t[b];
    t[b] = temp;
}


void perm(int *t, int n, int i)
{
	if (i==n)
    {
		for(int j=0;j<n;j++)
            printf("%d ", t[j]);
		putchar('\n');
	}
	else
		for(int j=i;j<n;j++)
        {
			zamien(t, i, j);
			perm(t, n, i+1);
			zamien(t, i, j);
		}
}

char pobierzwybor(char min, char max)
{
    int ch;
    ch = pobierzpierwszy();
    while((ch < min || ch > max) && ch!='q')
    {
        printf("Wpisz znak z dostepnch: ");
        for(int i=min; i<=max;i++)
            printf("%c ", i);
        putchar('\n');
        ch = pobierzpierwszy();
    }
    return ch;
}


char pobierzpierwszy(void)
{
    int ch;
    ch=getchar();
    while(getchar()!='\n')
        continue;
    return ch;
}

int pobierzint(void)
{
    int in;
    char ch;

    while( scanf("%d", &in) != 1)
    {
        while((ch = getchar()) != '\n')
            putchar(ch);
        printf(" nie jest liczba calkowita.\n");
    }
    return in;
}


void menu(void)
{
    printf("Wybierz z dostepnych opcji:\n"
           "a) Ile jest nieporzadkow\n"
           "b) Generuj permutacje\n"
           "q) Zakoncz program\n");
}
