#include "linha.h"

void cadastrarLinha(){
    Linha lin;
    int op;
    flin = fopen(bdlin, "a+b");
    lin.cod = getCodLin();
    printf("Codigo: %d\n", lin.cod);

    printf("Cidade: ");
    fgets(lin.cid, sizeof(lin.cid), stdin);
    toUpperCase(lin.cid);
    rmvLn(lin.cid);
    fflush(stdin);

    printf("Horário de partida: ");
    scanf("%d:%d", &lin.hora.h, &lin.hora.m);

    printf("Valor da passagem: ");
    scanf("%f", &lin.vlr);
    fflush(stdin);
    lin.ativo = 1;
    
    while(1){
        cls();
        mostrarLinha(lin);
        printf("1 - Salvar  2 - Alterar  3 - Sair\nOpção: ");
        scanf("%d", &op);
        if(op == 1){
            if(fwrite(&lin, sizeof(lin), 1, flin)){
                printf("Linha cadastrada com sucesso!");
                getchar();
                fclose(flin);
                break;
            } else {
                printf("Erro ao cadastrar linha!");
                printf("\nPressione enter para continuar!");
                getchar();
            }
        } else if(op == 2){
            printf("=== ALTERAR ===\n");
            mostrarLinha(lin);
            printf("\n1 - Cidade  2 - Horário de partida  3 - Valor  4 - voltar\nOpção: ");
            scanf("%d", &op);
			fflush(stdin);
            alterarLin(&lin, &op);
        } else if(op == 3){
            printf("Voltando ao menu...");
            getchar();            
            break;
        }


    }
}

void mostrarLinha(Linha lin){
	char h[6];
    printf("\nCodigo: %d",lin.cod);
    printf("\nSituação: %s",lin.ativo == 1?"ATIVO":"INATIVO");
    printf("\nCidade: %s", lin.cid);
	sprintf(h, "%02d:%02d",lin.hora.h, lin.hora.m);
    printf("\nHorário de partida: %s", h);
    printf("\nValor da passagem: %.2f R$\n", lin.vlr);
}

int getCodLin(){
    Linha lin;
    int linha = 0;
    rewind(flin);

    while(fread(&lin, sizeof(lin), 1, flin)){ 
        linha++;
    }
    return linha+1;
}

void consultarHorarios(){
    char cid[30];
    int est = 0;
    Linha lin;
    printf("Cidade: ");
    fgets(cid, sizeof(cid), stdin);
    fflush(stdin);
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

fpos_t pesquisarLinha(Linha *lin){
    fpos_t pos = 0;
    int cod = -1;
    char cid[30];
    Hora hora;
    printf("Cidade(Nome ou Codígo): ");
    fgets(cid, sizeof(cid), stdin);
    fflush(stdin);
    rmvLn(cid);
    if(isNum(cid)){
        cod = atoi(cid);
    }else{
        toUpperCase(cid);
        printf("Horário de partida: ");
        scanf("%d:%d", &hora.h, &hora.m);
    }
    fflush(stdin);

    flin = fopen(bdlin, "rb");

    while(fread(lin, sizeof(Linha), 1, flin)){
       
        if(cod != -1){
            if((cod == lin->cod) && lin->ativo == 1){
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
        fgetpos(flin, &pos);
    }
    pos = -1;
    fclose(flin);
    return pos;
}

void removerLinha(){
    int op;
    Linha lin;
    fpos_t pos = pesquisarLinha(&lin);
    flin = fopen(bdlin, "r+b");
    if(flin == NULL){
        printf("Erro ao abrir bd!\n");
        getchar();
    }else if(pos != -1){
        mostrarLinha(lin);
        printf("\n1 - Excluir  0 - Sair\nOpção: ");
        scanf("%d", &op);
        if(op == 1){
            fflush(stdin);
            lin.ativo = 0;
            fsetpos(flin, &pos);
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
    fpos_t pos = pesquisarLinha(&lin);
    flin = fopen(bdlin, "r+b");
    if(flin == NULL){
        printf("Erro ao abrir bd!\n");
        getchar();
    }else if(pos != -1){
        do{
			cls();
			mostrarLinha(lin);
			printf("\n1 - Cidade  2 - Horário de partida  3 - Valor  (4 - Salvar  0 - Cancelar)\nOpção: ");
			scanf("%d", &op);
			alterarLin(&lin, &op);
			if(op == 4){
				fflush(stdin);
				
				fsetpos(flin, &pos);
				if(fwrite(&lin, sizeof(Linha), 1, flin)){
					printf("Linha alterado com sucesso!");
                    op = 0;
				}else {
					printf("Erro ao alterar linha!\n");
				}
				getchar();
				fclose(flin);
			}
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
        fflush(stdin);
        *op = -1;
    }else if(*op == 2){
        printf("Horário de partida: ");
        scanf("%d:%d", &lin->hora.h, &lin->hora.m);
        *op = -1;
    }else if(*op == 3){
        printf("Valor da passagem: ");
    	scanf("%f", &lin->vlr);
        *op = -1;
    } 
}