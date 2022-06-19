#include "Projeto.h"


/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Dá open ao file
|
 */
FILE *AbreFicheiro(char *nome, char *mode);

/**
|   Entradas: String com o nome
|
|   Saídas: String com o nome alterado
|
|   Descrição: Faz com que o .in se torne .sol
|
 */
char *trata_nome(int argc, char **argv, char *FileName);

/**
|   Entradas: Argumentos.
|
|   Saídas:
|
|   Descrição: Trata dos argumentos.
|
 */
char *argumentos(int argc, char *argv[]);


 /**
|   Entradas: Pointers.
|
|   Saídas:
|
|   Descrição: Feixa.
|
 */
void Close(FILE *pout, FILE *pin);
 
 
/**
|   Entradas: Pointers.
|
|   Saídas:
|
|   Descrição: Liberta.
|
 */ 
void libertar(int **tabuleiro, int y, int *id);

/**
|   Entradas: Pointers.
|
|   Saídas:
|
|   Descrição: Liberta.
|
 */
void liberta_final(int *tabela_custo, int *tabela_ordem);