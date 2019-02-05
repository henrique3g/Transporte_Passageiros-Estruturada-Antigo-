#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar();
void compilar();
void execultar();

int main(int argc, char const *argv[]){
    if(argc == 1){
        printf("\"ag clean\" - Remove os arquivos .o e o arquivo Sistema.exe\n");
        printf("\"ag comp\" - Executa 'clean' e compila o Sistema com o makefile\n");
        printf("\"ag exec\" - Executa 'comp' e executa o Sistema\n");
    }else{
        if(!strcmp(argv[1], "clean"))
            limpar();
        else if(!strcmp(argv[1], "comp"))
            compilar();
        else if(!strcmp(argv[1], "exec"))
            execultar();
        else
            printf("Argumento invalido!\n");
    }
    return 0;
}

void limpar(){
    system("rd objects /s /q");
    system("del Sistema.exe");
}
void compilar(){
    limpar();
    system("make");
}
void execultar(){
    compilar();
    system("Sistema.exe");
}
