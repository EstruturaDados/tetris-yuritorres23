#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5  // Tamanho fixo da fila

// Estrutura que representa uma peça
typedef struct {
    int id;
    char tipo;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM];
    int inicio;
    int fim;
    int qtd;
} Fila;

// Função para gerar uma peça aleatória
Peca gerarPeca() {
    Peca p;
    p.id = rand() % 1000; // ID aleatório
    char tipos[] = {'A', 'B', 'C', 'D', 'E'};
    p.tipo = tipos[rand() % 5]; // Tipo aleatório
    return p;
}

// Inicializa a fila com 5 peças
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    for (int i = 0; i < TAM; i++) {
        f->pecas[i] = gerarPeca();
        f->fim = (f->fim + 1) % TAM;
        f->qtd++;
    }
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->qtd == TAM;
}

// Remove a peça da frente (jogar)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n Fila vazia, nada para remover!\n");
        return;
    }

    Peca p = f->pecas[f->inicio];
    printf("\n Peça jogada: ID=%d, Tipo=%c\n", p.id, p.tipo);

    f->inicio = (f->inicio + 1) % TAM;
    f->qtd--;
}

// Insere uma nova peça no final da fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n Fila cheia, não é possível adicionar nova peça!\n");
        return;
    }

    f->pecas[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->qtd++;
    printf("\n Nova peça adicionada: ID=%d, Tipo=%c\n", p.id, p.tipo);
}

// Mostra o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\n Fila atual (%d peças):\n", f->qtd);
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    int i = f->inicio;
    for (int count = 0; count < f->qtd; count++) {
        printf("[%d] ID=%d, Tipo=%c\n", count + 1, f->pecas[i].id, f->pecas[i].tipo);
        i = (i + 1) % TAM;
    }
}

// Função principal
int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Visualizar fila\n");
        printf("2. Jogar (remover) peça\n");
        printf("3. Inserir nova peça\n");
        printf("0. Sair\n");
        printf("===========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarFila(&fila);
                break;
            case 2:
                dequeue(&fila);
                break;
            case 3:
                enqueue(&fila, gerarPeca());
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

        mostrarFila(&fila); // Sempre mostra o estado atualizado

    } while (opcao != 0);

    return 0;
}
