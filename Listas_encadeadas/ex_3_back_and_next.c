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
#include <conio.h>

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
    getchar();

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
            printf("Sua lista esta vazia. Gostaria de adicionar um elemento? (Y/N): ");
            scanf(" %c", &y_n);
            getchar();

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
            getchar();

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

//==========USANDO CHAR PARA NAVEGAR==========//
/**
 * @brief Função que permite navegar pela lista:
 * '<' para trás
 * '>' para frente
 * 'q' para sair da função
 * @param element Nodo que pode estar em qualquer posição da lista
 */
void back_and_next_char(Node *element)
{
    if(element == NULL)
    {
        printf("A lista se encontra vazia!");
        return;
    }

    if(element->next == element)
    {
        printf("Sua lista te unico elemento: %s", element->name);
        return;
    }

    printf("Elemento atual: %s\n", element->name);
    uint8_t check = 1;
    do 
    {
        char command;
        printf("Pressione:\nVoltar:  '<'\nAvancar: '>'\nSair:    'q'\n");
        scanf(" %c", &command);
        getchar();

        if(command == '<') 
        {
            element = element->prev;
            printf("%s\n", element->name);
        } else if(command == '>') 
        {
            element = element->next;
            printf("%s\n", element->name);
        } else if(command == 'q' || command == 'Q')
        {
            printf("Voce esta nos deixando.");
            exit(1);
        } else 
        {
            printf("Comando inválido, tente novamente!");
        }

    } while(check);
}
//======================================================
//==========USANDO _getch() PARA NAVEGAR==========//
/**
 * @brief Função que permite navegar pela lista:
 * ← para trás
 * → para frente
 * q para sair da função
 * @param element Nodo que pode estar em qualquer posição da lista
 */
void back_and_next(Node *element) {
    if (element == NULL) {
        printf("A lista se encontra vazia!\n");
        return;
    }

    if (element->next == element) {
        printf("Sua lista tem um único elemento: %s\n", element->name);
        return;
    }

    printf("Elemento atual: %s\n", element->name);
    printf("Pressione:\nVoltar:  '<'\nAvancar: '>'\nSair:    'q'\n");
    uint8_t check = 1;

    do{
        uint16_t ch = _getch();

        if (ch == 0 || ch == 224) {
            uint16_t arrow = _getch(); // Captura o segundo código

            if (arrow == 75) { // ← esquerda
                element = element->prev;
                printf("<< %s\n", element->name);
            } else if (arrow == 77) { // → direita
                element = element->next;
                printf(">> %s\n", element->name);
            }

        } else if (ch == 'q' || ch == 'Q') {
            printf("Voce esta saindo...\n");
            break;
        }
    } while(check); 
}
//========================================================

/**
 * @brief Libera a memória alocada para a lista circular
 * @param head Ponteiro para a cabeça da lista
 */
void free_list(Node *head)
{
    if (head == NULL)
        return;

    Node *current = head;
    Node *next_node;

    do
    {
        next_node = current->next;
        free(current);
        current = next_node;
    } while (current != head);
}

int main(void)
{
    Node *list = NULL;

    insert_elements(&list);

    printf("\nLista final:\n");
    print_list(list);

    if (list != NULL)
    {
        printf("\nIniciando navegacao pela lista...\n");
        back_and_next(list);
    }

    return 0;
}