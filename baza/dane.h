#ifndef DANE_H
#define DANE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum {czlowiek, elf, krasnolud, ork, golem, zwierzoludz} Rasa;
typedef enum {wojownik, mag, kaplan, lowca, druid, zlodziej, tank, paladyn} Klasa;
typedef enum {aktywny, na_misji, ranny, zaginiony, zawieszony} Status;

typedef struct Bohater {
    char Unikalneimie[100];
    Rasa rasa;
    Klasa klasa;
    int doswiadczenie;
    int reputacja;
    Status status;
    struct Bohater *nastepny_bohater;
} Bohater;
extern const char* nazwarasy[];
extern const char* nazwaklasy[];
extern const char* obecnystatus[];
Bohater* stworz_bohatera();
void dodaj_bohatera(Bohater **HEAD, Bohater *nowy);
void wyswietl_liste(Bohater *HEAD);
void wyszukaj_bohaterow(Bohater *HEAD);
void usun_bohatera(Bohater **HEAD);
void modyfikuj_bohatera(Bohater *HEAD);
void sortuj_ranking(Bohater *HEAD);
void zapisz_baze(Bohater *HEAD);
void wczytaj_baze(Bohater **HEAD);
void zwolnij_pamiec(Bohater *HEAD);
#endif