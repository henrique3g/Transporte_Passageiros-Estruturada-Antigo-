#include "menu.h"

void menu(){
    int op;
    do{
        op = -1;
        cls();
        printf("////////////////////////////////\n");
        printf("//             MENU           //\n");    
        printf("////////////////////////////////\n");
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
        scanf("%d", &op);
        fflush(stdin);
        opcao(op);
    }while(op != 0);
}

void opcao(int op){
    switch (op){
        case 1:
            cls();
            printf("//////////////////////////////\n");
            printf("//     Cadastrar Linha      //\n");
            printf("//////////////////////////////\n");
            cadastrarLinha();
            break;
        case 2:
            cls();
            printf("//////////////////////////////\n");
            printf("//      Remover Linha       //\n");
            printf("//////////////////////////////\n");
            removerLinha();
            break;
        case 3:
            cls();
            printf("//////////////////////////////\n");
            printf("//      Alterar Linha       //\n");
            printf("//////////////////////////////\n");
            alterarLinha();
            break;
        case 4:
            cls();
            printf("//////////////////////////////\n");
            printf("//      Listar Linhas       //\n");
            printf("//////////////////////////////\n");
            listarLinhas();
            break;
        case 5:
            cls();
            printf("//////////////////////////////\n");
            printf("//     Consular Horários    //\n");
            printf("//////////////////////////////\n");
            consultarHorarios();
            break;
        case 6:
            printf("//////////////////////////////\n");
            printf("//     Cadastrar Linha      //\n");
            printf("//////////////////////////////\n");
            
            break;
        case 7:
            printf("//////////////////////////////\n");
            printf("//     Cadastrar Linha      //\n");
            printf("//////////////////////////////\n");
            
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