#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum{czlowiek, elf, krasnolud, ork, golem, zwierzoludz} Rasa;
typedef enum{wojownik, mag, kaplan, lowca, druid, zlodziej, tank, paladyn} Klasa;
typedef enum{aktywny, na_misji, ranny, zaginiony, zawieszony} Status;
typedef struct Bohater {
    char Imie[100];
    Rasa rasa;
    Klasa klasa;
    int doswiadczenie;
    int Reputacja;
    Status status;
    struct Bohater *nastepny_bohater;
} Bohater;
const char* nazwarasy[] = {"Czlowiek", "Elf", "Krasnolud", "ork", "Golem", "Zwierzoludz"};
const char* nazwaklasy[] = {"Wojownik", "Mag", "Kaplan", "Lowca", "Druid", "Zlodziej", "Tank", "Paladyn"};
const char* obecnystatus[] = {"Aktywny", "Na misji", "Ranny", "Zaginiony", "Zawieszony"};

int main()
{
    return 0;
}