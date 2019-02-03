#include "func.h"

void cls(){
    #ifdef __unix__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32)
        system("cls");
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