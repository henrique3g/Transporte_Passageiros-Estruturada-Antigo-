#include "linha.h"


void cadastrarLinha(){
    Linha lin;
    int op;
    flin = fopen(bdlin, "a+b");
    lin.id = getCodLin();
    printf("Codigo: %d\n", lin.id);
    clearBuf();
    printf("Cidade: ");
    fgets(lin.cid, sizeof(lin.cid), stdin);
    toUpperCase(lin.cid);
    rmvLn(lin.cid);
    clearBuf();

    printf("Horário de partida: ");
    scanf("%2d:%2d", &lin.hora.h, &lin.hora.m);
    clearBuf();
    printf("Valor da passagem: ");
    scanf("%6f", &lin.vlr);
    clearBuf();
    lin.ativo = 1;
    
    while(1){
        cls();
        printf("//////////////////////////////\n");
        printf("//     Cadastrar Linha      //\n");
        printf("//////////////////////////////\n");
        mostrarLinha(lin);
        printf("1 - Salvar  2 - Alterar  0 - Voltar\nOpção: ");
        scanf("%1d", &op);
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
                cls();
                printf("//////////////////////////////\n");
                printf("//          Alterar         //\n");
                printf("//////////////////////////////\n");
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
}

void mostrarLinha(Linha lin){
	char h[6];
    printf("Codigo: %d",lin.id);
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
    Linha lin;
    int id = 0;
    rewind(flin);

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
    clearBuf();
    rmvLn(cid);
    toUpperCase(cid);

    flin = fopen(bdlin, "rb");
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
    printf("Cidade(Nome ou Código): ");
    fgets(cid, sizeof(cid), stdin);
    clearBuf();
    rmvLn(cid);
    if(isNum(cid)){
        cod = atoi(cid);
    }else{
        toUpperCase(cid);
        printf("Horário de partida: ");
        scanf("%2d:%2d", &hora.h, &hora.m);
    }
    clearBuf();

    flin = fopen(bdlin, "rb");

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
    pos = -1;
    fclose(flin);
    return pos;
}

void removerLinha(){
    int op;
    Linha lin;
    int pos = pesquisarLinha(&lin)*sizeof(Linha);
    flin = fopen(bdlin, "r+b");
    if(flin == NULL){
        printf("Erro ao abrir bd!\n");
        getchar();
    }else if(pos != -1){
        mostrarLinha(lin);
        printf("\n1 - Excluir  0 - Voltar\nOpção: ");
        scanf("%1d", &op);
        if(op == 1){
            clearBuf();
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
    flin = fopen(bdlin, "r+b");
    if(flin == NULL){
        printf("Erro ao abrir bd!\n");
        getchar();
    }else if(pos != -1){
        do{
			cls();
            printf("//////////////////////////////\n");
            printf("//      Alterar Linha       //\n");
            printf("//////////////////////////////\n");
			mostrarLinha(lin);
			printf("\n1 - Cidade  2 - Horário de partida  3 - Valor  (4 - Salvar  0 - Cancelar)\nOpção: ");
			scanf("%1d", &op);
			if(op == 4){
				clearBuf();
				
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
    flin = fopen(bdlin, "rb");
    Linha lin;
    int count=0;
    while(fread(&lin, sizeof(lin), 1, flin)){
        if(lin.ativo == 1){
            printf("\n");
            mostrarLinha(lin);
            count = 1;
        }
    }
    if(!count){
        printf("\nNão existe linhas cadastradas!\n");
    }
    clearBuf();
    getchar();
}


void alterarLin(Linha *lin, int *op){
	cls();
    if(*op == 1){
        printf("Cidade: ");
        fgets(lin->cid, sizeof(lin->cid), stdin);
        rmvLn(lin->cid);
        clearBuf();
        *op = -1;
    }else if(*op == 2){
        printf("Horário de partida: ");
        scanf("%2d:%2d", &lin->hora.h, &lin->hora.m);
        clearBuf();
        *op = -1;
    }else if(*op == 3){
        printf("Valor da passagem: ");
    	scanf("%6f", &lin->vlr);
        clearBuf();
        *op = -1;
    } 
}