#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Servico {
    int id;
    char descricao[100];
    char status; // 'P' (Pendente), 'E' (Em Execução), 'C' (Concluído)
    char prioridade; // 'A' (Alta), 'M' (Média), 'B' (Baixa)
    struct Servico *ant;
    struct Servico *prox;
};
typedef struct Servico Servico;

Servico *listaDeServicos = NULL;
int proximoId = 1;

void exibirNomesDesenvolvedores() {
    printf("------------------------------------------\n");
    printf("Sistema de Gerenciamento de Servicos\n");
    printf("Desenvolvido por: Leonardo Bora e Luan Constancio\n");
    printf("------------------------------------------\n\n");
}

// Helper to map priority char to a value for comparison
int getPrioridadeValor(char p) {
    if (p == 'A') return 3; // Alta
    if (p == 'M') return 2; // Média
    if (p == 'B') return 1; // Baixa
    return 0; // Desconhecida/Baixa
}

void insereServicoPrioridade(char descricao[], char prioridadeChar, char status) {
    Servico *novoServico = (Servico*)malloc(sizeof(Servico));
    if (!novoServico) {
        printf("Erro: Falha na alocacao de memoria!\n");
        return;
    }

    novoServico->id = proximoId++;
    strcpy(novoServico->descricao, descricao);
    novoServico->status = status;
    novoServico->prioridade = prioridadeChar;
    novoServico->ant = NULL;
    novoServico->prox = NULL;

    int novaPrioridadeVal = getPrioridadeValor(prioridadeChar);

    if (listaDeServicos == NULL || novaPrioridadeVal > getPrioridadeValor(listaDeServicos->prioridade)) {
        // Insere no início se a lista está vazia ou nova prioridade é maior que a da cabeça
        novoServico->prox = listaDeServicos;
        if (listaDeServicos != NULL) {
            listaDeServicos->ant = novoServico;
        }
        listaDeServicos = novoServico;
    } else {
        Servico *atual = listaDeServicos;
        // Procura a posição correta para inserir
        while (atual->prox != NULL && getPrioridadeValor(atual->prox->prioridade) >= novaPrioridadeVal) {
            atual = atual->prox;
        }
        novoServico->prox = atual->prox;
        if (atual->prox != NULL) {
            atual->prox->ant = novoServico;
        }
        atual->prox = novoServico;
        novoServico->ant = atual;
    }
    printf("Servico ID %d ('%s') adicionado com prioridade %c.\n", novoServico->id, descricao, prioridadeChar);
}

void atualizaStatusServico(int id, char novoStatus) {
    Servico *atual = listaDeServicos;
    while (atual != NULL) {
        if (atual->id == id) {
            atual->status = novoStatus;
            printf("Status do Servico ID %d atualizado para %c.\n", id, novoStatus);
            return;
        }
        atual = atual->prox;
    }
    printf("Servico ID %d nao encontrado.\n", id);
}

void exibeServicos() {
    Servico *atual = listaDeServicos;
    if (atual == NULL) {
        printf("Nenhum servico cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Servicos ---\n");
    // Formato: ID | Descrição | Prioridade | Status
    printf("%-5s | %-30s | %-10s | %-15s\n", "ID", "Descricao", "Prioridade", "Status");
    printf("------------------------------------------------------------------\n");
    while (atual != NULL) {
        char prioridadeStr[10];
        if (atual->prioridade == 'A') strcpy(prioridadeStr, "Alta");
        else if (atual->prioridade == 'M') strcpy(prioridadeStr, "Media");
        else if (atual->prioridade == 'B') strcpy(prioridadeStr, "Baixa");
        else strcpy(prioridadeStr, "N/A");

        char statusStr[15];
        if (atual->status == 'P') strcpy(statusStr, "Pendente");
        else if (atual->status == 'E') strcpy(statusStr, "Em Execucao");
        else if (atual->status == 'C') strcpy(statusStr, "Concluido");
        else strcpy(statusStr, "N/A");

        printf("%-5d | %-30s | %-10s | %-15s\n", atual->id, atual->descricao, prioridadeStr, statusStr);
        atual = atual->prox;
    }
    printf("------------------------------------------------------------------\n");
}

void liberaMemoria() {
    Servico *atual = listaDeServicos;
    Servico *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    listaDeServicos = NULL;
    printf("Memoria liberada.\n");
}

int main() {
    exibirNomesDesenvolvedores();
    int escolha;
    char descricao[100];
    char prioridade, status;
    int id;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Servico\n");
        printf("2. Atualizar Status de Servico\n");
        printf("3. Listar Servicos\n");
        printf("4. Creditos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar(); // Consumir o newline deixado pelo scanf

        switch (escolha) {
            case 1:
                printf("Descricao do servico: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = 0; // Remover newline

                do {
                    printf("Prioridade (A - Alta, M - Media, B - Baixa): ");
                    scanf(" %c", &prioridade);
                    prioridade = toupper(prioridade);
                } while (prioridade != 'A' && prioridade != 'M' && prioridade != 'B');

                do {
                    printf("Status (P - Pendente, E - Em Execucao, C - Concluido): ");
                    scanf(" %c", &status);
                    status = toupper(status);
                } while (status != 'P' && status != 'E' && status != 'C');
                getchar(); // Consumir o newline

                // Usando a função de inserção com prioridade
                insereServicoPrioridade(descricao, prioridade, status);
                break;
            case 2:
                printf("ID do servico para atualizar status: ");
                scanf("%d", &id);
                
                // Verificar se o ID existe antes de pedir o novo status
                Servico *encontrado = listaDeServicos;
                int idExiste = 0;
                while (encontrado != NULL) {
                    if (encontrado->id == id) {
                        idExiste = 1;
                        break;
                    }
                    encontrado = encontrado->prox;
                }
                
                if (!idExiste) {
                    printf("Servico ID %d nao encontrado.\n", id);
                    getchar(); // Consumir o newline
                    break;
                }
                
                do {
                    printf("Novo Status (P, E, C): ");
                    scanf(" %c", &status);
                    status = toupper(status);
                } while (status != 'P' && status != 'E' && status != 'C');
                getchar(); // Consumir o newline

                atualizaStatusServico(id, status);
                break;
            case 3:
                exibeServicos();
                break;
            case 4:
                printf("\n--- Creditos ---\n");
                printf("Sistema de Gerenciamento de Servicos\n");
                printf("Desenvolvido para a disciplina de Estrutura de Dados I\n");
                printf("Professor: Fabio Bettio\n");
                printf("Curso: Engenharia de Software\n\n");
                printf("Desenvolvedores:\n");
                printf("- Leonardo Bora (github.com/leonardobora)\n");
                printf("- Luan Constancio (github.com/luanconstancio)\n");
                printf("----------------\n");
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    liberaMemoria();
    return 0;
}