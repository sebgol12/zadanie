#include <stdio.h>
#include <stdlib.h>


struct baza
{
    struct rekord* tab_rekordow;
    int liczba_rekordow;
};

struct rekord
{
    char* imie;
    char* nazwisko;
    long int numer;
};

int dodaj_rekord(struct baza* b, struct rekord* rek)
{
    struct rekord* tab_rekordow2 = malloc((b->liczba_rekordow + 1) * sizeof(struct rekord));
    int i;
    if(tab_rekordow2 != NULL)
    {
        for(i = 0; i < b->liczba_rekordow; ++i)
        {
            tab_rekordow2[i] = b->tab_rekordow[i];
        }
        tab_rekordow2[b->liczba_rekordow] = *rek;
        free(b->tab_rekordow);
        b->tab_rekordow = tab_rekordow2;
        b->liczba_rekordow += 1;
        return 0;
    }
    else
    {
        return -1;
    }
}

int znajdz_indeks(struct baza* b, long int numer)
{
    int i;
    for(i = 0; i < b->liczba_rekordow; ++i)
    {
        if(b->tab_rekordow[i].numer == numer)
        {
            return i;
        }
    }
    return -1;
}
void wypisz_rekord(struct baza* b, int indeks)
{
    struct rekord rek = b->tab_rekordow[indeks];
    printf("Imie: %s\n", rek.imie);
    printf("Nazwisko: %s\n", rek.nazwisko);
    printf("Numer: %ld\n", rek.numer);
}
void usun_rekord(struct baza* b, int indeks)
{
    int i;
    int t = 0;
    struct rekord* tab_rekordow2 = malloc((b->liczba_rekordow - 1)*sizeof(struct rekord));
    for(i = 0; i < b->liczba_rekordow - 1; ++i)
        {
            if(i == indeks)
            {
                t = 1;
            }
            tab_rekordow2[i] = b->tab_rekordow[i+t];
        }
        if(t == 0)
        {
            free(tab_rekordow2);
            return;
        }
        else
        {
            b->liczba_rekordow -= 1;
            free(b->tab_rekordow);
            b->tab_rekordow = tab_rekordow2;
        }
}

int main()
{

    struct baza k;
    k.tab_rekordow = NULL;
    k.liczba_rekordow = 0;

    struct rekord r1;
    r1.imie = "Jan";
    r1.nazwisko = "Kowalski";
    r1.numer = 123456789;

    struct rekord r2;
    r2.imie = "Druga";
    r2.nazwisko = "Osoba";
    r2.numer = 123321123;

    int code = dodaj_rekord(&k, &r1);
    if(code == -1)
    {
        printf("blad dodawania");
        return 0;
    }

    code = dodaj_rekord(&k, &r2);
    if(code == -1)
    {
        printf("blad dodawania");
        return 0;
    }

    int id = znajdz_indeks(&k, 123123123);
    if(id == -1)
    {
        printf("blad szukania");
        return 0;
    }
    wypisz_rekord(&k, id);
    usun_rekord(&k, 1);
    usun_rekord(&k, 0);
    return 0;

}
