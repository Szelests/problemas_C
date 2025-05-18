/*
    Escrever um programa    em C (no mínimo a função main(), uma função inserir e uma função listar todos), utilizando uma Lista Encadeada Simples, cujos elementos são inseridos na lista em ordem crescente (nomes em ordem alfabética). Considere a seguinte estrutura:
*/

/*
    Funções necessárias:
    * Relacionado a lista:
        - função para inicializar a lista;
        - função para inserir um novo elemento na lista;
        - função para listar todos os elementos da lista;
    
    * Relacionado a string:
        - função para verificar se está em maiusculo ou minusculo;
        - função para transformar a string em maiusculo;
        - função para comparar se a string é maior ou menor que a outra;
        - função para transformar a string em minusculo e deixar uppercase a primeira letra;
        ------------------------------------------------------
        → A função strcmp() já faz isso, então não precisamos implementar essas funções.

*/ 

#include <stdio.h>
#include <stdlib.h>

#include <string.h> // Para usar a função strcpy() e strcmp()

// Definição da estrutura do elemento da lista encadeada
struct elemento {
    char nome[40];
    struct elemento *prox;
};

typedef struct elemento Nodo; 

// Função para inicializar a lista encadeada
void inicializar_lista(Nodo **head) 
{
    *head = NULL;
}

// Função para criar um novo elemento e inserir na lista em ordem crescente
Nodo *insert_element(Nodo **head, char *name) 
{
    if (name == NULL) 
    {
        printf("Error: name cannot be NULL.\n");
        return NULL;
    }

    Nodo *new_element = (Nodo*)malloc(sizeof(Nodo));
    if (new_element == NULL) 
    {
        printf("Error allocating memory.\n");
        return NULL;
    }
    
    // Copia o nome para o novo elemento
    /*
        Em C não se pode atribuir diretamete uma string a outra string,
        é necessário usar a função strcpy() para copiar o conteúdo de uma string para outra.
    */ 
    strcpy(new_element->nome, name);
    new_element->prox = NULL;

    // Se a lista estiver vazia ou o novo elemento deve ser o primeiro
    if (*head == NULL || strcmp((*head)->nome, new_element->nome) > 0) 
    {
        new_element->prox = *head;
        *head = new_element;
        return new_element;
    }

    // Percorre a lista para encontrar a posição correta para inserir o novo elemento
    /*
        A comparação é feita com strcmp() para verificar a ordem alfabética.
        Se o nome do elemento atual for maior que o novo elemento, insere o novo elemento antes do atual.
        Caso contrário, continua percorrendo a lista até encontrar a posição correta.
        O loop continua enquanto o próximo elemento não for NULL e o nome do próximo elemento for menor que o novo elemento.
        ==========================================================================
        * A vantagem é que não precisamos transformar o nome em maiúsculo ou minúsculo, pois a comparação é feita diretamente com strcmp().
    */ 
    Nodo *current = *head;
    while (current->prox != NULL && strcmp(current->prox->nome, new_element->nome) < 0) 
    {
        current = current->prox;
    }

    // Insere o novo elemento na lista
    new_element->prox = current->prox;
    current->prox = new_element;

    return new_element;
}

// Função para listar todos os elementos da lista encadeada
void listar_elementos(Nodo* head)
{
    if (head == NULL)
    {
        printf("Lista está vazia.\n");
        return;
    }
    
    // Percorre a lista e imprime os nomes
    while(head != NULL) 
    {
        printf("%s\n", head->nome);
        head = head->prox;
    }

}

// Função para liberar a memória da lista encadeada
void liberar_lista(Nodo **head) 
{

    if (head == NULL || *head == NULL) 
    {
        return;
    }

    // Percorre a lista e libera cada elemento
    Nodo *current = *head;
    Nodo *next_element;

    while (current != NULL) 
    {
        next_element = current->prox;
        free(current);
        current = next_element;
    }

    *head = NULL;
}

void main()
{
    Nodo *head = NULL;
    char nome[40];
    int i = 0, n = 5; // Número de nomes a serem inseridos

    inicializar_lista(&head);

    // Insere os nomes na lista
    for (i = 0; i < n; i++) 
    {
        printf("Digite o nome %d: ", i + 1);
        scanf("%s", nome);
        insert_element(&head, nome);
    }

    // Lista todos os elementos da lista encadeada
    printf("\nLista de nomes em ordem alfabética:\n");
    listar_elementos(head);

    // Libera a memória da lista encadeada
    liberar_lista(&head);
    printf("\nLista liberada.\n");
}