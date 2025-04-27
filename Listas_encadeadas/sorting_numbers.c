/*
LISTAS DUPLAMENTE ENCADEADAS

Faça um programa que receba 20 números inteiros e armazene os pares em uma lista simplesmente encadeada não ordenada e os ímpares em uma segunda lista simplesmente encadeada e não ordenada. 

Posteriormente, o programa deverá montar uma terceira lista, duplamente encadeada e ordenada de forma crescente, com os números das duas listas anteriores. 

Para finalizar, o programa deve mostrar todos os números da terceira lista na ordem crescente e decrescente
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    uint16_t data;
    struct Node *next;
    struct Node *previous;
}

void receive_ numbers(uint16)

int main(){
    //Array que armazena os números
    uint16_t numbers[20];
    Node *pairs = NULL, *odds = NULL, *sorted = NULL;

    return 0;
}
