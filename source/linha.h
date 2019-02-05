#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define bdlin "bd/linhas.bin"

FILE *flin;

typedef struct {
    int id;
    char cid[30];
    Hora hora;
    float vlr;
    int ativo;
} Linha;


void cadastrarLinha();
void alterarLinha();
void removerLinha();
void mostrarLinha();
void mostrarLinhaS();
void consultarHorarios();
int pesquisarLinha(Linha *lin);
int getCodLin();
void listarLinhas();
void alterarLin(Linha *lin, int *op);

#endif
