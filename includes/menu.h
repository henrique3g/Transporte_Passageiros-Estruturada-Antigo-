#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "linha.h"
#include "onibus.h"
#include "relatorio.h"

void menu();

void menuRel();

void opcao(int op);

void cabecalho(int i);

void printCabecalho(char *s);

#endif