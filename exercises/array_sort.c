#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

int *utworz(int n, int min, int max);
int pint(void);
char pwybor(char min, char max);
char ppierwszy(void);
void menu(void);
void drukuj(int *t, int n);
void przezscalanie(int *A, int n);
void scalaj(int *A, int *L, int li, int *R, int ri);
int *przezzliczanie(int *t, int n);
int min(int *t, int n);
int max(int *t, int n);


int main(void)
{
    int *tablica,*posortowana;
    int n,mx,mi;
    char wybor;
    bool tjest = false;

    srand((unsigned int)time(0));
    menu();
    while((wybor=pwybor('a','d'))!='q')
    {
        switch(wybor)
        {
        case 'a':
            if(!tjest)
            {
                printf("Podaj rozmiar tablicy\n");
                n=pint();
                printf("Podaj mim wartosc\n");
                mi=pint();
                printf("Podaj max wartosc\n");
                mx=pint();
                tablica=utworz(n,mi,mx);
                tjest=true;
            }
            else
                printf("Tablica jest juz utworzona, wpierw usun tablce\n");
            break;

        case 'b':
            if(tjest)
                drukuj(tablica, n);
            else
                printf("Tablica nie utworzona\n");
            break;
        case 'c':
            if(tjest)
            {
                printf("Sortowanie przez scalanie\n");
                przezscalanie(tablica, n);
            }
            else
                printf("Tablica nie utworzona\n");
            break;
        case 'd':
            if(tjest)
            {
                printf("Sortowanie przez zliczanie\n");
                posortowana=przezzliczanie(tablica,n);
                drukuj(posortowana,n);

                break;
            }
            else
                printf("Tablica nie utworzona\n");
            break;

        case 'e':
            free(tablica);
            tjest=false;
            printf("Usunieto tablice\n");
            break;
        }
        menu();
    }

    return 0;
}


int *utworz(int n, int min, int max)
{
    int i;
    int *t=(int *)malloc(sizeof(int)*n);
    max -= min;
    for(i=0;i<n;i++)
        t[i]=(rand() % max) + min;

    return t;
}

char ppierwszy(void)
{
    char ch;
    ch=getchar();
    while(getchar()!='\n')
        continue;
    return ch;
}

char pwybor(char min, char max)
{
    char ch;
    bool czyjest = false;
    while(!czyjest)
    {
        fflush(stdin);
        ch=ppierwszy();
        ch=tolower(ch);
        if(!(ch<min || ch > max) || ch=='q')
        {
            czyjest=true;
            break;
        }
        if(!czyjest)
            printf("wybierz znak z przedzialu %c - %c\n", min,max);
    }
    return ch;
}

void menu(void)
{
    printf("Wybierz:\n"
           "a-stworz tablice\n"
           "b-pokaz tablice\n"
           "c-sortowanie przez scalanie\n"
           "d-sortowanie przez zliczanie\n"
           "e-usun tablice\n"
           "q-zakoncz\n"

           );
}

void drukuj(int *t, int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ", t[i]);
    putchar('\n');
}

int pint(void)
{
    int i;
    char ch;
    while(scanf("%d",&i)!=1)
    {
        while((ch=getchar())!='\n')
            putchar(ch);
        printf(" to nie poprawana liczba calkowia\n");
    }
    return i;
}

void scalaj(int *A, int *L, int lll, int *R, int rrr)
{
    int i,j,k;
    i=0;
    j=0;
    k=0;

    while(i<lll && j<rrr)
    {
        if(L[i]<R[j])
            A[k++]=L[i++];
        else
            A[k++]=R[j++];
    }
    while(i<lll)
        A[k++]=L[i++];
    while(j<rrr)
        A[k++]=R[j++];
}

void przezscalanie(int *A, int n)
{
    int mid, i;
    int *L, *R;
    if(n<2)
        return;
    mid = n/2;
    L=(int *)malloc(sizeof(int)*mid);
    R=(int *)malloc(sizeof(int)*(n-mid));
    for(i=0;i<mid;i++)
        L[i]=A[i];
    for(i=mid;i<n;i++)
        R[i-mid]=A[i];

    przezscalanie(L,mid);
    przezscalanie(R,n-mid);
    scalaj(A,L,mid,R,n-mid);
    free(L);
    free(R);
}

int min(int *t, int n)
{
    int i, m=INT_MAX;
    for(i=0;i<n;i++)
        m=(t[i]<m)?t[i]:m;
    return m;
}

int max(int *t, int n)
{
    int i, m=0;
    for(i=0;i<n;i++)
        m=(t[i]>m)?t[i]:m;
    return m;
}


int *przezzliczanie(int *t, int n)
{
    int *temp, *sort, i;
    int mi=min(t,n);
    int mx=max(t,n);
    temp=(int *)calloc(mx-mi+1,sizeof(int));
    sort=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        temp[t[i]-mi]++;
    for(i=mi+1;i<=mx;i++)
        temp[i-mi]+=temp[i-mi-1];
    for(i=n-1;i>=0;i--)
        sort[(temp[t[i]-mi]--)-1]=t[i];
    free(temp);

    return sort;
}
