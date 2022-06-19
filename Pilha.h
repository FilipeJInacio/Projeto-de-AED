#include "Projeto.h"


typedef struct pilha
{
    int sala; 
} pilha;

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Coloca na pilha
|
 */
pilha *push(pilha *pointer, int nome);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Retira da pilha
|
 */
int pop(pilha **pointer);
