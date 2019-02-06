#ifndef RELATORIO_H
#define RELATORIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "onibus.h"
#include "func.h"
FILE *flog;

void relArrecTela();
void relArrecArq();
void relOcupTela();
void relOcupArq();
void logErro(int i, char *s);

#endif