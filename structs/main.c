#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "file.dat"

typedef struct 
{
   int dzien, mies, rok;
} data;

typedef struct
{
   char imie[15];
   char nazwisko[20];
   data dataUrodz;
} osoba;

osoba** osoby = NULL;
int rozmiar = 0;

void flush()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void sprawdz_plik(FILE* f)
{
    if (f == NULL)
    {
        printf("Blad otwarcia pliku\n");
        system("pause");
        exit(1);
    }
}

void wczytaj(char napis[], int n)
{
   fgets(napis, n, stdin);
   napis[strlen(napis) - 1] = '\0';
}

void odczyt()
{
    FILE* f = fopen(FILENAME, "r");
    sprawdz_plik(f);
    
    osoba o;
    rozmiar = 0;
    
    while (fread(&o, sizeof(osoba), 1, f)) rozmiar++;
    rewind(f);
    osoby = realloc(osoby, rozmiar * sizeof(osoba*));
    
    if (rozmiar == 0)
        printf("pusto\n");

    for (int i = 0; i < rozmiar; i++)
    {
        fread(&o, sizeof(osoba), 1, f);
        osoba* oc = malloc(sizeof(osoba));
        memcpy(oc, &o, sizeof(osoba));
        osoby[i] = oc;
    }
    
    fclose(f);
}

void zapis()
{
    FILE* f = fopen(FILENAME, "w+");
    sprawdz_plik(f);
    
    if (rozmiar == 0)
    {
        fprintf(f, " ");
    }
    else for (int i = 0; i < rozmiar; i++)
    {
        if (osoby[i] != NULL)
            fwrite(osoby[i], sizeof(osoba), 1, f);
    }
    
    fclose(f);
}

void wyswietlanie()
{
    osoba* o;
    
    for (int i = 0; i < rozmiar; i++)
    {
        o = osoby[i];
        printf("%-5s %-20s %-15s %10s\n", "NUMER", "NAZWISKO", "IMIE", "DATA URODZENIA");
        printf("%5d %-20s %-15s %4d-%02d-%02d\n", i + 1,
            o->nazwisko, o->imie,
            o->dataUrodz.rok, o->dataUrodz.mies,
            o->dataUrodz.dzien);
    }
}

void dopisywanie()
{
    osoba* o = malloc(sizeof(osoba));
    char c;
    
    printf("WPROWADZANIE DANYCH:\n");
    printf("Nazwisko: ");
    flush();
    wczytaj(o->nazwisko, 20);
    printf("Imie    : ");
    wczytaj(o->imie, 15);
    printf("Data urodzenia [r m d]: ");
    scanf("%d %d %d", &o->dataUrodz.rok, &o->dataUrodz.mies, &o->dataUrodz.dzien);
                    
    osoby = realloc(osoby, ++rozmiar * sizeof(osoba*));
    osoby[rozmiar - 1] = o;
}

void usuwanie()
{
    int numer;
    printf("podaj numer osoby do usunięcia (0 - wszystkie): ");
    scanf("%d", &numer);
    
    if (numer == 0)
    {
        for (int i = 0; i < rozmiar; i++) free(osoby[i]);
        osoby = realloc(osoby, 0);
        rozmiar = 0;
    }
    else if (numer > 0 && numer <= rozmiar)
    {
        free(osoby[numer]);
        osoby[numer] = NULL;
        rozmiar--;
    }
    else
    {
        printf("nieprawidłowy element");
        return;
    }
    
    zapis();
}

void program()
{
    printf("1) odczyt danych z pliku binarnego do tablicy struktur\n");
    printf("2) zapis danych z tablicy struktur do pliku binarnego\n");
    printf("3) wyświetlanie danych na ekranie\n");
    printf("4) dopisywanie nowych danych\n");
    printf("5) usuwanie danych\n");
    
    switch (getchar())
    {
        case '1': return odczyt();
        case '2': return zapis();
        case '3': return wyswietlanie();
        case '4': return dopisywanie();
        case '5': return usuwanie();
    }
    
    printf("nieprawidłowe działanie\n");
}

int main()
{
    osoby = malloc(0);
    char c;
    
    do
    {
        program();
        do
        {
            printf("\nk - koniec; Enter - kontynuacja:\n");
            flush();
            c = getchar();
        } while (c != 'k' && c != 'K' && c != '\n');
    }
    while (c == '\n');
    
    return 0;
}
