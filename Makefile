
# Nome do executável a ser gerado.
TARGET= roap

all: $(TARGET)
$(TARGET): Makefile
	gcc -Wall -std=c99 -O3 Projeto.h Pilha.h ProjetoFinal.h fun.gerais.h Projeto.c fun.gerais.c Ficheiro.c Grafo.c Algoritmo.c Pilha.c -o $@

