#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[50];
    char corExercito[30];
    int tropas;
};

int main() {
    struct Territorio mapa[5]; // Vetor estático de 5 territórios
    int i;

    printf("=== Cadastro Inicial dos Territórios ===\n\n");

    // Cadastro dos territórios
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o \n do final

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa o buffer após o scanf

        printf("\n");
    }

    // Exibição dos territórios cadastrados
    printf("\n=== Estado Atual do Mapa ===\n");
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].corExercito);
        printf("Número de Tropas: %d\n\n", mapa[i].tropas);
    }

    return 0;
}