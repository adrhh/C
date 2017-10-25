#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct dane
{
    char tekst[MAX];
    int liczba;
};

typedef struct dane Dane;

struct wezel
{
    Dane data;
    struct wezel *next;
};

struct wezel *push(struct wezel *head, Dane d);
struct wezel *pop(struct wezel *head, Dane *d);
void display(struct wezel *head);
Dane utworzdane(char *c, int x);

int main(void)
{
    struct wezel *glowa;
    Dane dd = { "test",2};

    glowa=(struct wezel *)malloc(sizeof(struct wezel));
    glowa->next=NULL;

    for(int i=0;i<10;i++)
    {
         glowa=push(glowa, dd);
         dd.liczba++;
    }

    display(glowa);

    return 0;
}

struct wezel *push(struct wezel *head, Dane d)
{
    struct wezel *temp = (struct wezel *)malloc(sizeof(struct wezel));

    if(temp == NULL)
        exit(EXIT_FAILURE);
    temp->data=d;
    temp->next=head;
    head=temp;
    return head;
};

Dane utworzdane(char *c, int x)
{
    Dane wynik;
    strcpy(wynik.tekst, c);
    wynik.liczba =x;

    return wynik;
};

void display(struct wezel *head)
{
    struct wezel *biezacy;
    biezacy = head;
    if(biezacy!=NULL)
    {
        printf("zawartosc stosu\n");
        do{
            printf("%d %s", biezacy->data.liczba, biezacy->data.tekst);
            biezacy=biezacy->next;
        }while(biezacy!=NULL);
        printf("\n");
    }
    else
        printf("Stos pusty\n");
}

struct wezel *pop(struct wezel *head, Dane *d)
{
    struct wezel *temp = head;
    *d=head->data;
    head=head->next;
    free(temp);

    return head;
};
