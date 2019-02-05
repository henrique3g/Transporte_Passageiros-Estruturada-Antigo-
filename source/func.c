#include "func.h"

/*void cls(){
    system("cls");

}*/
 void cls(){
    #ifdef __unix__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32)
        system("cls");
    #endif
} 

void clearBuf(){
    #ifdef __unix__
        __fpurge(stdin);
        
    #elif defined(_WIN32) || defined(WIN32)
        fflush(stdin);
    #endif
}

void rmvLn(char *s){
    if(s[strlen(s) - 1] == '\n')
        s[strlen(s) - 1] = '\0';
}

void toUpperCase(char *s){
    for(int i = 0; i < 30; i++){
        if(!i)  toUpper(s);
        else{
            toLower(&s[i]);
            if(s[i] == ' '){
                toUpper(&s[i+1]);
                i++;
            }
        }
    }
}

void toUpper(char *c){
    if(*c > 96 && *c < 123)
        *c -= 32;
}

void toLower(char *c){
    if(*c > 64 && *c < 91)
        *c += 32;
}

int isNum(char *s){
    for(unsigned int i = 0; i < strlen(s); i++)
        if(!isCharNum(s[i]))
            return 0;
    return 1;
}

int isCharNum(char c){
    if(c > 47 && c < 57)
        return 1;
    return 0;
}

void lerData(Data *d){
	scanf("%2d/%2d/%4d", &d->dia, &d->mes, &d->ano);
}