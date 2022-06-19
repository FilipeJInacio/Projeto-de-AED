#include "ProjetoFinal.h"

// Conectividade
void compressed_weighted_quick_union(int *id, int p, int q)
{
    int i, j;

    // Dá o índice correto
    for (i = p; i != id[i]; i = id[i])
    {
    }
    for (j = q; j != id[j]; j = id[j])
    {
    }

    // Faz a união com o maior
    if (i < j)
    {
        id[j] = i;
    }
    else
    {
        id[i] = j;
    }

    return;
}

// Preenche a lista
int preenche_grafo(int a, int b, int x, int y, int custo, ListaP *lista_de_adjacencia)
{
    int c = 0;
    Lista *aux;

    if (lista_de_adjacencia[a].nextp == NULL) // A não tiver nada
    {
        if ((lista_de_adjacencia[a].nextp = (Lista *)malloc(sizeof(Lista))) == NULL)
        {
            return 1;
        }
        lista_de_adjacencia[a].nextp->custo = custo; // Inicializa
        lista_de_adjacencia[a].nextp->nome = b;
        lista_de_adjacencia[a].N++;
        lista_de_adjacencia[a].nextp->next = NULL;
        lista_de_adjacencia[a].nextp->x = x;
        lista_de_adjacencia[a].nextp->y = y;
        c = 1;
    }

    if (lista_de_adjacencia[b].nextp == NULL) // B não tiver nada
    {
        if ((lista_de_adjacencia[b].nextp = (Lista *)malloc(sizeof(Lista))) == NULL)
        {
            return 1;
        }
        lista_de_adjacencia[b].N++;
        lista_de_adjacencia[b].nextp->next = NULL;
        lista_de_adjacencia[b].nextp->custo = custo; // Inicializa
        lista_de_adjacencia[b].nextp->nome = a;
        lista_de_adjacencia[b].nextp->x = x;
        lista_de_adjacencia[b].nextp->y = y;
        if (c == 1)
        {
            c = 2; // A e B estão a ser inicializados pela primeira vez
        }
        else
        {
            c = 3; // Apenas B não existe
        }
    }

    if (c == 2)
    {
        return 0; // Já foram inicializados ambos
    }

    if (c == 1) // Inserir no B porque B já estava inicializado
     {
        if ((aux = (Lista *)malloc(sizeof(Lista))) == NULL)
        {
            return 1;
        }
        aux->next = lista_de_adjacencia[b].nextp; // Inicializa
        lista_de_adjacencia[b].nextp = aux;
        aux->custo = custo;
        aux->nome = a;
        lista_de_adjacencia[b].N++;
        aux->x = x;
        aux->y = y;
        return 0;
    }

    if (c == 3) // Inserir no A porque A já estava inicializado
    {
        if ((aux = (Lista *)malloc(sizeof(Lista))) == NULL)
        {
            return 1;
        }
        aux->next = lista_de_adjacencia[a].nextp; // Inicializa
        lista_de_adjacencia[a].nextp = aux;
        aux->custo = custo;
        aux->nome = b;
        lista_de_adjacencia[a].N++;
        aux->x = x;
        aux->y = y;
        return 0;
    }

    if (c == 0) // A e B já estavam inicializados mas exite ligação entre os dois?
    {

        for (aux = lista_de_adjacencia[a].nextp; aux != NULL; aux = aux->next) 
        {
            if (aux->nome == b) // Tem ligação
            {
                c = 4; 
                if (aux->custo > custo)  // Implica alteração
                {
                    aux->custo = custo;
                    aux->x = x;
                    aux->y = y;
                    c = 5;
                }
            }
        }

        if (c == 4)
        {
            return 0; // Tem ligação e custo não implica um alteração
        }
        if (c == 5)
        {
            for (aux = lista_de_adjacencia[b].nextp; aux != NULL; aux = aux->next)
            {
                if (aux->nome == a) // Altera no outro elemento
                {
                    aux->custo = custo;
                    aux->x = x;
                    aux->y = y;
                    return 0;
                }
            }
        }

        if (c == 0) // A ligação entre os dois não existe
        {
            if ((aux = (Lista *)malloc(sizeof(Lista))) == NULL)
            {
                return 1;
            }
            aux->next = lista_de_adjacencia[a].nextp; // Inicializa
            lista_de_adjacencia[a].nextp = aux;
            aux->custo = custo;
            aux->nome = b;
            aux->x = x;
            aux->y = y;
            lista_de_adjacencia[a].N++;
            if ((aux = (Lista *)malloc(sizeof(Lista))) == NULL)
            {
                return 1;
            }
            aux->next = lista_de_adjacencia[b].nextp; // Inicializa
            lista_de_adjacencia[b].nextp = aux;
            aux->custo = custo;
            aux->nome = a;
            lista_de_adjacencia[b].N++;
            aux->x = x;
            aux->y = y;
            return 0;
        }
    }

    return 0;
}

// Procura as paredes mais baratas entre salas e preenche a lista 
int ve_paredes(int **tabuleiro, int x, int y, int *paredes, ListaP *lista)
{
    int i, j;
    int w = x - 1, z = y - 1;

    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x; j++) // Percorre o tabuleiro
        {
            if (tabuleiro[i][j] > 0) // É uma parede
            {
                if (i != 0 && i != z) // Não está nos limites
                {
                    if (((tabuleiro[i + 1][j] == 0) && tabuleiro[i - 1][j] == 0) && (paredes[(i + 1) * x + j] != paredes[(i - 1) * x + j]))
                    { // Parede é quebravel e está entre duas salas diferentes.
                        if (preenche_grafo(paredes[(i + 1) * x + j], paredes[(i - 1) * x + j], i, j, tabuleiro[i][j], lista) == 1)
                        {
                            return 1;
                        }
                    }
                }
                if (j != 0 && j != w) // Não está nos limites
                {
                    if (tabuleiro[i][j + 1] == 0 && tabuleiro[i][j - 1] == 0 && paredes[i * x + j + 1] != paredes[i * x + j - 1])
                    { // Parede é quebravel e está entre duas salas diferentes.
                        if (preenche_grafo(paredes[i * x + j + 1], paredes[i * x + j - 1], i, j, tabuleiro[i][j], lista) == 1)
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

// Retorna as coordenadas e o custo da parede que divide duas salas
coordenadas parede(int a, int b, ListaP *lista)
{
    Lista *aux;
    coordenadas coord;

    if (lista[a].N > lista[b].N)
    {
        for (aux = lista[b].nextp; aux != NULL; aux = aux->next)
        {
            if (aux->nome == a)
            {
                coord.x = aux->x;
                coord.y = aux->y;
                coord.valor = aux->custo;
                return coord;
            }
        }
    }
    else
    {
        for (aux = lista[a].nextp; aux != NULL; aux = aux->next)
        {
            if (aux->nome == b)
            {
                coord.x = aux->x;
                coord.y = aux->y;
                coord.valor = aux->custo;
                return coord;
            }
        }
    }

    coord.x = -1;
    coord.y = -1;
    coord.valor = .1;
    return coord;
}

// Free à lista
void liberta_lista(int V, ListaP *lista)
{
	int i;
    Lista *aux;
    for (i = 0; i < V; i++)
    {
      while (lista[i].nextp != NULL)
      {
        aux = lista[i].nextp;
        lista[i].nextp = lista[i].nextp->next;
        free(aux);
      }
    }
    free(lista);

	return;
	
}