#include "onibus.h"

void consultarAssentos(){
	Linha lin;
	Onibus on;
	int ass;
	if(pesquisarLinha(&lin) != -1){
		on.idLin = lin.id; 
		cls();
		printf("//////////////////////////////\n");
		printf("//    Consultar Assentos    //\n");
		printf("//////////////////////////////\n");
		mostrarLinhaS(lin);
		printf("Data: ");
		lerData(&on.data);
		iniciarAssetos(&on);
		fflush(stdin);
		if(mostrarAssentos(on)){
			printf("assento para reservar (0 para cancelar): ");
			scanf("%2d", &ass);
			if(ass >= 1 && ass <= 20){
				if(verificaAssento(on, ass)){
					reservarAssento(on,ass);
				}else{
					printf("Assento ocupado!\n");
				}
			}else if(ass != 0){
				printf("Assento Invalido!");
			}
		}else{
			printf("Todos os assentos estão ocupados!\n");

		}
	}else {
		printf("Linha não encontrada!\n");
	}
	fflush(stdin);
	getchar();
}

int mostrarAssentos(Onibus o){
	int count = 1;
	int dis = 0;
	for(int i = 0; i < 20; i++){
		if(o.ass[i] != -1){
			printf("%02d", o.ass[i]);
			dis = 1;
		}else{
			printf(" X");
		}
		printf("%c",count == 2?'\t':count == 4?'\n':' ');
		//printf("%s",count == 2?"\t\t":count == 4?"\n":"\t");
		
		if(count == 4)	count = 0;
		count++;
	}
	return dis;
}

void iniciarAssetos(Onibus *o){
	int count = 0;
	int lin = o->idLin;
	int est = 0;
	Data d = o->data;
	fo = fopen(bdoni, "rb");
	if(fo == NULL)	printf("Banco não encontrado\n");
	fflush(stdin);
	while(fread(o, sizeof(Onibus), 1, fo)){
		if(lin == o->idLin){
			if(d.dia == o->data.dia && d.mes == o->data.mes && d.ano == o->data.ano){
				est = 1;
				break;
			}
		}
	}
	if(!est){
		o->id = getCodOni();
		o->data = d;
		o->idLin = lin;
		for(int i = 0; i < 20; i++){
			if(count == 2){
				o->ass[i] = i+2;
				o->ass[i+1] = i+1;
				i++;
				count = 0;
				continue;
			}
			o->ass[i] = i+1;
			count++;
		}	
	}
	fclose(fo);
	
}

int verificaAssento(Onibus o, int a){
	for(int i = 0; i < 20; i++){
		if(o.ass[i] == a)
			return 1;
	}
	return 0;
}

void reservarAssento(Onibus o, int ass){
	int pos = (o.id - 1) * sizeof(Onibus);
	fo = fopen(bdoni, "r+b");
	
	fseek(fo, pos, SEEK_SET);
	if(verificaAssento(o, ass)){
		for(int i = 0; i < 20; i++){
			if(o.ass[i] == ass)
				o.ass[i] = -1;
		}
	}
	if(fwrite(&o, sizeof(o), 1, fo))
		printf("Reserva realizada com sucesso!");

	fclose(fo);
}

int getCodOni(){
    Onibus o;
    int id = 0;
    rewind(fo);

    while(fread(&o, sizeof(o), 1, fo)){ 
        id++;
    }
    return id+1;
}