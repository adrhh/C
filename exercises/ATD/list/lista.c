#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

static void KopjujDoWezla(Pozycja pozycja, Wezel * wwezel);

void InicjujListe(Lista * wlista)
{
    * wlista = NULL;
}

bool PustaLista(const Lista * wlista)
{
    if(*wlista == NULL)
        return true;
    else
        return false;
}

bool PelnaLista(const Lista * wlista)
{
    Wezel * wsk;
    bool full;
    wsk = (Wezel *) malloc(sizeof(Wezel));
    if (wsk == NULL)
        full = true;
    else
        full = false;
    free(wsk);
    return full;
}

unsigned int LiczbaPozycji(const Lista * wlista)
{
    unsigned int licznik = 0;
    Wezel *w = *wlista;
    while(w != NULL)
    {
        ++licznik;
        w = w->nast;
    }
    return licznik;
}

bool DodajPozycje(Pozycja pozycja, Lista * wlista)
{
    Wezel * wnowy;
    Wezel * szuk = *wlista;
    wnowy = (Wezel *) malloc(sizeof(Wezel));
    if(wnowy == NULL)
        return false;
    KopjujDoWezla(pozycja, wnowy);
    wnowy->nast = NULL;
    if(szuk == NULL)
        *wlista = wnowy;
    else
    {
        while(szuk->nast != NULL)
            szuk = szuk->nast;
        szuk->nast = wnowy;
    }
    return true;
}

void Przejdz(const Lista *wlista, void(* wfun)(Pozycja pozycja))
{
    Wezel *wsk = *wlista;
    while (wsk != NULL)
    {
        (*wfun)(wsk->pozycja);
        wsk = wsk->nast;
    }
}

void CzyscListe(Lista *wlista)
{
    Wezel *wsk;
    while (*wlista != NULL)
    {
        wsk = (*wlista)->nast;
        free(*wlista);
        *wlista = wsk;
    }
}

static void KopjujDoWezla(Pozycja pozycja, Wezel * wwezel)
{
    wwezel->pozycja = pozycja;
}
