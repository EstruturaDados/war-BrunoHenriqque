#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    char cor[30];
    int tropas;
} Territorio;

void cadastrar(Territorio *t, int n);
void exibirMapa(const Territorio *t, int n);
void atacar(Territorio *t, int n);
void verificarMissao(const Territorio *t, int n, const char *missao);

int main() {
    srand(time(NULL));
    int n = 5;
    Territorio *mapa = calloc(n, sizeof(Territorio));

    cadastrar(mapa, n);

    const char *missao = (rand() % 2 == 0) ? "Destruir o exército Verde" : "Conquistar 3 territórios";
    printf("\n🎯 Sua missão: %s\n", missao);

    int opcao;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                atacar(mapa, n);
                break;
            case 2:
                verificarMissao(mapa, n, missao);
                break;
        }
    } while (opcao != 0);

    free(mapa);
    return 0;
}

void cadastrar(Territorio *t, int n) {
    printf("\n=== Cadastro dos Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        fgets(t[i].nome, sizeof(t[i].nome), stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("Cor: ");
        fgets(t[i].cor, sizeof(t[i].cor), stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &t[i].tropas);
        getchar();
    }
}

void exibirMapa(const Territorio *t, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("%s (%s): %d tropas\n", t[i].nome, t[i].cor, t[i].tropas);
    }
}

void atacar(Territorio *t, int n) {
    int a, d;
    printf("\nEscolha o território atacante (1-5): ");
    scanf("%d", &a);
    printf("Escolha o território defensor (1-5): ");
    scanf("%d", &d);
    getchar();

    if (a == d || a < 1 || d < 1 || a > n || d > n) {
        printf("Entrada inválida.\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n%s rolou %d | %s rolou %d\n", t[a-1].nome, dadoA, t[d-1].nome, dadoD);

    if (dadoA >= dadoD) {
        t[d-1].tropas--;
        printf("✅ %s venceu! %s perdeu 1 tropa.\n", t[a-1].nome, t[d-1].nome);
        if (t[d-1].tropas <= 0) {
            printf("🏴 %s foi conquistado!\n", t[d-1].nome);
        }
    } else {
        t[a-1].tropas--;
        printf("❌ %s resistiu! %s perdeu 1 tropa.\n", t[d-1].nome, t[a-1].nome);
    }

    exibirMapa(t, n);
}

void verificarMissao(const Territorio *t, int n, const char *missao) {
    printf("\n🎯 Missão: %s\n", missao);

    if (strcmp(missao, "Destruir o exército Verde") == 0) {
        int vivos = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(t[i].cor, "Verde") == 0 && t[i].tropas > 0)
                vivos = 1;
        }
        if (!vivos) printf("🏆 Missão concluída!\n");
        else printf("A missão ainda não foi cumprida.\n");
    } else {
        int conquistados = 0;
        for (int i = 0; i < n; i++)
            if (t[i].tropas == 0) conquistados++;

        if (conquistados >= 3)
            printf("🏆 Missão concluída!\n");
        else
            printf("A missão ainda não foi cumprida.\n");
    }
}
