#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t n = 0;  // nombre d'elements
    size_t cap = 1;// capacite du tableau
    int *old_tab, *tab;

    tab = (int *) malloc(sizeof(int));
    if (tab == NULL) {
        printf("Erreur d'allocation de memoire\n");
        return 1;
    }

    while (true) {
        printf("Entrez un entier positif (une lettre pour finir): ");
        int i;
        if (scanf("%d", &i) != 1) {
            // L'utilisateur n'a pas entré un entier.
            // Nettoyer le buffer d'entrée et sortir de la boucle
            while (getchar() != '\n');
            break;
        }
        if (n == cap) {
            // Le tableau est plein, redimensionner
            old_tab = tab;
            tab = realloc(old_tab, cap * 2 * sizeof(int));
            if (tab == NULL) {
                // Mémoire pleine. On conserve l'ancien tableau
                // et on sort de la boucle
                printf("Mémoire pleine !\n");
                tab = old_tab;
                break;
            } else {
                // Redimensionnement réussi
                cap *= 2;
            }
        }
        tab[n++] = i;
    }

    printf("Vous avez entre: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    free(tab);
}
