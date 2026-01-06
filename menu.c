#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum{czlowiek, elf, krasnolud, ork, golem, zwierzoludz} Rasa;
typedef enum{wojownik, mag, kaplan, lowca, druid, zlodziej, tank, paladyn} Klasa;
typedef enum{aktywny, na_misji, ranny, zaginiony, zawieszony} Status;
typedef struct Bohater {
    char Unikalneimie[100];
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
Bohater* stworz_bohatera() {

    Bohater *nowy = (Bohater*)malloc(sizeof(Bohater));

    if (nowy == NULL) {
        printf("Blad alokacji pamieci!\n");
        exit(1);
    }
    printf("\nPodaj unikalne imie bohatera: ");
    scanf(" %[^\n]", nowy->Unikalneimie); 

    int i, wybor_rasy;
    printf("\nDostepne rasy:\n");
    for(i = 0; i < 6; i++) {
        printf("%d. %s\n", i, nazwarasy[i]);
    }
    printf("Wybierz numer rasy: ");
    scanf("%d", &wybor_rasy); 
    if (wybor_rasy < 0 || wybor_rasy > 5) wybor_rasy = 0; 
    nowy->rasa = (Rasa)wybor_rasy;

    int wybor_klasy;
    printf("\nDostepne klasy:\n");
    for(i = 0; i < 8; i++) {
        printf("%d. %s\n", i, nazwaklasy[i]);
    }
    printf("Wybierz numer klasy: ");
    scanf("%d", &wybor_klasy); 
    if (wybor_klasy < 0 || wybor_klasy > 7) wybor_klasy = 0; 
    nowy->klasa = (Klasa)wybor_klasy;
    
    nowy -> doswiadczenie = 1;

    printf("Podaj reputacje (0-100): ");
    scanf("%d", &nowy->Reputacja);

    nowy->status = aktywny; 

    nowy->nastepny_bohater = NULL;

    printf("Bohater utworzony pomyslnie!\n");
    return nowy;
}
int main()
{
    int wybor;
    do{
        printf("\n---Witamy w gildi Poszukiwaczy Przygód---\n");
        printf("1. Zarejestruj się\n");
        printf("2. Wyświetl dane bohatera\n");
        printf("3. Ranking bohaterów \n"); 
        printf("4. Usuń bohatera\n");
        printf("0. Wyjscie\n");
        printf("Twoj wybor: ");
    } while(wybor !=0);
    return 0;
}