/*
Escreva uma função que permita inserir elementos na lista e uma função que recebe o endereço de um elemento qualquer da lista e permita que o usuário navegue para frente e para trás na lista, exibindo os nomes das posições. Utilize as seguintes teclas para navegação:

·       '<' para exibir o nome anterior;

·       '>' para exibir o nome seguinte; e

·       'q' para encerrar a navegação.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Node 
{
    char name[40];
    struct Node *prev;
    struct Node *next;
} Node;

/**
 * @brief Cria um novo Nodo
 * @return Novo nodo
 */
Node *create_node(void)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    new_node->name[0] = '\0';
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Função que mostra os nomes na tela
 * @param head Cabeça da lista (como é circular, não há um começo e fim definidos)
 */
void print_list(Node *head)
{
    if (head == NULL)
    {
        printf("A lista se encontra vazia.\n");
        return;
    }

    Node *current = head;
    uint8_t pos = 1;

    do
    {
        printf("%d: %s\n", pos, current->name);
        current = current->next;
        pos++;
    } while (current != head);
}

/**
 * @brief Insere um novo nodo em uma lista circular
 * @param head Ponteiro para o ponteiro da cabeça da lista
 */
void insert_node_circular_list(Node **head) 
{
    Node *new_node = create_node();
    printf("Digite o nome desejado: ");
    scanf("%39s", new_node->name);

    if (*head == NULL)
    {
        // Caso a lista esteja vazia
        *head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    }
    else
    {
        // Caso a lista já tenha elementos
        Node *last = (*head)->prev;
        last->next = new_node;
        new_node->prev = last;
        new_node->next = *head;
        (*head)->prev = new_node;
    }
}

/**
 * @brief Insere elementos na lista circular
 * @param head Ponteiro para o ponteiro da cabeça da lista
 */
void insert_elements(Node **head)
{
    uint8_t check = 1;
    char y_n;

    do
    {
        if (*head == NULL)
        {
            printf("Sua lista está vazia. Gostaria de adicionar um elemento? (Y/N): ");
            scanf(" %c", &y_n);

            if (y_n == 'Y' || y_n == 'y')
            {
                insert_node_circular_list(head);
            }
            else
            {
                check = 0;
            }
        }
        else
        {
            printf("Elementos presentes na sua lista:\n");
            print_list(*head);

            printf("\nGostaria de adicionar mais elementos? (Y/N): ");
            scanf(" %c", &y_n);

            if (y_n == 'Y' || y_n == 'y')
            {
                insert_node_circular_list(head);
            }
            else
            {
                check = 0;
            }
        }
    } while (check == 1);
}



int main(void)
{
    Node *list = NULL;

    insert_elements(&list);

    printf("\nLista final:\n");
    print_list(list);

    return 0;
}