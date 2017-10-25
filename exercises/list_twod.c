#include<stdio.h>
#include<stdlib.h>

struct element
{
    int k;
    struct element*prev;
    struct element*next;
};

void lista_wyswietl(struct element *head);
struct element *lista_dodaj(struct element *head, struct element *nowy);
struct element *szukaj(struct element *head, int x);
struct element *usun(struct element *head, struct element *x);
struct element *odwroc(struct element *head);

int main(void)
{
    struct element *head=NULL, *nowy=NULL, *szukany=NULL, *odwrotnie=NULL;
    char z;
    int liczba;
    while(1)
    {
    printf("\nco chcesz zrobic?");
    printf("\nd - dodac");
    printf("\ns - szukac");
    printf("\nu - usunac");
    printf("\no - odwrocic liste");
    printf("\nw - wyswietlic");
    printf("\nq - wyjsc\n");
    fflush(stdin);
    z=getchar();
        
    switch(z)
        {
        case 'd':
            nowy=(struct element*)malloc(sizeof(struct element));
            printf("\npodaj wartosc elementu do wstawienia:\n");
            scanf("%d",&liczba);
            nowy->k=liczba;
            head=lista_dodaj(head,nowy);
            break;
        case 'o':
            odwrotnie=odwroc(head);
            lista_wyswietl(odwrotnie);
            break;
        case 's':
            printf("Podaj liczbe szukana\n");
            scanf("%d",&liczba);
            if((szukany=szukaj(head,liczba))!=NULL)
               printf("Znaleziono %d\n", szukany->k);
            else
                printf("Nie znaleziono\n");
            break;
        case 'u':
            printf("Podaj element do usuniecia\n");
            scanf("%d", &liczba);
            if((szukany=szukaj(head,liczba))!=NULL)
                head=usun(head, szukany);
            else
                printf("Nie ma takiego elementu o kluczu %d\n", liczba);
            break;
        case 'w': lista_wyswietl(head);
            break;
        case 'q': return 0;
        }
    }

    return 0;
}
void lista_wyswietl(struct element *head)
{
    struct element*x=head;
    while(x!=NULL)
    {
        printf("%d ",x->k);
        x=x->next;
    }
}

struct element *lista_dodaj(struct element *head, struct element *nowy)
{
    nowy->prev=NULL;
    nowy->next=head;
    if(head!=NULL)
        head->prev=nowy;
    head=nowy;
    return head;
}

struct element *szukaj(struct element *head, int x)
{
    struct element *y=head;
    while(y!=NULL && y->k!=x)
        y=y->next;
    return y;
};

struct element *usun(struct element *head, struct element *x)
{
    if(x->prev!=NULL)
        x->prev->next = x->next;
    else
        head=x->next;
    if(x->next!=NULL)
        x->next->prev = x->prev;
    free(x);
    return head;
};

struct element *odwroc(struct element *head)
{
    struct element *nowa = NULL, *y, *x=head;
    while(x!=NULL)
    {
        y=(struct element *)malloc(sizeof(struct element));
        y->k=x->k;
        nowa=lista_dodaj(nowa, y);
        x=x->next;
    }
    return nowa;
};
