#ifndef ONIBUS_H
#define ONIBUS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"
#include "func.h"

#define bdoni "bd/onibus.bin"
typedef struct {
	int id;
	int idLin;
	Data data;
	int ass[20];
}Onibus;

FILE *fo;

void consultarAssentos();
int mostrarAssentos(Onibus o);
void iniciarAssetos(Onibus *o);
int verificaAssento(Onibus o, int a);
void reservarAssento(Onibus o, int ass);
int getCodOni();
int getTotReserva(Onibus o);

#endif