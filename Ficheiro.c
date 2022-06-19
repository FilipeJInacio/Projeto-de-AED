#include "Pilha.h"
#include "ProjetoFinal.h"
#include "fun.gerais.h"

// Lê as coordenadas do ficheiro e preenche a tabela
void matrixindexation(int **tabuleiro, FILE *pficheiro, int x, int y, FILE *pout)
{

    int repeticoes;
    int i;
    coordenadas cord;

    if (fscanf(pficheiro, " %d ", &repeticoes) != 1) // lê o número de coordenadas a ler
    {

        Close(pout, pficheiro);
        libertar(tabuleiro, y, NULL);
        exit(0);
    }

    for (i = 0; i < repeticoes; i++)
    {
        if (fscanf(pficheiro, " %i %i %i ", &cord.x, &cord.y, &cord.valor) != 3)
        {
            Close(pout, pficheiro);
            libertar(tabuleiro, y, NULL);
            exit(0);
        } // Lê do ficheiro
        if ((cord.x > 0 && cord.x <= x) && (cord.y > 0 && cord.y <= y))
        {
            tabuleiro[cord.y - 1][cord.x - 1] = cord.valor; // Preenche a struct coordenadas com os valores a colocar na tabuleiro
        }
    }
    return;
}

// Algoritmo A6
short mesma_sala(int cordx, int cordy, coordenadas cordC, int **tabuleiro, int x, int y, int *id)
{
    int i, j;

    for (i = 0; i < y * x; i++)
    {
        id[i] = i; // Inicializa
    }

    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x; j++)
        {
            if (tabuleiro[i][j] == 0)
            {

                if (j + 1 != x)
                { // Conectividade entre o ponto atual e o da frente
                    if (tabuleiro[i][j + 1] == 0)
                    {
                        compressed_weighted_quick_union(id, i * x + j, i * x + j + 1);
                    }
                }

                if ((i + 1 != y))
                { // Conectividade entre o ponto atual e o de baixo
                    if (tabuleiro[i + 1][j] == 0)
                    {
                        compressed_weighted_quick_union(id, i * x + j, (i + 1) * x + j);
                    }
                }

                if (id[(cordy - 1) * x + (cordx - 1)] == id[(cordC.y - 1) * x + (cordC.x - 1)])
                {
                    return 1; // No caso de o ponto de chegada e o ponto de partida terem o mesmo id
                }
            }
        }
    }

    return 0;
}

// Lê o ficheiro e monta a matriz
void ficheiro(FILE *pficheiro, FILE *pout)
{

    int **tabuleiro;                  // Array com as várias informações
    coordenadas coordenadas_C;        // Coordenadas das variantes
    int i, j = 0, e = 0;              // Para for's
    int *id;                          // Tabuleiro da Conectividade
    ListaP *lista_adjacencia = NULL;  // Pointer para a tabela de listas
    int V = 0;                        // nº de salas
    int *tabela_custo, *tabela_ordem; // Tabelas dos Dijkstra
    int x, y;                         // Tamanho do tabuleiro
    unsigned short n_paredes_p = 0;   // nº de paredes partidas
    pilha *stack;                     // Pilha

    if (fscanf(pficheiro, " %i %i ", &x, &y) != 2)
    {
        Close(pout, pficheiro);

        exit(0);
    } // Lê o x e o y máximos

    if (x < 0 || y < 0)
    {
        Close(pout, pficheiro);

        exit(0);
    } // Algumas verificações

    if (fscanf(pficheiro, " %i %i ", &coordenadas_C.x, &coordenadas_C.y) != 2)
    {
        Close(pout, pficheiro);
        exit(0);
    } // Consegue as coordenadas de chegada

    if (!((coordenadas_C.x > 0) && (coordenadas_C.x <= x)) || !((coordenadas_C.y > 0) && (coordenadas_C.y <= y)))
    {
        if (fscanf(pficheiro, " %i ", &j) != 1)
        {
            Close(pout, pficheiro);

            exit(0);
        } // lê o número de coordenadas a ler

        for (i = 0; i < j; i++) // Lê o resto do ficheiro
        {
            if (fscanf(pficheiro, " %i %i %i ", &coordenadas_C.x, &coordenadas_C.x, &coordenadas_C.x) != 3)
            {
                Close(pout, pficheiro);

                exit(0);
            }
        }
        fprintf(pout, "-1\n\n");
        return;
    }

    if ((tabuleiro = (int **)calloc(sizeof(int *), (y))) == NULL)
    {
        Close(pout, pficheiro);

        exit(0);
    } // Aloca tabuleiro

    for (i = 0; i < y; i++)
    {
        if ((tabuleiro[i] = (int *)calloc(sizeof(int), (x))) == NULL)
        {
            Close(pout, pficheiro);
            libertar(tabuleiro, 0, NULL);
            exit(0);
        } // Aloca tabuleiro
    }

    matrixindexation(tabuleiro, pficheiro, x, y, pout); // preenche tabuleiro

    if (tabuleiro[0][0] != 0 || tabuleiro[coordenadas_C.y - 1][coordenadas_C.x - 1] != 0) // É uma parede?
    {
        fprintf(pout, "-1\n\n");
        libertar(tabuleiro, y, NULL);
        return;
    }

    if ((id = (int *)malloc((x) * (y) * sizeof(int))) == NULL) // Aloca id
    {
        Close(pout, pficheiro);
        libertar(tabuleiro, y, NULL);
        exit(0);
    }

    if (tabuleiro[0][1] == -1 && tabuleiro[1][0] == -1) // Caso de o ínicio estar rodeado de paredes inquebraveis.
    {
        fprintf(pout, "-1\n\n");
        libertar(tabuleiro, y, NULL);
        return;
    }

    if (mesma_sala(1, 1, coordenadas_C, tabuleiro, x, y, id) == 1) // Faz as salas
    {
        fprintf(pout, "0\n\n");
        libertar(tabuleiro, y, id);
        return;
    }

    for (i = 0; i < (y); i++)
    {
        for (j = 0; j < (x); j++)
        {
            if (tabuleiro[i][j] == 0)
            {
                if (id[i * (x) + j] == i * (x) + j)
                {
                    V++;                     // Conta o número de salas
                    id[i * (x) + j] = V - 1; // Coloca o nome correto nas sala
                }
                else
                {
                    id[i * (x) + j] = id[id[i * (x) + j]]; // Copia o nome da raiz
                }
            }
        }
    }

    j = id[(coordenadas_C.y - 1) * (x) + coordenadas_C.x - 1]; // Sala de chegada

    if ((lista_adjacencia = (ListaP *)malloc(sizeof(ListaP) * V)) == NULL) // Aloca a head da matriz de ad
    {
        Close(pout, pficheiro);
        libertar(tabuleiro, y, id);
        exit(0);
    }
    for (i = 0; i < V; i++) // Inicialização do vetor
    {
        lista_adjacencia[i].nextp = NULL;
        lista_adjacencia[i].N = 0;
    }

    if (ve_paredes(tabuleiro, x, y, id, lista_adjacencia) == 1) // Verifica as paredes mais baratas
    {
        Close(pout, pficheiro);
        libertar(tabuleiro, y, id);
        liberta_lista(V, lista_adjacencia);
        exit(0);
    }

    libertar(tabuleiro, y, id); // Não é mais necessário os tabuleiros

    if ((tabela_ordem = (int *)malloc(sizeof(int) * V)) == NULL) // Tabela com a ordem da sala do anterior.
    {
        Close(pout, pficheiro);
        liberta_lista(V, lista_adjacencia);
        exit(0);
    }
    if ((tabela_custo = (int *)malloc(sizeof(int) * V)) == NULL) // Tabela com o custo de viagem a cada sala (partindo de 0 0).
    {
        Close(pout, pficheiro);
        liberta_lista(V, lista_adjacencia);
        liberta_final(tabela_ordem, NULL);
        exit(0);
    }
    if ((stack = (pilha *)malloc(sizeof(pilha) * (V + 1))) == NULL) // Pilha
    {
        Close(pout, pficheiro);
        liberta_lista(V, lista_adjacencia);
        liberta_final(tabela_ordem, tabela_custo);
        exit(0);
    }

    if (Calculo_Dijkstra(V, tabela_ordem, tabela_custo, lista_adjacencia, j) == 1) // Verifica se terminou
    {
        e = tabela_ordem[j];
        stack = push(stack, j);
        stack = push(stack, e);
        n_paredes_p = 1;
        while (tabela_ordem[e] != -1) // Guarda as salas na pilha para posterior interpretação
        {
            e = tabela_ordem[e];
            stack = push(stack, e);
            n_paredes_p++;
        }
        fprintf(pout, "%i\n", tabela_custo[j]);
    }
    else
    {
        fprintf(pout, "-1\n\n"); // Caso de não conseguir chegar
        liberta_lista(V, lista_adjacencia);
        liberta_final(tabela_ordem, tabela_custo);
        free(stack);
        return;
    }

    fprintf(pout, "%i\n", n_paredes_p); // Coloca o número de paredes

    i = pop(&stack);
    for (e = 0; e < n_paredes_p; e++)
    {
        j = pop(&stack);
        coordenadas_C = parede(i, j, lista_adjacencia); // Dá o custo e as coordenadas

        fprintf(pout, "%i %i %i\n", coordenadas_C.y + 1, coordenadas_C.x + 1, coordenadas_C.valor); // Coloca no ficheiro
        i = j;
    }
    fprintf(pout, "\n\n");
    free(stack);
    liberta_lista(V, lista_adjacencia);
    liberta_final(tabela_ordem, tabela_custo);

    return;
}