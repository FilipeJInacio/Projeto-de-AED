/** /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
|   Programa: Projeto                                                                                                                           |
|                                                                                                                                               |
|   Descrição: Programa capaz de, ao analisar um ficheiro de entrada, é capaz de, determinar um caminho com o menor custo.                      |
|                                                                                                                                               |
|                                                                                                                                               |
|   Ficheiros:                                                                                                                                  |
|       (1)     Projeto.c - main.                                                                                                               |
|       (2)     fun.gerais.c - Funções gerais.                                                                                                  |                                                                                                     |
|       (3)     ficheiro.c - Funções de tratamento de tabuleiro e verificação da mesma sala.                                                    |
|       (4)     Pilha.c - Funções de pilha.                                                                                                     |
|       (5)     Grafo.c - Conectividade e criação do grafo                                                                                      |
|       (6)     Algoritmo.c - Dijkstra                                                                                                          |
|                                                                                                                                               |
|                                                                                                                                               |
|   Autoria:    Duarte Santos, 99927                                                                                                            |
|               Filipe Cravidão, 99932                                                                                                          |
|                                                                                                                                               |
|                                                                                                                                               |
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include "Projeto.h"
#include "fun.gerais.h"
#include "ProjetoFinal.h"


// Complexidades
//  Os valores máximos de x, y e valor da parede são Max(INT).

int main(int argc, char *argv[])
{
    char *FileName;  // Nome do ficheiro de Input e Output
    FILE *pficheiro; // Pointer para o ficheiro de Input
    FILE *pout;      // Pointer para o ficheiro de Output

    FileName = argumentos(argc, argv); // Trata dos argumentos e aloca FileName

    pficheiro = AbreFicheiro(FileName, "r"); // Abre ficheiro de Input

    trata_nome(argc, argv, FileName); // Cria o name de Output

    pout = AbreFicheiro(FileName, "w"); // Abre o ficheiro de Output

    free(FileName);

    while (!feof(pficheiro))
    { // Até o ficheiro acabar

        ficheiro(pficheiro, pout); // interpreta e escreve no ficheiro
    }

    fclose(pficheiro);
    fclose(pout);

    exit(0);
}
