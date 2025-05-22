
# Tests unitaires pour une gestion de pile avec ``CUnit``

## Prérequis
Il faut d'abord installer le *framework* ``CUnit`` à l'aide de la commande suivante :

~~~sh
sudo apt install libcunit1-ncurses-dev
~~~

## Gestion d'une pile d'entiers

Vous allez écrire des tests unitaires pour une structure de pile d’entiers (Stack).

L’un des tests exigera une préparation spécifique : il faudra empiler plusieurs valeurs avant de vérifier le comportement de la pile.

Voici les fonctions à tester :

~~~cpp

#include <stdbool.h>

#define STACK_MAX 10

typedef struct {
    int data[STACK_MAX];
    int top; // Indice du prochain emplacement libre (0 si vide)
} Stack;

// Initialise la pile (vide)
void stack_init(Stack *s) {
    s->top = 0;
}

// Retourne vrai si la pile est vide
bool stack_is_empty(Stack *s) {
    return s->top == 0;
}

// Empile une valeur. Retourne vrai si succès, faux si pile pleine.
bool stack_push(Stack *s, int value) {

    if (s->top >= STACK_MAX) {
        return false; // pile pleine
    }
    s->data[s->top] = value;
    s->top++;

    return true;
}

// Dépile et retourne la valeur au sommet. Retourne -1 si pile vide.
int stack_pop(Stack *s) {

    if (stack_is_empty(s)) {
        return -1; // pile vide
    }
    s->top--;

    return s->data[s->top];
}


~~~

On notera que :

* La pile est vide si top == 0.
* La pile est pleine si top == STACK_MAX.
* On empile en écrivant à l’indice top, puis on incrémente top.
* On dépile en décrémentant top, puis en lisant la valeur correspondante.
* Si on tente de dépiler une pile vide, on retourne -1 comme valeur d’erreur (convention simple pour l’exercice).

### Objectif 
Écrivez les tests unitaires suivants avec CUnit :

#### Test de pile vide 

* Vérifiez qu’une pile nouvellement initialisée est vide et que stack_pop retourne -1.

#### Test d’empilement et de dépilement (avec préparation) :

* Avant les assertions, empilez plusieurs valeurs (par exemple 10, 20, 30), puis :

* Vérifiez que la pile n’est pas vide.

* Dépilez deux valeurs et vérifiez qu’elles sont dans le bon ordre (LIFO).

* Empilez une nouvelle valeur, vérifiez qu’elle est bien au sommet.

* Dépilez tous les éléments restants et vérifiez que la pile redevient vide.

#### Test de débordement

* Empilez jusqu’à la capacité maximale, puis vérifiez qu’un empilement supplémentaire échoue.

Dans le test d’empilement/dépilement, effectuez la préparation (empilement de plusieurs valeurs) dans la fonction de test, avant les assertions.


<details>
<summary>Solution</summary>
 
Voici un exemple de tests:

~~~cpp

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

static Stack test_stack;

// Fonction appelée avant chaque test
int init_suite(void) {
    stack_init(&test_stack);
    return 0;
}

// Fonction appelée après chaque test (inutile ici)
int clean_suite(void) {
    return 0;
}

// Test pile vide
void test_pile_vide(void) {
    CU_ASSERT_TRUE(stack_is_empty(&test_stack));
    CU_ASSERT_EQUAL(stack_pop(&test_stack), -1);
}

// Test empiler/dépiler avec préparation locale
void test_empiler_depiler(void) {
        
    // Préparation : on empile plusieurs valeurs
    stack_push(&test_stack, 10);
    stack_push(&test_stack, 20);
    stack_push(&test_stack, 30);

    CU_ASSERT_FALSE(stack_is_empty(&test_stack));
    CU_ASSERT_EQUAL(stack_pop(&test_stack), 30);
    CU_ASSERT_EQUAL(stack_pop(&test_stack), 20);

    stack_push(&test_stack, 40);
    CU_ASSERT_EQUAL(stack_pop(&test_stack), 40);
    CU_ASSERT_EQUAL(stack_pop(&test_stack), 10);

    CU_ASSERT_TRUE(stack_is_empty(&test_stack));
}

// Test de débordement
void test_debordement(void) {
    for (int i = 0; i < STACK_MAX; ++i) {
        CU_ASSERT_TRUE(stack_push(&test_stack, i));
    }
    // La pile est pleine, le push suivant doit échouer
    CU_ASSERT_FALSE(stack_push(&test_stack, 100));
}

int main(void) {
    CU_pSuite pSuite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    pSuite = CU_add_suite("Suite Pile", init_suite, clean_suite);
    if (pSuite == NULL)
        goto cleanup;

    if (!CU_add_test(pSuite, "Pile vide", test_pile_vide) ||
        !CU_add_test(pSuite, "Empiler/Dépiler avec préparation", test_empiler_depiler) ||
        !CU_add_test(pSuite, "Débordement", test_debordement))
        goto cleanup;

    CU_basic_run_tests();

cleanup:
    CU_cleanup_registry();
    return CU_get_error();
}

~~~