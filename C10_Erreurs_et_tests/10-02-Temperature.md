
# Tests unitaires sur des fonctions de température avec ``CUnit``

## Prérequis
Il faut d'abord installer le *framework* ``CUnit`` à l'aide de la commande suivante :

~~~sh
sudo apt install libcunit1-ncurses-dev
~~~

## Fonctions de température

Soit une fonction qui calcule la température moyenne d’un tableau de températures (en degrés Celsius), 
ainsi qu’une fonction qui retourne la température maximale.

~~~cpp

#include <stddef.h>

// Retourne la température moyenne d'un tableau de températures
float temperature_moyenne(const float *tab, int taille) {
    float somme = 0.0f;

    if (tab == NULL || taille <= 0) {
        return 0.0f; // Convention : 0 pour tableau vide ou NULL
    }
    
    for (int i = 0; i < taille; ++i) {
        somme += tab[i];
    }
    return somme / taille;
}

// Retourne la température maximale d'un tableau de températures
float temperature_max(const float *tab, int taille) {
    float max = tab[0];

    if (tab == NULL || taille <= 0) {
        return 0.0f; // Convention : 0 pour tableau vide ou NULL
    }
    
    for (int i = 1; i < taille; ++i) {
        if (tab[i] > max) {
            max = tab[i];
        }
    }
    return max;
}
~~~

Écrivez ensuite des tests unitaires avec CUnit pour valider le bon fonctionnement de ces fonctions.
<p> 
Testez notamment :

* Le calcul de la moyenne sur un tableau de plusieurs valeurs

* Le calcul de la moyenne sur un tableau d’un seul élément

* La gestion d’un tableau vide (taille 0)

* La recherche du maximum sur un tableau de plusieurs valeurs

* La recherche du maximum sur un tableau d’un seul élément

<details>
<summary>Solution</summary>

Il s'agit d'une solution possible parmi d'autres.

~~~cpp

#include <CUnit/CUnit.h>
#include <CUnit/CUCurses.h>

// Fonctions à tester
float temperature_moyenne(const float *tab, int taille);
float temperature_max(const float *tab, int taille);

void test_temperature_moyenne(void) {
    float tab1[] = {10.0, 20.0, 30.0};
    float tab2[] = {42.0};
    float tab3[] = {};

    CU_ASSERT_DOUBLE_EQUAL(temperature_moyenne(tab1, 3), 20.0, 0.0001);

    CU_ASSERT_DOUBLE_EQUAL(temperature_moyenne(tab2, 1), 42.0, 0.0001);

    CU_ASSERT_DOUBLE_EQUAL(temperature_moyenne(NULL, 0), 0.0, 0.0001);

    CU_ASSERT_DOUBLE_EQUAL(temperature_moyenne(tab3, 0), 0.0, 0.0001);
}

void test_temperature_max(void) {
    float tab1[] = {10.0, 22.5, 18.0, 5.0};
    float tab2[] = {-5.0};
    float tab3[] = {};

    CU_ASSERT_DOUBLE_EQUAL(temperature_max(tab1, 4), 22.5, 0.0001);

    CU_ASSERT_DOUBLE_EQUAL(temperature_max(tab2, 1), -5.0, 0.0001);

    CU_ASSERT_DOUBLE_EQUAL(temperature_max(NULL, 0), 0.0, 0.0001);

    CU_ASSERT_DOUBLE_EQUAL(temperature_max(tab3, 0), 0.0, 0.0001);
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    pSuite = CU_add_suite("Test Températures", NULL, NULL);
    if (!pSuite)
        goto out;

    if (!CU_add_test(pSuite, "Moyenne", test_temperature_moyenne) ||
        !CU_add_test(pSuite, "Maximum", test_temperature_max))
        goto out;

    CU_curses_run_tests();

out:
    CU_cleanup_registry();
    return CU_get_error();
}

~~~

On remarque que pour chaque test, la fonction correspondante est appelée avec des arguments prédéfinis.

</details>

