#ifndef ONIBUS_H
#define ONIBUS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"
#include "func.h"
#include "relatorio.h"

#define bdoni "bd/onibus.bin"
typedef struct {
	int id;
	int idLin;
	Data data;
	int ass[20];
}Onibus;


void consultarAssentos();
int mostrarAssentos(Onibus o);
int verificaAssento(Onibus o, int a);
void iniciarAssentos(Onibus *o);
int reservarAssento(Onibus o, int ass);
int getCodOni();
int getTotReserva(Onibus o);
void lerReserva();
int pesquisaDataOnibus(Onibus *o);
#endif