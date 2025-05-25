#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Estrutura para representar um cliente
typedef struct Cliente {
    int senha;
    char cpf[12];
    char nome[100];
    int idade;
    char sexo;
    struct Cliente* proximo;
} Cliente;

// Estrutura para representar a fila
typedef struct {
    Cliente* inicio;
    Cliente* fim;
    int contador_senha;
    int tamanho;
} FilaAtendimento;

// Protótipos das funções
void inicializarFila(FilaAtendimento* fila);
void adicionarCliente(FilaAtendimento* fila);
void atenderCliente(FilaAtendimento* fila);
void listarNumeroClientes(FilaAtendimento* fila);
void listarTodosClientes(FilaAtendimento* fila);
void listarPrimeiroCliente(FilaAtendimento* fila);
void listarUltimoCliente(FilaAtendimento* fila);
void liberarFila(FilaAtendimento* fila);
void limparBuffer();

int main() {
    FilaAtendimento fila;
    inicializarFila(&fila);
    int opcao;
    
    do {
        printf("\n--- Sistema de Atendimento ---\n");
        printf("1. Adicionar cliente a fila de espera\n");
        printf("2. Atender primeiro cliente da fila\n");
        printf("3. Listar numero de clientes na fila\n");
        printf("4. Listar todos os clientes na fila\n");
        printf("5. Listar informacoes do primeiro cliente\n");
        printf("6. Listar informacoes do ultimo cliente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                adicionarCliente(&fila);
                break;
            case 2:
                atenderCliente(&fila);
                break;
            case 3:
                listarNumeroClientes(&fila);
                break;
            case 4:
                listarTodosClientes(&fila);
                break;
            case 5:
                listarPrimeiroCliente(&fila);
                break;
            case 6:
                listarUltimoCliente(&fila);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    liberarFila(&fila);
    return 0;
}

// Inicializa a fila
void inicializarFila(FilaAtendimento* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->contador_senha = 1;
    fila->tamanho = 0;
}

// Adiciona um novo cliente à fila
void adicionarCliente(FilaAtendimento* fila) {
    Cliente* novo = (Cliente*)malloc(sizeof(Cliente));
    if (!novo) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    
    novo->senha = fila->contador_senha++;
    novo->proximo = NULL;
    
    printf("Digite o CPF do cliente: ");
    fgets(novo->cpf, 12, stdin);
    novo->cpf[strcspn(novo->cpf, "\n")] = '\0';
    limparBuffer();
    
    printf("Digite o nome completo do cliente: ");
    fgets(novo->nome, 100, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';
    
    printf("Digite a idade do cliente: ");
    scanf("%d", &novo->idade);
    
    printf("Digite o sexo do cliente (M/F): ");
    scanf(" %c", &novo->sexo);
    limparBuffer();
    
    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
    printf("Cliente adicionado com sucesso! Senha: %d\n", novo->senha);
}

// Atende o primeiro cliente da fila
void atenderCliente(FilaAtendimento* fila) {
    if (fila->inicio == NULL) {
        printf("Nao ha clientes na fila para atender!\n");
        return;
    }
    
    Cliente* temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    printf("Cliente atendido:\n");
    printf("Senha: %d\n", temp->senha);
    printf("CPF: %s\n", temp->cpf);
    printf("Nome: %s\n", temp->nome);
    printf("Idade: %d\n", temp->idade);
    printf("Sexo: %c\n", temp->sexo);
    
    free(temp);
    fila->tamanho--;
}

// Lista o número de clientes na fila
void listarNumeroClientes(FilaAtendimento* fila) {
    printf("Numero de clientes aguardando atendimento: %d\n", fila->tamanho);
}

// Lista todos os clientes na fila
void listarTodosClientes(FilaAtendimento* fila) {
    if (fila->inicio == NULL) {
        printf("Nao ha clientes na fila!\n");
        return;
    }
    
    Cliente* atual = fila->inicio;
    printf("\n--- Clientes na fila ---\n");
    while (atual != NULL) {
        printf("Senha: %d | CPF: %s | Nome: %s | Idade: %d | Sexo: %c\n", 
               atual->senha, atual->cpf, atual->nome, atual->idade, atual->sexo);
        atual = atual->proximo;
    }
}

// Lista informações do primeiro cliente
void listarPrimeiroCliente(FilaAtendimento* fila) {
    if (fila->inicio == NULL) {
        printf("Nao ha clientes na fila!\n");
        return;
    }
    
    printf("\n--- Primeiro cliente na fila ---\n");
    printf("Senha: %d\n", fila->inicio->senha);
    printf("CPF: %s\n", fila->inicio->cpf);
    printf("Nome: %s\n", fila->inicio->nome);
    printf("Idade: %d\n", fila->inicio->idade);
    printf("Sexo: %c\n", fila->inicio->sexo);
}

// Lista informações do último cliente
void listarUltimoCliente(FilaAtendimento* fila) {
    if (fila->fim == NULL) {
        printf("Nao ha clientes na fila!\n");
        return;
    }
    
    printf("\n--- Ultimo cliente na fila ---\n");
    printf("Senha: %d\n", fila->fim->senha);
    printf("CPF: %s\n", fila->fim->cpf);
    printf("Nome: %s\n", fila->fim->nome);
    printf("Idade: %d\n", fila->fim->idade);
    printf("Sexo: %c\n", fila->fim->sexo);
}

// Libera a memória alocada para a fila
void liberarFila(FilaAtendimento* fila) {
    Cliente* atual = fila->inicio;
    while (atual != NULL) {
        Cliente* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

// Limpa o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
