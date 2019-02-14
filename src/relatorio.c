#include "relatorio.h"

void relArrecTela(){
	float valor = 0, total = 0;
	int f = 0;
	Onibus o;
	Linha lin;
	FILE *fo = fopen(bdoni, "rb");
	FILE *flin = fopen(bdlin, "rb");
	Data d = getData();
	cls();
	printf("/////////////////////////////////////////////////\n");
	printf("//                                             //\n");
	printf("//        Relatório Arrecadação Mensal         //\n");
	printf("//                                             //\n");
	printf("//                 Emissão: %02d/%02d/%04d         //\n", d.dia, d.mes, d.ano);
	printf("/////////////////////////////////////////////////\n");
	printf("+-----------------------------------------------+\n");
	printf("|%-29s|%7s|%s|\n","Cidade", "Horário", "Total/Mês");
	printf("+-----------------------------+-------+---------+\n");
	while(fread(&lin, sizeof(lin), 1, flin)){
		while(fread(&o, sizeof(o), 1, fo)){
			if(o.idLin == lin.id){
				if(o.data.mes == d.mes && o.data.ano == d.ano){
					valor += lin.vlr * getTotReserva(o);
					f = 1;
				}
			}
		}
		rewind(fo);
		if(f == 1){
			printf("|%-29s| %02d:%02d | %8.2f|\n", lin.cid, lin.hora.h, lin.hora.m, valor);
			f = 0;
		}
		total += valor;
		valor = 0;
	}
	printf("+-----------------------------------------------+\n");
	printf("|Total                                %10.2f|\n", total);
	printf("+-----------------------------------------------+\n");
	getchar();


	fclose(fo);
	fclose(flin);
}

void relArrecArq(){
	float valor = 0, total = 0;
	int f = 0;
	char arq[100];
	Onibus o;
	Linha lin;
	Data d = getData();
	sprintf(arq, "relatorios/relatorio de vendas do mes %d emitido %02d-%02d-%04d.txt", d.mes,d.dia , d.mes, d.ano);
	FILE *fo = fopen(bdoni, "rb");
	FILE *flin = fopen(bdlin, "rb");
	FILE *frel = fopen(arq, "w");
	fprintf(frel, "/////////////////////////////////////////////////\n");
	fprintf(frel, "//                                             //\n");
	fprintf(frel, "//        Relatório Arrecadação Mensal         //\n");
	fprintf(frel, "//                                             //\n");
	fprintf(frel, "//                 Emissão: %02d/%02d/%04d         //\n", d.dia, d.mes, d.ano);
	fprintf(frel, "/////////////////////////////////////////////////\n");
	fprintf(frel, "+-----------------------------+-------+---------+\n");
	fprintf(frel, "|%-29s|%7s|%s|\n","Cidade", "Horário", "Total/Mês");
	fprintf(frel, "+-----------------------------+-------+---------+\n");
	while(fread(&lin, sizeof(lin), 1, flin)){
		while(fread(&o, sizeof(o), 1, fo)){
			if(o.idLin == lin.id){
				if(o.data.mes == d.mes && o.data.ano == d.ano){
					valor += lin.vlr * getTotReserva(o);
					f = 1;
				}
			}
		}
		rewind(fo);
		if(f == 1){
			fprintf(frel, "|%-29s| %02d:%02d | %8.2f|\n", lin.cid, lin.hora.h, lin.hora.m, valor);
			f = 0;
		}
		total += valor;
		valor = 0;
	}
	fprintf(frel,"+-----------------------------------------------+\n");
	fprintf(frel,"|Total                                %10.2f|\n", total);
	fprintf(frel,"+-----------------------------------------------+\n");


	fclose(fo);
	fclose(frel);
	fclose(flin);
	sprintf(arq, "\"relatorios\\relatorio de vendas do mes %d emitido %02d-%02d-%04d.txt\"", d.mes,d.dia, d.mes, d.ano);
	printf("Feche o arquivo aberto para continuar!\n");
	system(arq);

}

void relOcupTela(){
	int tot[7];
	int soma=0;
	for(int i = 0; i < 7; i++) tot[i] = 0;
	int f = 0;
	char str[60];
	Onibus o;
	Linha lin;
	FILE *fo = fopen(bdoni, "rb");
	FILE *flin = fopen(bdlin, "rb");
	Data d = getData();
	cls();
	printf("/////////////////////////////////////////////////////\n");
	printf("//                                                 //\n");
	printf("//     Relatório de ocupação por dia da semana     //\n");
	printf("//                                                 //\n");
	printf("//                          Emissão: %02d/%02d/%04d    //\n", d.dia, d.mes, d.ano);
	printf("/////////////////////////////////////////////////////\n");
	printf("+---------------------------------------------------+\n");
	while(fread(&lin, sizeof(lin), 1, flin)){
		while(fread(&o, sizeof(o), 1, fo)){
			if(o.idLin == lin.id){
				if(o.data.mes == d.mes && o.data.ano == d.ano){
					tot[getDiaSemanaE(o.data)-1] += getTotReserva(o);
					soma += getTotReserva(o);
					f = 1;
				}
			}
		}
		rewind(fo);
		if(f == 1){
			sprintf(str, "|%s, %02d:%02d , Total no mês = %02d", lin.cid, lin.hora.h, lin.hora.m, soma);
			printf("%-53s|\n",str);
			printf("|Dom\tSeg\tTer\tQua\tQui\tSex\tSab |\n|");
			for(int i = 0; i < 7; i++)
				printf("%d/80%c",tot[i], i == 6?'|':'\t');
			printf("\n+---------------------------------------------------+\n");
			for(int i = 0; i < 7; i++) tot[i] = 0;
			f = 0;
			soma = 0;
		}
	}
	fclose(fo);
	fclose(flin);
	getchar();
}

void relOcupArq(){
	int tot[7];
	int soma=0;
	for(int i = 0; i < 7; i++) tot[i] = 0;
	int f = 0;
	char str[60];
	Onibus o;
	Linha lin;
	char arq[100];
	Data d = getData();
	sprintf(arq, "relatorios/relatorio de ocupacao do mes %d emitido %02d-%02d-%04d.txt", d.mes,d.dia, d.mes, d.ano);
	FILE *fo = fopen(bdoni, "rb");
	FILE *flin = fopen(bdlin, "rb");
	FILE *frel = fopen(arq, "w");
	fprintf(frel, "/////////////////////////////////////////////////////\n");
	fprintf(frel, "//                                                 //\n");
	fprintf(frel, "//     Relatório de ocupação por dia da semana     //\n");
	fprintf(frel, "//                                                 //\n");
	fprintf(frel, "//                         Emissão: %02d/%02d/%04d     //\n", d.dia, d.mes, d.ano);
	fprintf(frel, "/////////////////////////////////////////////////////\n");
	fprintf(frel, "+---------------------------------------------------+\n");
	while(fread(&lin, sizeof(lin), 1, flin)){
		while(fread(&o, sizeof(o), 1, fo)){
			if(o.idLin == lin.id){
				if(o.data.mes == d.mes && o.data.ano == d.ano){
					tot[getDiaSemanaE(o.data)-1] += getTotReserva(o);
					soma += getTotReserva(o);
					f = 1;
				}
			}
		}
		rewind(fo);
		if(f == 1){
			sprintf(str, "|%s, %02d:%02d , Total no mês = %02d", lin.cid, lin.hora.h, lin.hora.m, soma);
			fprintf(frel, "%-53s|\n",str);
			fprintf(frel, "|Dom%sSeg%sTer%sQua%sQui%sSex%sSab |\n|",es,es,es,es,es,es);
			for(int i = 0; i < 7; i++)
				fprintf(frel, "%d/80%c",tot[i], i == 6?'|':'\t');
			fprintf(frel, "\n+---------------------------------------------------+\n");
			for(int i = 0; i < 7; i++) tot[i] = 0;
			f = 0;
			soma = 0;
		}
	}

	fclose(fo);
	fclose(frel);
	fclose(flin);
	sprintf(arq, "\"relatorios\\relatorio de ocupacao do mes %d emitido %02d-%02d-%04d.txt\"", d.mes, d.dia, d.mes, d.ano);
	printf("Feche o arquivo aberto para continuar!\n");
	system(arq);
}

void logErro(int i, char *s){
	
	char erro[][30] = {{"Assento ocupado"},
					   {"Onibus já partiu"},
					   {"Linha não existe!"},
					   {"Horario invalido!"},
					   {"Data invalida!"},
					   {"Assento invalido!"},
					   {"Reserva realizada!"}};

	fprintf(flog, "em \"%s\": %s\n", s, erro[i]);
	//printf("em \"%s\": %s\n", s, erro[i]);
}