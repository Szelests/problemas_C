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

typedef struct {
    uint16_t data;
    struct Node *next;
    struct Node *previous;
} Node_st;

/**
 * @brief Função para receber os números e passar para o array 
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
}

int main(){
    //Array que armazena os números
    int16_t numbers[20];
    uint32_t size = sizeof(numbers) / sizeof(numbers[0]);
        
    Node_st *pairs = NULL, *odds = NULL, *sorted = NULL;

    return 0;
}
