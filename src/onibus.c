#include "onibus.h"

void consultarAssentos(){
	Linha lin;
	Onibus on;
	int ass,res;
	if(pesquisarLinha(&lin) != -1){
		on.idLin = lin.id; 
		cabecalho(6);
		mostrarLinhaS(lin);
		printf("Data: ");
		lerData(&on.data);
		if(validaData(on.data)){
			iniciarAssentos(&on);
			if(mostrarAssentos(on)){
				printf("assento para reservar (0 para cancelar): ");
				scanf("%2d", &ass);
				clearBuf();
				if(ass >= 1 && ass <= 20){
					res = reservarAssento(on, ass);
					if(res == 1){
						printf("Reserva realizada com sucesso!");
					}else if(res == -1){
						printf("Erro efetuar reserva!\n");
					}else if(res == 0){
						printf("Assento ocupado!\n");
					}
					getchar();
				}else if(ass != 0){
					printf("Assento Invalido!");
					getchar();
				}
			}else{
				printf("Todos os assentos estão ocupados!\n");
				getchar();
			}
		}else{
			printf("Erro! Data invalida!\n");
			getchar();
		}
	}else {
		printf("Linha não encontrada!\n");
		getchar();
	}
	fflush(stdin);
	
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
		
		if(count == 4)	count = 0;
		count++;
	}
	return dis;
}

void iniciarAssentos(Onibus *o){
	int count = 0;
	int lin = o->idLin;
	Data d = o->data;
	
	if(!pesquisaDataOnibus(o)){
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
}

int verificaAssento(Onibus o, int a){
	for(int i = 0; i < 20; i++){
		if(o.ass[i] == a)
			return 1;
	}
	return 0;
}

int reservarAssento(Onibus o, int ass){
	if(verificaAssento(o, ass)){
		FILE *fo = fopen(bdoni, "r+b");
		if(fo == NULL){
			printf("Erro ao abrir o banco onibus!");
			getchar();
		}	
			
		int pos = (o.id) * sizeof(Onibus);
		fseek(fo, pos, SEEK_SET);
		
		for(int i = 0; i < 20; i++){
			if(o.ass[i] == ass)
				o.ass[i] = -1;
		}
		if(fwrite(&o, sizeof(o), 1, fo)){
			fclose(fo);
			return 1;
		}
		else{
			fclose(fo);
			return -1;
		}
	}else{
		return 0;
	}
}

int getCodOni(){
    Onibus o;
    int id = 0;
	FILE *fo = fopen(bdoni, "rb");
    while(fread(&o, sizeof(o), 1, fo)){ 
        id++;
    }
	fclose(fo);
    return id+1;
}

int getTotReserva(Onibus o){
	int soma = 0;
	for(int i = 0; i < 20; i++){
		if(o.ass[i] == -1)
			soma++;
	}
	return soma;
}

void lerReserva(){
	char arq[100], str[60];
	Linha lin;
	Onibus o;
	char c;
	int ass, res, count = -1;

	printf("Arquivo: ");
	fgets(arq, sizeof(arq), stdin);
	rmvLn(arq);

	FILE *fo = fopen(arq, "r");
	flog = fopen("relatorios/log.txt", "w");
	if(fo == NULL)	printf("Erro ao abrir arquivo!\n");

	while(!feof(fo)){
		count = 0;
		do{
			c = getc(fo);
			if(isChar(c) || c == ' ' || isCharNum(c) || c == '-'){
				lin.cid[count] = c;
				count++;
			}
		}while (c != ',' && c != EOF);
		lin.cid[count] = '\0';
		toUpperCase(lin.cid);

		fscanf(fo, " %02d:%02d, %02d/%02d/%4d, %02d", &lin.hora.h,&lin.hora.m, &o.data.dia,&o.data.mes, &o.data.ano, &ass);
			// fscanf(fo, "%2d/%2d/%4d,", &o.data.dia,&o.data.mes, &o.data.ano);
			// fscanf(fo, "%2d", &ass);
		sprintf(str, "%s, %02d:%02d, %02d/%02d/%04d, %02d", lin.cid, lin.hora.h, lin.hora.m, o.data.dia, o.data.mes, o.data.ano, ass);
		if(!feof(fo)){
			if(validaHora(lin.hora)){
				if(validaData(o.data)){
					if(ass >= 1 && ass <= 20){
						if(pesquisaLin(&lin) != -1){
							o.idLin = lin.id;
							iniciarAssentos(&o);
								res = reservarAssento(o, ass);
								if(res == 1){
									logErro(6, str);
								}else if(res == -1){
									//printf("Erro efetuar reserva!\n");
								}else if(res == 0){
									logErro(0, str);
								}		
						}else{
							logErro(2, str);
							//gravar no log - linha inexistente
						}
					}else{
						logErro(5, str);
					}
				}else{
					logErro(4, str);
				}
			}else{
				logErro(3, str);
			}
		}
	}
	fclose(flog);
	fclose(fo);
	printf("Arquivo processado com sucesso!\nRelatório gravado em log.txt.");
	getchar();
}

int pesquisaDataOnibus(Onibus *o){
	int lin = o->idLin;
	Data d = o->data;
	FILE *fo = fopen(bdoni, "rb");
	if(fo == NULL)	printf("Banco não encontrado\n");
	while(fread(o, sizeof(Onibus), 1, fo)){
		if(lin == o->idLin){
			if(d.dia == o->data.dia && d.mes == o->data.mes && d.ano == o->data.ano){
				return 1;
			}
		}
	}
	return 0;
	fclose(fo);
}