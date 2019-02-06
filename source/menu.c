#include "menu.h"
#include "func.h"

void menu(){
    int op;
    do{
        op = -1;
        cabecalho(11);
        printf("1 - Inserir linha\n");
        printf("2 - Remover linha\n");
        printf("3 - Alterar linha\n");
        printf("4 - Listar linhas\n");
        printf("5 - Consultar horários\n");
        printf("6 - Consultar assento disponivel\n");
        printf("7 - Relatórios\n");
        printf("8 - Ler reservas de arquivos texto\n");
        printf("0 - Sair\n");
        printf("OPÇÃO: ");
        clearBuf();
        scanf("%1d", &op);
        clearBuf();
        opcao(op);
    }while(op != 0);
}

void opcao(int op){
    switch (op){
        case 1:
            cabecalho(1);
            cadastrarLinha();
            break;
        case 2:
            cabecalho(2);
            removerLinha();
            break;
        case 3:
            cabecalho(3);
            alterarLinha();
            break;
        case 4:
            cabecalho(4);
            listarLinhas();
            break;
        case 5:
            cabecalho(5);
            consultarHorarios();
            break;
        case 6:
            cabecalho(6);
            consultarAssentos();
            break;
        case 7:
            cabecalho(7);
            menuRel();
            break;
        case 8:
            cabecalho(8);
            lerReserva();
            break;
        case 0:
            printf("Saindo...");
            getchar();    
            break;
        default:
            printf("Opção Invalida!");
            getchar();
            break;
    }
}

void menuRel(){
	int op;
	cabecalho(7);
    printf("1 - Total arrecadado (tela)\n");
    printf("2 - Total arrecadado (arquivo)\n");
    printf("3 - Ocupação percentual media (tela)\n");
    printf("4 - Ocupação percentual media (arquivo)\n");
    printf("0 - Voltar\n");
	printf("OPÇÃO: ");
    scanf("%1d", &op);
    clearBuf();
    if(op == 1){
		relArrecTela();
	}else if(op == 2){
		relArrecArq();
	}else if(op == 3){
        relOcupTela();
	}else if(op == 4){
        relOcupArq();
	}
}

void cabecalho(int i){
	if(i == 1){
		printCabecalho("Cadastrar Linha");
	}else if(i == 2){
		printCabecalho("Remover Linha");
	}else if(i == 3){
		printCabecalho("Alterar Linha");
	}else if(i == 4){
		printCabecalho("Listar Linha");
	}else if(i == 5){
		printCabecalho("Consular Horários");
	}else if(i == 6){
		printCabecalho("Consultar Assentos");
	}else if(i == 7){
		printCabecalho("Relatórios");
	}else if(i == 8){
		printCabecalho("Ler reservas de arquivo texto");
	}else if(i == 9){
		printCabecalho("Relatório Arrecadação Mensal");
	}else if(i == 10){
		printCabecalho("Relatório Ocupacao percentual media");
	}else if(i == 11){
		printCabecalho("Menu");
	}else if(i == 12){
		printCabecalho("Relatórios");
	}
	
}

void printCabecalho(char *s){
	cls();
	int t = (int)strlen(s);
	int sp = (43/2) - (t/2);
	printf("///////////////////////////////////////////////\n");
    printf("//                                           //\n//");
	for(int i = 0; i < sp; i++){
		printf(" ");
	}
	printf("%s", s);
	sp = (isPar(t)? (sp+1):(sp));
	for(int i = 0; i < sp; i++){
		printf(" ");
	}
    printf("//\n//                                           //\n");
    printf("///////////////////////////////////////////////\n");
}