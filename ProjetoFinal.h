#include "Projeto.h"

typedef struct coordenadas
{
    int x, y;
    int valor;
} coordenadas;

typedef struct Lista
{
    int nome;
    int custo;
    int x, y;
    struct Lista *next;
} Lista;

typedef struct ListaP // Header da lista
{
    int N;        // Número de ligações de uma sala
    Lista *nextp; // Header da lista
} ListaP;

/**
|   Entradas: Coordenadas do ficheiro.
|
|   Saídas: Tabuleiro preenchido.
|
|   Descrição: Preenche o tabuleiro.
|
 */
void matrixindexation(int **tabuleiro, FILE *pficheiro, int x, int y, FILE *pout);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Verifica se estão na mesma sala (A6).
|
 */
short mesma_sala(int cordx, int cordy, coordenadas cordC, int **tabuleiro, int x, int y, int *id);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Lê as linhas do ficheiro e trata de calcular o caminho mais rápido.
|
 */
void ficheiro(FILE *pficheiro, FILE *pout);

/**
|   Entradas: 2 pontos adjacentes.
|
|   Saídas: Pontos na mesma sala.
|
|   Descrição: Conectividade.
|
 */
void compressed_weighted_quick_union(int *id, int p, int q);

/**
|   Entradas: Tabuleiro
|
|   Saídas: As paredes mais baratas que separam as salas do tabuleiro e o respetivo grafo.
|
|   Descrição:
|
 */
int ve_paredes(int **tabuleiro, int x, int y, int *paredes, ListaP *lista);

/**
|   Entradas: As paredes mais baratas e as salas
|
|   Saídas: Grafo preenchido
|
|   Descrição:
|
 */
int preenche_grafo(int a, int b, int x, int y, int custo, ListaP *lista_de_adjacencia);

/**
|   Entradas: 2 salas
|
|   Saídas: O custo da ligação
|
|   Descrição:
|
 */
coordenadas parede(int a, int b, ListaP *lista);

/**
|   Entradas: Lista de adj.
|
|   Saídas:
|
|   Descrição: Free
|
 */
void liberta_lista(int V, ListaP *lista);

/**
|   Entradas: Lista de adj.
|
|   Saídas: Caminho de menos custo
|
|   Descrição: Algoritmo de Dijkstra.
|
 */
int Calculo_Dijkstra(int V, int *tabela_ordem, int *tabela_custo, ListaP *lista_de_adjacencia, int Sala_Chegada);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Compara o custo
|
 */
int Ver_Prioridade(int i, int j, int *tabela_custo);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Aloca o acervo
|
 */
int *FilaInit(int V);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição:  É se alocado a fila
|
 */
void Inserir_Fila(int *Acervo, int Posicao, int *Livres, int V);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: São inseridos vértices na fila
|
 */
void FixDown(int *Acervo, int Posicao, int Livres, int *tabela_custo);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: É se reordenado quando um certo vértice perde prioridade
|
 */
void FixUp(int *Acervo, int Posicao, int *tabela_custo);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: É se reordenado quando um certo vértice ganha prioridade
|
 */
int ApagarMaiorElemento(int *Acervo, int Livres, int *tabela_custo);

/**
|   Entradas:
|
|   Saídas:
|
|   Descrição: Reordena
|
 */
int Reordenar(int *Acervo, int Livres, int *tabela_custo);

/**
|   Entradas: 2 elementos
|
|   Saídas:
|
|   Descrição: Troca dos elementos
|
 */
void Troca(int *A, int *B);
