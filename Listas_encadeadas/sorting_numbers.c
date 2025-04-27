/*
LISTAS DUPLAMENTE ENCADEADAS

Faça um programa que receba 20 números inteiros e armazene os pares em uma lista simplesmente encadeada não ordenada e os ímpares em uma segunda lista simplesmente encadeada e não ordenada. 

Posteriormente, o programa deverá montar uma terceira lista, duplamente encadeada e ordenada de forma crescente, com os números das duas listas anteriores. 

Para finalizar, o programa deve mostrar todos os números da terceira lista na ordem crescente e decrescente
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

typedef struct Node_st
{
    int16_t data; // Alterado de uint16_t para int16_t para suportar números negativos
    struct Node_st *next;
    struct Node_st *previous;
} Node_st;

/**
 * @brief Cria um nodo na lista encadeada
 * @return Retorna um novo nodo com next == NULL; previous == NULL
 */
Node_st *create_node() 
{
    Node_st *new_node = (Node_st*)malloc(sizeof(Node_st));
    if(new_node == NULL) {
        printf("Error on trying to alocate memory!");
        exit(1);
    }

    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}

/**
 * @brief Adiciona um novo nó ao final de uma lista encadeada
 * @param head Ponteiro para o ponteiro do primeiro nó da lista
 * @param data Valor a ser armazenado ao novo nó
 */
void append_node(Node_st **head, int16_t data)
{
    Node_st *new_node = create_node();
    new_node->data = data;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node_st *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    new_node->previous = current;
}

/**
 * @brief Função para receber os números e passar para o array 
 * @param numbers Array para adicionar os números
 * @param size Tamanho do array
 */
void receive_numbers(int16_t *numbers, uint32_t size)
{
    for(uint8_t i = 0; i < size; i++)
    {
        float n;
        try_again:
            printf("Insert the %d integer nubmer:\n", (i+1));
            scanf("%f", &n);
            // Gambiarra para detectar decimal e não inteiro 
            if(floor(n) != n)
            {
                printf("Floating number detected!\n");
                goto try_again;
            } 
            numbers[i] = n;
    }
    return; 
}

//==========SORT FUNCTION==============

/**
 * @brief Obtém o último nó da lista
 * @param head Ponteiro para o primeiro nó da lista
 * @return Ponteiro para o último nó da lista
 */
Node_st *get_last_node(Node_st *head) 
{
    Node_st *current = head; 
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    return current;
}

/**
 * @brief Troca os dados de dois nós
 * @param node1 Primeiro nó
 * @param node2 Segundo nó
 */
void swap_nodes_data(Node_st *node1, Node_st *node2) 
{
    int16_t temp = node1->data; // Alterado para int16_t
    node1->data = node2->data;
    node2->data = temp;
}

/**
 * @brief Particiona a lista com base no pivô
 * @param low Primeiro nó da sublista
 * @param high Último nó da sublista
 * @return Ponteiro para o nó do pivô após a partição
 */
Node_st *partition(Node_st *low, Node_st *high) 
{
    int16_t pivot_value = high->data; // Toma o data do último elemento
    Node_st *init = low->previous;    // Aponta para o menor elemento, no caso, head

    // Organizando valores à esquerda do pivot
    for (Node_st *i = low; i != high; i = i->next) 
    {
        if (i->data <= pivot_value) 
        {
            init = (init == NULL) ? low : init->next; // Incrementa init
            swap_nodes_data(init, i); // Troca os elementos de init e i
        }
    }

    // Posicionando o pivot no lugar correto (meio)
    init = (init == NULL) ? low : init->next; // Incrementa o init para o pivot
    swap_nodes_data(init, high); // Troca os valores de init e high
    return init; // Retorna o pivô
}

/**
 * @brief Ordena a lista usando Quick Sort
 * @param low Primeiro nó da sublista
 * @param high Último nó da sublista
 */
void quick_sort(Node_st *low, Node_st *high) 
{
    if(low != NULL && high != NULL && low != high && low != high->next)
    {
        Node_st *pivot = partition(low, high);
        //Parte esquerda do pivot
        quick_sort(low, pivot->previous);
        //Parte direita do pivot
        quick_sort(pivot->next, high);
    }
}

/**
 * @brief Função para chamar o Quick Sort em uma lista encadeada
 * @param head Ponteiro para o primeiro nó da lista
 */
void call_sort_linked_list(Node_st *head) {
    Node_st *last = get_last_node(head);
    quick_sort(head, last); 
}

//=====================================

/**
 * @brief Checa se o número é par ou ímpar e o adiciona à lista encadeada
 * @param pair_list Ponteiro para a lista de números pares
 * @param odd_list Ponteiro para a lista de números ímpares
 * @param numbers Array de números
 * @param size Tamanho do array
 */
void check_pair_odds(Node_st **pair_list, Node_st **odd_list, int16_t *numbers, uint32_t size)
{
    //Debbug printf("Entrou");
    for (uint8_t i = 0; i < size; i++) 
    {
        if ((numbers[i] % 2) != 0) {
            append_node(odd_list, numbers[i]);
        } else {
            append_node(pair_list, numbers[i]);
        }
    }
}

/**
 * @brief Combina duas listas em uma lista duplamente encadeada ordenada
 * @param sorted Ponteiro para a lista ordenada
 * @param pair_list Lista de números pares
 * @param odd_list Lista de números ímpares
 */
void combine_and_sort(Node_st **sorted, Node_st *pair_list, Node_st *odd_list)
{
    if (pair_list == NULL && odd_list == NULL) {
        printf("Both pair and odd lists are empty. Nothing to combine.\n");
        return;
    }

    Node_st *current = pair_list;
    while (current != NULL) {
        append_node(sorted, current->data);
        current = current->next;
    }

    current = odd_list;
    while (current != NULL) {
        append_node(sorted, current->data);
        current = current->next;
    }

    if (*sorted != NULL) {
        call_sort_linked_list(*sorted);
    }
}

/**
 * @brief Exibe os números da lista em ordem crescente
 * @param head Ponteiro para o primeiro nó da lista
 */
void display_list_ascending(Node_st *head)
{
    //Debbug printf("Entrou 2");
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node_st *current = head;
    printf("Ascending order: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * @brief Exibe os números da lista em ordem decrescente
 * @param head Ponteiro para o primeiro nó da lista
 */
void display_list_descending(Node_st *head)
{
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node_st *current = get_last_node(head);
    printf("Descending order: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->previous;
    }
    printf("\n");
}

/**
 * @brief Libera a memória alocada para a lista
 * @param head Ponteiro para o primeiro nó da lista
 */
void free_list(Node_st *head)
{
    Node_st *current = head;
    while (current != NULL) {
        Node_st *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    // Array que armazena os números
    int16_t numbers[20];
    uint32_t size = sizeof(numbers) / sizeof(numbers[0]);
    receive_numbers(numbers, size);

    Node_st *pairs = NULL, *odds = NULL, *sorted = NULL;

    // Separar números pares e ímpares
    check_pair_odds(&pairs, &odds, numbers, size);

    // Verificar se as listas de pares e ímpares foram preenchidas
    if (pairs == NULL && odds == NULL) {
        printf("Both pair and odd lists are empty. No numbers to process.\n");
        return 0;
    }

    // Combinar e ordenar as listas
    combine_and_sort(&sorted, pairs, odds);

    // Exibir a lista ordenada
    if (sorted != NULL) {
        printf("\nDisplaying sorted list in ascending order:\n");
        display_list_ascending(sorted);

        printf("\nDisplaying sorted list in descending order:\n");
        display_list_descending(sorted);
    } else {
        printf("Sorted list is empty.\n");
    }

    // Liberar memória
    free_list(pairs);
    free_list(odds);
    free_list(sorted);

    return 0;
}
