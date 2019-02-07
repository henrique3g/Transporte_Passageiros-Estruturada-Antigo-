#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
typedef struct {
	int dia;
	int mes;
	int ano;
}Data;

typedef struct {
    int h;
    int m;
} Hora;

void cls();

void rmvLn(char *s);

void toUpperCase(char *s);

void toUpper(char *c);

void toLower(char *c);

int isNum(char *s);

int isCharNum(char c);

int isChar(char c);

void lerData(Data *d);

int isPar(int n);

void clearBuf();

Data getData();

Hora getHora();

int getDiaSemana();

int getDiaSemanaE(Data d);

int validaData(Data d);

int validaHora(Hora h);

int formatMes(char *s);

int diffDate(Data i, Data f);

#endif
