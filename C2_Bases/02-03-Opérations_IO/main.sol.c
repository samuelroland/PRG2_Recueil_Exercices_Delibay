#include <stdio.h>

int main(void) {
    char prenom[50];
    int age;

    printf("Entrez votre prénom: ");
    scanf("%s", prenom);

    printf("Entrez votre âge: ");
    scanf("%d", &age);

    printf("Bienvenue, %s! Vous avez %d ans.\n", prenom, age);

    return 0;
}
