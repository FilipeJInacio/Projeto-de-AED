#include "Pilha.h"

// Push da pilha
// Ignora o primeiro quadrado de memoria
pilha *push(pilha *pointer, int nome)
{
    pointer++;
    pointer->sala = nome;
    return pointer; 
}

// Pop da pilha
int pop(pilha **pointer)
{
    pilha *dados = *pointer;
    (*pointer)--;
    return dados->sala;
}
