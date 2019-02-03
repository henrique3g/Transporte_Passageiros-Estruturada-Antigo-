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
            if(op == 1){
                printf("Cidade: ");
                fgets(lin.cid, sizeof(lin.cid), stdin);
                rmvLn(lin.cid);
                fflush(stdin);
            }else if(op == 2){
                printf("Horário de partida: ");
                scanf("%d:%d", &lin.hora.h, &lin.hora.m);
            }else if(op == 3){
                printf("Valor da passagem: ");
                scanf("%f", &lin.vlr);
            }
        } else if(op == 3){
            printf("Voltando ao menu...");
            getchar();            
            break;
        }


    }
}

void mostrarLinha(Linha lin){
    printf("\nCodigo: %d",lin.cod);
    printf("\nCidade: %s", lin.cid);
    printf("\nHorário de partida: %d:%d", lin.hora.h, lin.hora.m);
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
            if((!strncmp(lin.cid, cid, strlen(cid))) && lin.ativo == 1){
                printf("\n%d:%d\t%.2f R$",lin.hora.h,lin.hora.m,lin.vlr);
                est = 1;
            }
        }
        if(!est)    printf("Não foi encontrado cidade com esse nome!\n");
        getchar();
    }

}

fpos_t pesquisarLinha(Linha *lin){
    fpos_t pos;
    char cid[30];
    Hora hora;

    printf("Cidade: ");
    fgets(cid, sizeof(cid), stdin);
    fflush(stdin);
    rmvLn(cid);
    toUpperCase(cid);

    printf("Horário de partida: ");
    scanf("%d:%d", &hora.h, &hora.m);

    flin = fopen(bdlin, "rb");
    fgetpos(flin, &pos);

    while(fread(&lin, sizeof(lin), 1, flin)){
        if(!strcmp(cid, lin->cid)){
            if((hora.h == lin->hora.h && hora.m == lin->hora.m) && lin->ativo == 1){

                fclose(flin);
                return pos;
            }
        }
        fgetpos(flin, &pos);
    }
    pos = -1;
    fclose(flin);
    return pos;
}

void removerLinha(){
    flin = fopen(bdlin, "ab");
    Linha lin;
    fpos_t pos = pesquisarLinha(&lin);
    if(pos != -1){
        fsetpos(flin, &pos);
        fflush(stdin);
        lin.ativo = 0;
        if(fwrite(&lin, sizeof(lin), 1, flin)){
            printf("Arquivo excluido com sucesso!");
            getchar();
        }
        printf("Erro ao remover linha!\n");
        getchar();
        fclose(flin);
    }else {
        printf("Linha não encontrada!");
        getchar();
    }
}