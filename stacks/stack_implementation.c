/*
    Here we gonna implement stack data structure. The ideal way would be do it using a header to store the fucntions, but for pratice we gonna do it all into a C file
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


// Dynamic Satakc struct
typedef struct Node {
    int data;   
    struct Node* next;
} Node;

//Pointo to the top of the stack
Node *top = NULL;

//=============BASIC OPERATIONS============================

//Empty
/**
 *  @brief Check if the stack is empty
 */
int isEmpty()
{
    return top == NULL;
}

//Push
/**
 *  @brief Push a new element onto the stack
 *  @param data The data to be pushed onto the stack
 */
void push(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = top;
    top = newNode;
    printf("Pushed %d onto the stack\n", data);
}

// Pop
/**
 *  @brief Pop an element from the stack
 *  @return The data of the popped element
 */
void pop()
{
    if (isEmpty()) {
        printf("Stack underflow\n");
        return;
    }
    Node* temp = top;
    top = top->next;
    free(temp);
    printf("Popped element from the stack\n");
}

// Peak
/**
 *  @brief Peek at the top element of the stack
 *  @return The data of the top element
 */
int peek()
{
    if (isEmpty()) {
        printf("Stack is empty\n");
        return -1; // or some other error value
    }
    return top->data;
}

// Print
/**
 *  @brief Print the elements of the stack
 */
void printStack()
{
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    Node* current = top;
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Free memory
/**
 *  @brief Free the memory allocated for the stack
 */
void freeStack()
{
    while (!isEmpty()) {
        pop();
    }
}

//=========================================================
int main()
{
    int choice, data;

    do {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Print Stack\n");
        printf("5. Free Stack\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(data);
                break;
            case 2:
                pop();
                break;
            case 3:
                data = peek();
                if (data != -1) {
                    printf("Top element is: %d\n", data);
                }
                break;
            case 4:
                printStack();
                break;
            case 5:
                freeStack();
                break;
            case 6:
                freeStack();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 6);

    return 0;
}


