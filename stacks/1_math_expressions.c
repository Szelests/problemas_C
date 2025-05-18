/*
Escrever um programa em C para avaliar o resultado de expressões aritméticas posfixa utilizando as funções para manipulação de uma Pilha, com alocação dinâmica de memória. O usuário deverá entrar com uma expressão (string) formada por números inteiros e operadores aritméticos (+, -, *, /) separados por espaços em branco. A saída deve ser o resultado da expressão.

---> Solução: usar o algorítmo de Shunting Yard, criado pelo Edsger Dijkstra (passa de infix para post-fixed)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _POSIX_C_SOURCE 200809L  // Para strdup() em sistemas POSIX

//=====ESTRUTURA DE DADOS======

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

typedef struct Node_int {
    int value_int;
    struct Node_int* next;
} Node_int;

// Pilhas e filas globais
Node* op_stack = NULL; // Pilha de operadores
Queue post_queue = {NULL, NULL}; // Fila para pós-fixa
Node_int* int_stack = NULL; // Pilha de inteiros

//===== MÉTODOS =====

// --- QUEUE ---
void enqueue(Queue *q, const char *val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = strdup(val);
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

char* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    Node* temp = q->front;
    char* value = temp->value;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return value;
}

// --- STACK ---
void push(Node** top, const char* var) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = strdup(var);
    newNode->next = *top;
    *top = newNode;
}

char* pop(Node** top) {
    if(*top == NULL) return NULL;
    Node *temp = *top;
    char *val = temp->value;
    *top = temp->next;
    free(temp);
    return val;
}

char* peek(Node* top) {
    return top ? top->value : NULL;
}

int isStackEmpty(Node* top) {
    return top == NULL;
}

// --- PILHA DE INTEIROS ---
void push_int(Node_int** top, int val) {
    Node_int* newNode = (Node_int*)malloc(sizeof(Node_int));
    newNode->value_int = val;
    newNode->next = *top;
    *top = newNode;
}

int pop_int(Node_int** top) {
    if(*top == NULL) return 0;
    Node_int *temp = *top;
    int val = temp->value_int;
    *top = temp->next;
    free(temp);
    return val;
}

// ===== FUNÇÕES AUXILIARES ======

int precedence(const char* op) {
    if(strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 2;
    if(strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    return 0;
}

int isOperator(const char* str) {
    return (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 ||
            strcmp(str, "*") == 0 || strcmp(str, "/") == 0);
}

// --- Conversion Infix to Post-fixed ---
void infixToPostfix(char *exp) {
    char* token = strtok(exp, " ");
    while (token != NULL) {
        if(isdigit(token[0])) {
            enqueue(&post_queue, token);
        } else if (strcmp(token, "(") == 0) {
            push(&op_stack, token);
        } else if (strcmp(token, ")") == 0) {
            while(!isStackEmpty(op_stack) && strcmp(peek(op_stack), "(") != 0) {
                enqueue(&post_queue, pop(&op_stack));
            }
            if (!isStackEmpty(op_stack) && strcmp(peek(op_stack), "(") == 0) {
                free(pop(&op_stack)); // Remove '('
            }
        } else if (isOperator(token)) {
            while(!isStackEmpty(op_stack) && isOperator(peek(op_stack)) &&
                  precedence(peek(op_stack)) >= precedence(token)) {
                enqueue(&post_queue, pop(&op_stack));
            }
            push(&op_stack, token);
        } else {
            printf("Erro: Token inválido '%s'\n", token);
            exit(1);
        }
        token = strtok(NULL, " ");
    }
    while (!isStackEmpty(op_stack)) {
        enqueue(&post_queue, pop(&op_stack));
    }
}

// --- Avaliação da Expressão Pós-fixa ---
int evaluatePostfix() {
    char* tok;
    while ((tok = dequeue(&post_queue)) != NULL) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            push_int(&int_stack, atoi(tok));
        } else if (isOperator(tok)) {
            int b = pop_int(&int_stack);
            int a = pop_int(&int_stack);
            if (strcmp(tok, "+") == 0) push_int(&int_stack, a + b);
            else if (strcmp(tok, "-") == 0) push_int(&int_stack, a - b);
            else if (strcmp(tok, "*") == 0) push_int(&int_stack, a * b);
            else if (strcmp(tok, "/") == 0) {
                if (b == 0) {
                    printf("Erro: Divisão por zero!\n");
                    exit(1);
                }
                push_int(&int_stack, a / b);
            }
        }
        free(tok); // Libera o token removido da fila
    }
    return pop_int(&int_stack);
}

// --- Liberação de Memória ---
void freeQueue(Queue* q) {
    while (q->front != NULL) {
        Node* temp = q->front;
        q->front = q->front->next;
        free(temp->value);
        free(temp);
    }
    q->rear = NULL;
}

void freeIntStack() {
    while (int_stack != NULL) {
        Node_int* temp = int_stack;
        int_stack = int_stack->next;
        free(temp);
    }
}

// --- Main ---
int main() {
    char expr[256];
    printf("Digite a expressão infixa (ex: 3 + 4 * 2): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; // Remove a quebra de linha

    infixToPostfix(expr);
    int result = evaluatePostfix();
    printf("Resultado: %d\n", result);

    // Libera memória
    freeQueue(&post_queue);
    while (!isStackEmpty(op_stack)) {
        free(pop(&op_stack));
    }
    freeIntStack();

    return 0;
}