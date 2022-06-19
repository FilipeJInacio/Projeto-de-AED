#include "ProjetoFinal.h"

// Troca 2 elementos
void Troca(int *A, int *B)
{
    int Aux;
    Aux = *A;
    *A = *B;
    *B = Aux;

    return;
}

// Novo elemento
void Inserir_Fila(int *Acervo, int Posicao, int *Livres, int V)
{
    if (V > *Livres + 1)
    {
        Acervo[*Livres] = Posicao;
        (*Livres)++;
    }
}

// Compara custos
int Ver_Prioridade(int i, int j, int *tabela_custo)
{
    if (tabela_custo[i] > tabela_custo[j])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Aloca o Acervo
int *FilaInit(int V)
{
    int *Acervo;
    Acervo = (int *)malloc(sizeof(int) * V);

    return Acervo;
}

void FixDown(int *Acervo, int Posicao, int Livres, int *tabela_custo)
{
    int descen;

    while (Livres - 1 > 2 * Posicao)
    {
        descen = (Posicao * 2) + 1;

        if ((Ver_Prioridade(Acervo[descen], Acervo[descen + 1], tabela_custo) && ((Livres - 1) > descen)) == 1) // Compara a prioridade entre o vértice atual e o diretamente abaixo
        {
            descen += 1;
        }
        if (Ver_Prioridade(Acervo[Posicao], Acervo[descen], tabela_custo) == 0) // Verifica-se o outro filho
        {
            break;
        }

        Troca(&Acervo[Posicao], &Acervo[descen]); // Se há uma incompatibilidade de prioridades, troca

        Posicao = descen; // Desce-se o Acervo
    }
    return;
}

void FixUp(int *Acervo, int Posicao, int *tabela_custo)
{

    while (((Posicao > 0) && (Ver_Prioridade(Acervo[(Posicao - 1) / 2], Acervo[Posicao], tabela_custo))) == 1) // Compara a prioridade entre o vértice atual e o diretamente acima
    {
        Troca(&Acervo[Posicao], &Acervo[(Posicao - 1) / 2]); // Se se verificar uma ordenação de prioridades incorreta, efetua-se a troca

        Posicao = (Posicao - 1) / 2; // É se seguido o Acervo acima
    }
    return;
}

int Reordenar(int *Acervo, int Livres, int *tabela_custo)
{
    Troca(&Acervo[0], &Acervo[Livres - 1]); // Troca o ultimo com o primeiro
    FixDown(Acervo, 0, Livres - 1, tabela_custo);
    return Acervo[Livres - 1];
}

int Calculo_Dijkstra(int V, int *tabela_ordem, int *tabela_custo, ListaP *lista_de_adjacencia, int Sala_Chegada)
{

    Lista *Aux;
    int i, Livres = 0, j;
    int *Acervo;

    Acervo = FilaInit(V); // Aloca o acervo

    for (i = 0; i < V; i++) // Inicializa
    {
        tabela_custo[i] = __INT_MAX__;
        tabela_ordem[i] = -1;
    }
    Acervo[0] = 0;
    tabela_custo[0] = 0; // Coloca o 0
    Livres = 1;

    while (Livres != 0) // Até serem tirados todos os elementos
    {
        i = Reordenar(Acervo, Livres, tabela_custo);
        Livres--; // Remove o último
        if (tabela_custo[i] != __INT_MAX__)
        {
            for (Aux = lista_de_adjacencia[i].nextp; Aux != NULL; Aux = Aux->next) // Percorre a lista
            {
                if (tabela_custo[Aux->nome] > (tabela_custo[i] + (Aux->custo))) // Verificação de um custo inferior
                {

                    tabela_custo[Aux->nome] = (tabela_custo[i] + (Aux->custo)); // Colocação do novo custo
                    for (j = 0; j < Livres; j++)                                //  Procura da posição do vértice pretendido no Acervo
                    {
                        if (Acervo[j] == Aux->nome)
                        {
                            FixUp(Acervo, j, tabela_custo); // Ajuste do Acervo
                            break;
                        }
                    }
                    if (tabela_ordem[Aux->nome] == -1) // Verificação de o vértice pretendido ainda não ter sido inserido no Acervo
                    {
                        Inserir_Fila(Acervo, Aux->nome, &Livres, V);
                        FixUp(Acervo, Livres - 1, tabela_custo); // Ajuste do Acervo
                    }
                    tabela_ordem[Aux->nome] = i; // Coloca o anterior
                }
            }
            if (Acervo[0] == Sala_Chegada) // Momento de terminar
            {
                free(Acervo);
                return 1;
            }
        }
    } // Terminar depois de não haver caminho
    free(Acervo);
    return 0;
}