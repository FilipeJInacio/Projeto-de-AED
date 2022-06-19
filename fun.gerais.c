#include "fun.gerais.h"
#include <string.h>

// Abre um ficheiro
FILE *AbreFicheiro(char *nome, char *mode)
{
  FILE *fp;
  fp = fopen(nome, mode);
  if (fp == NULL)
  {
    free(nome);
    exit(0);
  }
  return (fp);
}

// Transforma Input em Output
char *trata_nome(int argc, char **argv, char *FileName)
{
  char *p;

  if (argc == 2)
  {
    sscanf(argv[1], "%s", FileName);

    for (p = FileName + strlen(FileName) - 3; p != FileName; p--) // Procura o ponto
    {
      if (*p == '.')
      {
        (*p) = '\0';
        strcat(FileName, ".sol"); // Troca por sol
        break;
      }
    }
  }

  return FileName;
}

// Função de tratamento de argumentos
char *argumentos(int argc, char *argv[])
{
  char *p;
  char *algo;

  if (argc != 2) // Verificação Final
  {
    exit(0);
  }

  if ((algo = (char *)calloc(strlen(argv[1]) + 2, sizeof(char))) == NULL)
  {
    exit(0);
  }

  sscanf(argv[1], "%s", algo);

  for (p = algo + strlen(algo); p != algo; p--)
  {
    if (strcmp(p, ".in")) // Verifica o .in
    {
      return algo;
    }
  }

  exit(0);
  return p;
}

// Feixa os ficheiros
void Close(FILE *pout, FILE *pin)
{
    fclose(pout);
    fclose(pin);
}

// Liberta o Tabuleiro e o ID
void libertar(int **tabuleiro, int y, int *id)
{

  int i;

  if (tabuleiro != NULL)
  {
    for (i = 0; i < (y); i++)
    {
      free(tabuleiro[i]);
    }
    free(tabuleiro);
  }

  if (id != NULL)
  {
    free(id);
  }
}

// Liberta as tabelas de Dijkstra
void liberta_final(int *tabela_custo, int *tabela_ordem)
{
  if (tabela_custo != NULL)
  {
    free(tabela_custo);
  }
  if (tabela_ordem != NULL)
  {
    free(tabela_ordem);
  }
  
  return;
}