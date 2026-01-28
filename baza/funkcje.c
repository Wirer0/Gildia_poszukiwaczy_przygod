#include "dane.h"
const char* nazwarasy[] = {"Czlowiek", "Elf", "Krasnolud", "ork", "Golem", "Zwierzoludz"};
const char* nazwaklasy[] = {"Wojownik", "Mag", "Kaplan", "Lowca", "Druid", "Zlodziej", "Tank", "Paladyn"};
const char* obecnystatus[] = {"Aktywny", "Na misji", "Ranny", "Zaginiony", "Zawieszony"};
Bohater* stworz_bohatera() {
    Bohater *nowy = (Bohater*)malloc(sizeof(Bohater));
    if (nowy == NULL) {
        printf("Blad alokacji pamieci!\n");
        exit(1);
    }
    printf("Podaj unikalne imie bohatera: ");
    scanf(" %[^\n]", nowy->Unikalneimie); 

    int i, wybor_rasy;
    printf("Dostepne rasy:\n");
    for(i = 0; i < 6; i++) {
        printf("%d. %s\n", i, nazwarasy[i]);
    }
    printf("Wybierz numer rasy: ");
    scanf("%d", &wybor_rasy); 
    if (wybor_rasy < 0 || wybor_rasy > 5) wybor_rasy = 0; 
    nowy->rasa = (Rasa)wybor_rasy;

    int wybor_klasy;
    printf("Dostepne klasy:\n");
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

void wyswietl_liste(Bohater *HEAD) {
    if (HEAD == NULL) {
        printf("Rejestr gildii jest pusty.\n");
        return;
    }
    printf("REJESTR\n");
    Bohater *obecny = HEAD; 
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
        printf("Lista jest pusta, nie ma kogo szukac.\n");
        return;
    }
    int opcja;
    printf("WYSZUKIWANIE\n");
    printf("1. Szukaj po fragmencie imienia\n");
    printf("2. Szukaj po klasie\n");
    printf("Wybierz opcje: ");
    scanf("%d", &opcja);

    if (opcja == 1) {
        char szukane[100];
        printf("Wpisz fragment imienia: ");
        scanf(" %[^\n]", szukane);
        printf("Wyniki wyszukiwania dla '%s':\n", szukane);
        Bohater *obecny = HEAD;
        int znaleziono = 0;
        while (obecny != NULL) {
            if (strstr(obecny->Unikalneimie, szukane) != NULL) {
                printf(" -> Znaleziono: %s (Klasa: %s, Poziom: %d, Reputacja: %d)\n", 
                       obecny->Unikalneimie, nazwaklasy[obecny->klasa], obecny->doswiadczenie, obecny->reputacja);
                znaleziono = 1;
            }
            obecny = obecny->nastepny_bohater;
        }
        if (znaleziono == 0) printf("Nikogo nie znaleziono.\n");

    } else if (opcja == 2) {
        int szukana_klasa;
        printf("Jaka klase wyswietlic?\n");
        for(int i = 0; i < 8; i++) printf("%d. %s\n", i, nazwaklasy[i]);
        printf("Podaj numer: ");
        scanf("%d", &szukana_klasa);
        printf("Wyniki dla klasy %s:\n", nazwaklasy[szukana_klasa]);
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
        if (znaleziono == 0) printf("Brak bohaterow tej klasy.\n");
    } else {
        printf("Nieznana opcja wyszukiwania.\n");
    }
}

void usun_bohatera(Bohater **HEAD) {
    if (*HEAD == NULL) {
        printf("Rejestr jest pusty.\n");
        return;
    }
    char imie_do_usuniecia[100];
    printf("USUWANIE BOHATERA\n");
    printf("Podaj dokladne imie bohatera do zwolnienia: ");
    scanf(" %[^\n]", imie_do_usuniecia);
    Bohater *obecny = *HEAD;
    Bohater *poprzedni = NULL;
    while (obecny != NULL) {
        if (strcmp(obecny->Unikalneimie, imie_do_usuniecia) == 0) {
            if (obecny->status == na_misji) {
                printf("Nie mozna usunac bohatera '%s'!\n", obecny->Unikalneimie);
                printf("Powod: Bohater przebywa aktualnie na misji.\n");
                return;
            }
            if (poprzedni == NULL) {
                *HEAD = obecny->nastepny_bohater; 
            } else {
                poprzedni->nastepny_bohater = obecny->nastepny_bohater; 
            }
            free(obecny); 
            printf("Bohater '%s' zostal usuniety z rejestru.\n", imie_do_usuniecia);
            return;
        }
        poprzedni = obecny;
        obecny = obecny->nastepny_bohater;
    }
    printf("Nie znaleziono bohatera o imieniu '%s'.\n", imie_do_usuniecia);
}

void modyfikuj_bohatera(Bohater *HEAD) {
    if (HEAD == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }
    char szukane_imie[100];
    printf("EDYCJA DANYCH BOHATERA\n");
    printf("Podaj imie bohatera do edycji: ");
    scanf(" %[^\n]", szukane_imie);
    Bohater *obecny = HEAD;
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
                        printf("Status zmieniony na: %s\n", obecnystatus[nowy_status]);
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

void zapisz_baze(Bohater *HEAD) {
    FILE *plik = fopen("baza_gildii.txt", "w");
    if (plik == NULL) {
        printf("Blad otwarcia pliku do zapisu!\n");
        return;
    }
    Bohater *obecny = HEAD;
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

void wczytaj_baze(Bohater **HEAD) {
    FILE *plik = fopen("baza_gildii.txt", "r");
    if (plik == NULL) {
        printf("Brak pliku zapisu. Tworze nowa, czysta baze.\n");
        return;
    }
    char tempImie[100];
    int tempRasa, tempKlasa, tempExp, tempRep, tempStatus;
    while (fscanf(plik, " %[^\n]", tempImie) != EOF) { 
        fscanf(plik, "%d", &tempRasa);
        fscanf(plik, "%d", &tempKlasa);
        fscanf(plik, "%d", &tempExp);
        fscanf(plik, "%d", &tempRep);
        fscanf(plik, "%d", &tempStatus);
        Bohater *nowy = (Bohater*)malloc(sizeof(Bohater));
        strcpy(nowy->Unikalneimie, tempImie); 
        nowy->rasa = (Rasa)tempRasa;
        nowy->klasa = (Klasa)tempKlasa;
        nowy->doswiadczenie = tempExp;
        nowy->reputacja = tempRep;
        nowy->status = (Status)tempStatus;
        nowy->nastepny_bohater = NULL;
        dodaj_bohatera(HEAD, nowy);
    }
    fclose(plik);
    printf("Wczytano dane z pliku.\n");
}

void zwolnij_pamiec(Bohater *HEAD) {
    Bohater *temp;
    while (HEAD != NULL) {
        temp = HEAD;
        HEAD = HEAD->nastepny_bohater;
        free(temp);
    }
    printf("Pamiec zostala wyczyszczona.\n");
}

void sortuj_ranking(Bohater *HEAD) {
    if (HEAD == NULL || HEAD->nastepny_bohater == NULL) {
        printf("Za malo bohaterow do stworzenia rankingu.\n");
        return;
    }
    int zamiana;
    Bohater *ptr1;
    Bohater *lptr = NULL;
    do {
        zamiana = 0;
        ptr1 = HEAD;
        while (ptr1->nastepny_bohater != lptr) {
            if (ptr1->reputacja < ptr1->nastepny_bohater->reputacja) { 
                char tempImie[100];
                strcpy(tempImie, ptr1->Unikalneimie);
                strcpy(ptr1->Unikalneimie, ptr1->nastepny_bohater->Unikalneimie);
                strcpy(ptr1->nastepny_bohater->Unikalneimie, tempImie);
                Rasa tempRasa = ptr1->rasa;
                ptr1->rasa = ptr1->nastepny_bohater->rasa;
                ptr1->nastepny_bohater->rasa = tempRasa;
                Klasa tempKlasa = ptr1->klasa;
                ptr1->klasa = ptr1->nastepny_bohater->klasa;
                ptr1->nastepny_bohater->klasa = tempKlasa;
                int tempExp = ptr1->doswiadczenie;
                ptr1->doswiadczenie = ptr1->nastepny_bohater->doswiadczenie;
                ptr1->nastepny_bohater->doswiadczenie = tempExp;
                int tempRep = ptr1->reputacja;
                ptr1->reputacja = ptr1->nastepny_bohater->reputacja;
                ptr1->nastepny_bohater->reputacja = tempRep;
                Status tempStatus = ptr1->status;
                ptr1->status = ptr1->nastepny_bohater->status;
                ptr1->nastepny_bohater->status = tempStatus;
                zamiana = 1;
            }
            ptr1 = ptr1->nastepny_bohater;
        }
        lptr = ptr1;
    } while (zamiana);
    printf("Posortowano bohaterow wedlug reputacji.\n");
    printf("Wybierz opcje 'Wyswietl', aby zobaczyc ranking.\n");
}