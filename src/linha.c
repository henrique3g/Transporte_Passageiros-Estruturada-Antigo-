#include "linha.h"


void cadastrarLinha(){
    Linha lin;
    int op;
    FILE *flin = fopen(bdlin, "ab");
    lin.id = getCodLin();
    printf("\nCodigo: %d\n", lin.id);
    printf("Cidade: ");
    fgets(lin.cid, sizeof(lin.cid), stdin);
    toUpperCase(lin.cid);
    rmvLn(lin.cid);

    printf("Horário de partida: ");
    scanf("%2d:%2d", &lin.hora.h, &lin.hora.m);
    clearBuf();
    if(validaHora(lin.hora)){

        printf("Valor da passagem: ");
        scanf("%6f", &lin.vlr);
        clearBuf();
        lin.ativo = 1;
        
        while(1){
            cabecalho(1);
            mostrarLinha(lin);
            printf("\n1 - Salvar  2 - Alterar  0 - Voltar\nOpção: ");
            scanf("%1d", &op);
            clearBuf();
            if(op == 1){
                if(fwrite(&lin, sizeof(lin), 1, flin)){
                    printf("Linha cadastrada com sucesso!\n");
                    getchar();
                    fclose(flin);
                    break;
                } else {
                    printf("Erro ao cadastrar linha!");
                    printf("\nPressione enter para continuar!\n");
                    getchar();
                }
            } else if(op == 2){
                while(1){
                    cabecalho(3);
                    mostrarLinha(lin);
                    printf("\n1 - Cidade  2 - Horário de partida  3 - Valor  0 - voltar\nOpção: ");
                    scanf("%1d", &op);
                    clearBuf();
                    alterarLin(&lin, &op);
                    if(op == 0) break;
                }
            } else if(op == 0){            
                break;
            }


        }
    }else{
        printf("Erro! Hora invalida!\n");
        getchar();
    }
}

void mostrarLinha(Linha lin){
	char h[6];
    printf("\nCodigo: %d",lin.id);
    //printf("\nSituação: %s",lin.ativo == 1?"ATIVO":"INATIVO");
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s", h);
    printf("\nValor da passagem: %.2f R$\n", lin.vlr);
}
void mostrarLinhaS(Linha lin){
	char h[6];
    printf("\nCodigo: %d",lin.id);
    //printf("\nSituação: %s",lin.ativo == 1?"ATIVO":"INATIVO");
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s\n", h);
    //printf("\nValor da passagem: %.2f R$\n", lin.vlr);
}

int getCodLin(){
    FILE *flin = fopen(bdlin, "rb");
    Linha lin;
    int id = 0;
    
    while(fread(&lin, sizeof(lin), 1, flin)){ 
        id++;
    }
    return id+1;
}

void consultarHorarios(){
    char cid[30];
    int est = 0;
    Linha lin;
    printf("Cidade: ");
    fgets(cid, sizeof(cid), stdin);
    rmvLn(cid);
    toUpperCase(cid);

    FILE *flin = fopen(bdlin, "rb");
    if(flin == NULL){
        printf("Erro! Não existe linhas cadastradas!\n");
    }else{
        while(fread(&lin, sizeof(lin), 1, flin)){
            if((!strcmp(lin.cid, cid)) && lin.ativo == 1){
                printf("%d:%d\t%.2f R$\n",lin.hora.h,lin.hora.m,lin.vlr);
                est = 1;
            }
        }
        if(!est)    printf("Cidade não encontrada!\n");
        getchar();
    }

}

int pesquisarLinha(Linha *lin){
    int pos = 0;
    int cod = -1;
    char cid[30];
    Hora hora;
    printf("\nCidade ou Código: ");
    fgets(cid, sizeof(cid), stdin);
    rmvLn(cid);
    if(isNum(cid)){
        cod = atoi(cid);
    }else{
        toUpperCase(cid);
        printf("Horário de partida: ");
        scanf("%2d:%2d", &hora.h, &hora.m);
        clearBuf();
    }
    if(validaHora(hora) || cod != -1){

        FILE *flin = fopen(bdlin, "rb");

        while(fread(lin, sizeof(Linha), 1, flin)){
        
            if(cod != -1){
                if((cod == lin->id) && lin->ativo == 1){
                    fclose(flin);
                    return pos;
                }
            }else{
                if(!strcmp(cid, lin->cid)){
                    if((hora.h == lin->hora.h && hora.m == lin->hora.m) && lin->ativo == 1){
                        fclose(flin);
                        return pos;
                    }
                }
            }
            pos++;
        }
        fclose(flin);
    }
    printf("Erro! Hora invalida!\n");
    getchar();
    return -1;
}

void removerLinha(){
    int op;
    Linha lin;
    int pos = pesquisarLinha(&lin)*sizeof(Linha);
    FILE *flin = fopen(bdlin, "r+b");
    if(flin == NULL){
        printf("Erro ao abrir bd!\n");
        getchar();
    }else if(pos != -1){
        cabecalho(2);
        mostrarLinha(lin);
        printf("\n1 - Excluir  0 - Voltar\nOpção: ");
        scanf("%1d", &op);
        clearBuf();
        if(op == 1){
            lin.ativo = 0;
            fseek(flin, pos, SEEK_SET);
            if(fwrite(&lin, sizeof(Linha), 1, flin)){
            	printf("Linha excluida com sucesso!");
        	}else {
            	printf("Erro ao remover linha!\n");
        	}
        	getchar();
        	fclose(flin);
        }
    }else {
		printf("Linha não encontrada!");
        getchar();
    }
}
void alterarLinha(){
    int op;
    Linha lin;
    int pos = pesquisarLinha(&lin)*sizeof(Linha);
    FILE *flin = fopen(bdlin, "r+b");
    if(flin == NULL){
        printf("Erro ao abrir bd!\n");
        getchar();
    }else if(pos != -1){
        do{
			cabecalho(3);
			mostrarLinha(lin);
			printf("\n1 - Cidade  2 - Horário de partida  3 - Valor  (4 - Salvar  0 - Cancelar)\nOpção: ");
			scanf("%1d", &op);
			clearBuf();
			if(op == 4){
				
				fseek(flin, pos, SEEK_SET);
				if(fwrite(&lin, sizeof(Linha), 1, flin)){
					printf("Linha alterado com sucesso!\n");
                    op = 0;
				}else {
					printf("Erro ao alterar linha!\n");
				}
				getchar();
				fclose(flin);
			}
			alterarLin(&lin, &op);
		} while (op != 0);
	}else {
		printf("Linha não encontrada!");
		getchar();
	}
      
}

void listarLinhas(){
    FILE *flin = fopen(bdlin, "rb");
    Linha lin;
    int count=0;
    while(fread(&lin, sizeof(lin), 1, flin)){
        if(lin.ativo == 1){
            // printf("\n");
            mostrarLinha(lin);
            count = 1;
        }
    }
    if(!count){
        printf("\nNão existe linhas cadastradas!\n");
    }
    getchar();
}


void alterarLin(Linha *lin, int *op){
	cls();
    if(*op == 1){
        printf("Cidade: ");
        fgets(lin->cid, sizeof(lin->cid), stdin);
        rmvLn(lin->cid);
        *op = -1;
    }else if(*op == 2){
        printf("Horário de partida: ");
        scanf("%2d:%2d", &lin->hora.h, &lin->hora.m);
        clearBuf();
        if(validaHora(lin->hora)){
            *op = -1;
        }else{
            printf("Erro! Hora invalida!\n");
            getchar();
            *op = 0;
        }
    }else if(*op == 3){
        printf("Valor da passagem: ");
    	scanf("%6f", &lin->vlr);
        clearBuf();
        *op = -1;
    } 
}

int pesquisaLin(Linha *lin){
    FILE *flin = fopen(bdlin, "rb");
    Hora hora = lin->hora;
    char cid[30];
    int pos = 0;
    strcpy(cid, lin->cid);
    
    while(fread(lin, sizeof(Linha), 1, flin)){
        if(!strcmp(cid, lin->cid)){
            if((hora.h == lin->hora.h && hora.m == lin->hora.m) && lin->ativo == 1){
                fclose(flin);
                return pos;
            }
        }
        pos++;
    }
    pos = -1;
    fclose(flin);
    return pos;
}