#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
	char nazwisko[30];
	char imie[20];
	int numer;
	double oceny[5];
	double srednia;
}Student;

void dodaj(char*);
struct student srednia(struct student);
void drukuj(struct student);
void wydruk(char*);
double maksimum(char *);
struct student* najlepsi(char *, int*);
double minimum(char*);
int usun(char*);
void popraw(char*);

int main() 
{
	char wybor;
	
	while (1)
	{
		printf("\nd - Dodaj\n"
			"w - Wydruk\n"
			"u - usun\n"
			"m - Najlepsi\n"
			"p - Popraw\n"
			"q - Wyjscie\n"
			"Opcja: ");
		
		scanf(" %c", &wybor);
		switch (wybor)
		{
			case 'd': 
				{
				dodaj("plik.txt");
				break;
				}
			case 'w':
				{
				wydruk("plik.txt");
				break;
				}
			case 'u': 
				{
				printf("\nUsunieto %d Studentow\n", usun("plik.txt"));
				break;
				}
			case 'm': 
				{
				int ilosc=0,i=0;
				printf("1");
				Student *studenci = najlepsi("plik.txt", &ilosc);
				for (i = 0; i < ilosc; i++)
					drukuj(*(studenci + i));
				break;
				}
			case 'p': 
				{
				popraw("plik.txt");
				break;
				}
			case 'q':
				{
				return 0;
				break;
				}
	
			default:
				printf("\nNiepoprawny wybor");
				break;
		}
	}
	
}

void dodaj(char* nazwa) {
	int i;
	Student s;
	FILE *plik = fopen(nazwa, "a+b");
	if (plik == NULL) 
		printf("Nie udalo sie otworzyc pliku"); exit(0);

	printf("Podaj nazwisko: \t");
	scanf("%29s",s.nazwisko);
	//scanf("%29[^\n]s\n", s.nazwisko);
	printf("Podaj Imie: \t");
	//scanf("%19[^\n]s\n",s.imie);
	scanf("%19s", s.imie);
	printf("Podaj numer: \t");
	scanf("%d",&s.numer);
	printf("Podaj 5 ocen: \t");	
	for (i = 0; i < 5;) 
	{
		printf("[%d] = ", i + 1);			
		scanf("%lf", &s.oceny[i]);
			if (s.oceny[i]<0 || s.oceny[i]>6)
		printf("nie ma takiej oceny\n");
			else i++;
	}

	s = srednia(s);

	fwrite(&s, sizeof(Student), 1, plik);
	fclose(plik);

}

struct student srednia(struct student s)
{
	int i;
	double sr=0;
	for (i = 0; i < 5; i++)sr += s.oceny[i];
	s.srednia=sr / 5.0;
	return s;
}

void drukuj(struct student s)
{
	int i;
	printf("\nDane:\n\tImie:\t\t %s"
		"\n\tNazwisko:\t %s \n\tNumer:\t\t %d \n\tOceny: ",s.imie,s.nazwisko,s.numer);

	for (i = 0; i < 5; i++) 
		printf("\n\t\t[%d]%.2lf",i, s.oceny[i]);
	printf("\n\tSrednia: \t%0.2lf", s.srednia);
}
void wydruk(char* nazwa) 
{
	Student s;
	FILE *plik = fopen(nazwa, "r");
	if (plik == NULL) 
		printf("Nie udalo sie otworzyc pliku"); exit(0);
	while (fread(&s, sizeof(Student), 1, plik)) 
		drukuj(s);
	fclose(plik);

}
double maksimum(char * nazwa) 
{
	Student s;
	FILE *plik = fopen(nazwa, "r");
	double maxSrednia = -1;
	while (fread(&s, sizeof(Student), 1, plik)) 
		if (s.srednia > maxSrednia)maxSrednia = s.srednia;
	fclose(plik);
	return maxSrednia;
}
struct student* najlepsi(char * nazwa, int* ilosc) 
{
	double maxSrednia = maksimum("plik.txt");
	Student *studenci= malloc(sizeof(Student)) , s;
	FILE *plik=fopen(nazwa,"rb");
	int i = 0;
	while (fread(&s, sizeof(Student), 1, plik)) 
	{
		if (s.srednia == maxSrednia) 
		{
			i++;
			studenci = realloc(studenci, i * sizeof(Student));
			*(studenci + i-1) = s;
		}
	}
	*ilosc = i;
	fclose(plik);
	return studenci;

}

double minimum(char* nazwa) 
{
	Student s;
	double minSrednia=-1;
	FILE *plik = fopen(nazwa, "r+b");
	while (fread(&s, sizeof(Student), 1, plik))
	{
		if (s.srednia < minSrednia) minSrednia = s.srednia;
		else if (minSrednia < 0)minSrednia = s.srednia;
	}
	fclose(plik);
	return minSrednia;
}

int usun(char* nazwa) //zwarca ile usunieto
{ 
	int deletedStudents=0;
	Student s;
	double minSrednia = minimum("plik.txt");
	FILE *plik=fopen(nazwa,"r+b");
	FILE *tmpFile = fopen("tmp.txt", "wb");

	while (fread(&s, sizeof(Student), 1, plik)) 
	{
		if (s.srednia != minSrednia) fwrite(&s, sizeof(Student), 1, tmpFile);
		else deletedStudents++;
	}
	fclose(plik); fclose(tmpFile);
	if (remove(nazwa) == 0) 
		if (rename("tmp.txt", nazwa) != 0) printf("\nBrak dostepu do pliku tmp.txt");
	else
		printf("\nBrak dostepu do pliku %s", nazwa);

	return deletedStudents;
}
void popraw(char* nazwa)
{
	char imie[20], nazwisko[30];
	int numerOceny,nowaOcena,index=-1;
	char znaleziono=0;
	Student s;
	FILE *plik=fopen(nazwa,"r+b");
	if (plik == NULL) 
	{
		printf("Nie udalo sie otworzyc pliku");
		exit(0);
	}
	printf("Podaj Imie: \t");
	scanf(" %s", &imie);
	printf("Nazwisko: \t");
	scanf(" %s", &nazwisko);

	while (fread(&s, sizeof(Student), 1, plik))
	{
		index++;
		if (!strcmp(s.imie, imie) && !strcmp(s.nazwisko, nazwisko))
		{
			znaleziono = 1;
			fseek(plik, index * sizeof(Student), SEEK_SET);

			drukuj(s);
			printf("\nKtora ocene poprawic?\n");
			scanf("%d", &numerOceny);
			if (numerOceny < 0 || numerOceny >= 5) 
			{
				do
				{
					printf("\nNie ma oceny z takim indeksem. Wpisz jeszcze raz.\n");
					scanf("%d", &numerOceny);
				} while (numerOceny < 0 && numerOceny >= 5);

			}

			printf("Na jaka ocene?: ");
			scanf("%d", &nowaOcena);
			s.oceny[numerOceny] = nowaOcena;
			s = srednia(s);
			fwrite(&s, sizeof(Student), 1, plik);
			fclose(plik);
		}
	}
	if (znaleziono == 0) 
		printf("\nNie znaleziono ucznia");
}
