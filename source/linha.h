#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define bdlin "bd/linhas.bin"

FILE *flin;
typedef struct {
    int h;
    int m;
} Hora;


typedef struct {
    int cod;
    char cid[30];
    Hora hora;
    float vlr;
    int ativo;
} Linha;


void cadastrarLinha();
void alterarLinha();
void removerLinha();
void mostrarLinha();
void consultarHorarios();
fpos_t pesquisarLinha();
int getCodLin();

#endif
