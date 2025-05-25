#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

typedef struct Queue 
{
    struct Node* front;
    struct Node* rear;
} Queue;

//==================BASIC FUNCTIONS=============================

Queue* init_queue();
int is_empty(Queue *q);
void enqueue(Queue* q, int value);
int dequeue(Queue *q);
int peek(Queue *q);
void free_queue(Queue *q);

