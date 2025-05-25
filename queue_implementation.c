#include "queue_implementation.h"

Queue* init_queue()
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL)
    {
        print("Wasn't posible create a queue");
        return -1;
    } 

    queue->front = queue->rear = NULL;

    return queue;
}

int is_empty(Queue* q)
{
    if(q->front == NULL) 
    {
        printf("Queue is empty!");
        return 1;
    }
    return 0;
}

void enqueue(Queue* q, int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if(is_empty(q))
    {
        q->front = q->rear = newNode;
    } else 
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }

}

int dequeue(Queue *q)
{
    if(is_empty(q)) 
    {
        printf("There are no elements in the queue!");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = temp->next;

    if(q->front == NULL) q->rear = NULL;

    free(temp);
    return value;
}

int peek(Queue *q)
{
    if(is_empty(q))
    {
        printf("There are no elements in the queue!");
        return -1;
    }

    int value = q->front->data;
    
    return value;
}

void free_queue(Queue *q)
{
    while(!is_empty(q))
    {
        dequeue(q);
    }
    free(q);
}