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
    int reputacja;
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
    
    printf("Podaj poziom: ");
    scanf("%d", &nowy->doswiadczenie);

    printf("Podaj reputacje (0-100): ");
    scanf("%d", &nowy->reputacja);

    nowy->status = aktywny; 

    nowy->nastepny_bohater = NULL;

    printf("Bohater utworzony pomyslnie!\n");
    return nowy;
}
void dodaj_bohatera(Bohater **HEAD, Bohater *nowy) {
    nowy->nastepny_bohater = *HEAD;
    *HEAD = nowy;
}

void wyswietl_liste(Bohater *glowa) {
    if (glowa == NULL) {
        printf("\nRejestr gildii jest pusty.\n");
        return;
    }

    printf("REJESTR\n");
    Bohater *obecny = glowa; 
    int licznik = 1;
    while (obecny != NULL) {
        printf("Nr %d: %s\n", licznik, obecny->Unikalneimie); 
        printf("  Rasa:%s\n", nazwarasy[obecny->rasa]);
        printf("  Klasa:%s\n", nazwaklasy[obecny->klasa]);
        printf("  Poziom:%d\n", obecny->doswiadczenie);
        printf("  Reputacja:%d/100\n", obecny->reputacja);
        printf("  Status:%s\n", obecnystatus[obecny->status]);
        obecny = obecny->nastepny_bohater;
        licznik++;
    }
}
void wyszukaj_bohaterow(Bohater *HEAD) {
    if (HEAD == NULL) {
        printf("\n[INFO] Lista jest pusta, nie ma kogo szukac.\n");
        return;
    }

    int opcja;
    printf("\nWYSZUKIWANIE\n");
    printf("1. Szukaj po fragmencie imienia\n");
    printf("2. Szukaj po klasie\n");
    printf("Wybierz opcje: ");
    scanf("%d", &opcja);

    if (opcja == 1) {
        char szukane[100];
        printf("Wpisz fragment imienia: ");
        scanf(" %[^\n]", szukane);
        printf("\nWyniki wyszukiwania dla '%s':\n", szukane);
        Bohater *obecny = HEAD;
        int znaleziono = 0;
        while (obecny != NULL) {
            if (strstr(obecny->Unikalneimie, szukane) != NULL) {
                printf(" -> Znaleziono: %s (Klasa: %s, Poziom: %d ,Reputacja: %d)\n", 
                       obecny->Unikalneimie, nazwaklasy[obecny->klasa], obecny->doswiadczenie, obecny -> reputacja);
                znaleziono = 1;
            }
            obecny = obecny->nastepny_bohater;
        }
        if (znaleziono == 0) printf("Nikogo nie znaleziono.\n");

    } else if (opcja == 2) {
        int szukana_klasa;
        printf("\nJaka klase wyswietlic?\n");
        for(int i = 0; i < 8; i++) printf("%d. %s\n", i, nazwaklasy[i]);
        printf("Podaj numer: ");
        scanf("%d", &szukana_klasa);

        printf("\nWyniki dla klasy %s:\n", nazwaklasy[szukana_klasa]);
        Bohater *obecny = HEAD;
        int znaleziono = 0;

        while (obecny != NULL) {
            if (obecny->klasa == (Klasa)szukana_klasa) {
                 printf(" -> %s (Rasa: %s, Reputacja: %d)\n", 
                       obecny->Unikalneimie, nazwarasy[obecny->rasa], obecny->reputacja);
                znaleziono = 1;
            }
            obecny = obecny->nastepny_bohater;
        }
        if (znaleziono == 0) printf("[INFO] Brak bohaterow tej klasy.\n");
    } else {
        printf("Nieznana opcja wyszukiwania.\n");
    }
}
void usun_bohatera(Bohater **glowa) {
    if (*glowa == NULL) {
        printf("\n[BLAD] Rejestr jest pusty.\n");
        return;
    }
    char imie_do_usuniecia[100];
    printf("USUWANIE BOHATERA\n");
    printf("Podaj dokladne imie bohatera do zwolnienia: ");
    scanf(" %[^\n]", imie_do_usuniecia);
    Bohater *obecny = *glowa;
    Bohater *poprzedni = NULL;
    while (obecny != NULL) {
        if (strcmp(obecny->Unikalneimie, imie_do_usuniecia) == 0) {
            if (obecny->status == na_misji) {
                printf("Nie mozna usunac bohatera '%s'!\n", obecny->Unikalneimie);
                printf("Powod: Bohater przebywa aktualnie na misji.\n");
                return;
            }
            if (poprzedni == NULL) {
                *glowa = obecny->nastepny_bohater; 
            } 
            else {
                poprzedni->nastepny_bohater = obecny->nastepny_bohater; 
            }
            free(obecny); 
            printf("\n[SUKCES] Bohater '%s' zostal usuniety z rejestru.\n", imie_do_usuniecia);
            return;
        }
        poprzedni = obecny;
        obecny = obecny->nastepny_bohater;
    }

    printf("Nie znaleziono bohatera o imieniu '%s'.\n", imie_do_usuniecia);
}
void edytuj_bohatera(Bohater *glowa) {
    if (glowa == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    char szukane_imie[100];
    printf("EDYCJA DANYCH BOHATERA");
    printf("Podaj imie bohatera do edycji: ");
    scanf(" %[^\n]", szukane_imie);
    Bohater *obecny = glowa;
    while (obecny != NULL) {
        if (strcmp(obecny->Unikalneimie, szukane_imie) == 0) {
            printf("Edytujesz bohatera: %s (Obecny status: %s)\n", 
                   obecny->Unikalneimie, obecnystatus[obecny->status]);
            int wybor_edycji;
            printf("Co chcesz zmienic?\n");
            printf("1. Zmien status\n");
            printf("2. Aktualizuj doswiadczenie\n");
            printf("3. Zmien reputacje\n");
            printf("0. Anuluj\n");
            printf("Wybor: ");
            scanf("%d", &wybor_edycji);
            switch(wybor_edycji) {
                case 1: {
                    printf("Dostepne statusy:\n");
                    for(int i = 0; i < 5; i++) {
                        printf("%d. %s\n", i, obecnystatus[i]);
                    }
                    int nowy_status;
                    printf("Wybierz nowy status: ");
                    scanf("%d", &nowy_status);
                    
                    if (nowy_status >= 0 && nowy_status <= 4) {
                        obecny->status = (Status)nowy_status;
                        printf("[SUKCES] Status zmieniony na: %s\n", obecnystatus[nowy_status]);
                    } else {
                        printf("Niepoprawny numer statusu.\n");
                    }
                    break;
                }
                case 2: { 
                    int nowe_doswiadczenie;
                    printf("Obecne doswiadczenie: %d\n", obecny->doswiadczenie);
                    printf("Podaj NOWA wartosc doswiadczenia: ");
                    scanf("%d", &nowe_doswiadczenie);
                    obecny->doswiadczenie = nowe_doswiadczenie;
                    printf("Poziom doswiadczenia zaktualizowany.\n");
                    break;
                }
                case 3: { 
                    int zmieniona_reputacja;
                    printf("Obecna reputacja: %d\n", obecny->reputacja);
                    printf("Podaj NOWA wartosc reputacji (0-100): ");
                    scanf("%d", &zmieniona_reputacja);
                    if(zmieniona_reputacja < 0) zmieniona_reputacja = 0;
                    if(zmieniona_reputacja > 100) zmieniona_reputacja = 100;
                    obecny->reputacja = zmieniona_reputacja;
                    printf("Reputacja zaktualizowana.\n");
                    break;
                }
                case 0:
                    printf("Anulowano edycje.\n");
                    break;
                default:
                    printf("Nieznana opcja.\n");
            }
            return;
        }
        obecny = obecny->nastepny_bohater;
    }
    printf("Nie znaleziono bohatera o imieniu '%s'.\n", szukane_imie);
}
void zapisz_baze(Bohater *glowa) {
    FILE *plik = fopen("baza_gildii.txt", "w");

    if (plik == NULL) {
        printf("Blad otwarcia pliku do zapisu!\n");
        return;
    }

    Bohater *obecny = glowa;
    while (obecny != NULL) {
        fprintf(plik, "%s\n", obecny->Unikalneimie);
        fprintf(plik, "%d\n", obecny->rasa);
        fprintf(plik, "%d\n", obecny->klasa);
        fprintf(plik, "%d\n", obecny->doswiadczenie);
        fprintf(plik, "%d\n", obecny->reputacja);
        fprintf(plik, "%d\n", obecny->status);
        
        obecny = obecny->nastepny_bohater;
    }
    fclose(plik);
    printf("Stan gildii zostal zapisany w pliku 'baza_gildii.txt'.\n");
}
int main()
{
    Bohater *HEAD = NULL;
    int wybor;
    
    do{
        printf("\n---Witamy w gildi Poszukiwaczy Przygód---\n");
        printf("1. Zarejestruj się\n");
        printf("2. Wyświetl dane bohatera\n");
        printf("3. Wyszukaj bohatera\n");
        printf("4. Modyfikuj bohaterów \n"); 
        printf("5. Usuń bohatera\n");
        printf("0. Wyjscie\n");
        printf("Twoj wybor: ");
        scanf("%d", &wybor);
        switch(wybor) {
            case 1: {
                Bohater *nowy = stworz_bohatera();
                if (nowy != NULL) {
                    dodaj_bohatera(&HEAD, nowy); 
                }
                break;
            }
            case 2:
                wyswietl_liste(HEAD);
                break;
            case 3:
                wyszukaj_bohaterow(HEAD);
                break;
            case 4:
                modyfikuj_boahtera(HEAD);
                break;
            case 5:
                usun_bohatera(&HEAD); 
            break;
            case 0:
                zapisz_baze(HEAD); 
                printf("Narazie:D\n");
                break;
            default:
                printf("Nieznana opcja!\n");
        }
    } while(wybor !=0);
    return 0;
}