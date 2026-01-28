#include "dane.h"

int main()
{
    Bohater *HEAD = NULL;
    wczytaj_baze(&HEAD);
    int wybor;
    
    do{
        printf("\n---Witamy w gildi Poszukiwaczy Przygód---\n");
        printf("1. Zarejestruj się\n");
        printf("2. Wyświetl dane bohaterów\n");
        printf("3. Wyszukaj bohatera\n");
        printf("4. Modyfikuj bohaterów \n"); 
        printf("5. Usuń bohatera\n");
        printf("6. Ranking bohaterów\n");
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
                modyfikuj_bohatera(HEAD);
                break;
            case 5:
                usun_bohatera(&HEAD); 
            break;
            case 6:
                sortuj_ranking(HEAD);
                wyswietl_liste(HEAD);
                break;
            case 0:
                zapisz_baze(HEAD); 
                zwolnij_pamiec(HEAD);
                printf("Narazie:D\n");
                break;
            default:
                printf("Nieznana opcja!\n");
        }
    } while(wybor !=0);
    return 0;
}