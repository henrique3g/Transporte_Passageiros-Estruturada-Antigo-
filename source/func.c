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
    /* #ifdef __unix__
        __fpurge(stdin);
        
    #elif defined(_WIN32) || defined(WIN32)
        fflush(stdin);
    #endif */
    char c;
    while((c = getchar()) != '\n' && c != EOF);

}

void rmvLn(char *s){
    if(s[strlen(s) - 1] == '\n')
        s[strlen(s) - 1] = '\0';
}

void toUpperCase(char *s){
    for(int i = 0; i < strlen(s); i++){
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

int isPar(int n){
    if(n % 2)
        return 0;
    return 1;
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

int isChar(char c){
    toUpper(&c);
    if(c > 64 && c < 91)
        return 1;
    return 0;
}

void lerData(Data *d){
	scanf("%2d/%2d/%4d", &d->dia, &d->mes, &d->ano);
    clearBuf();
}

Data getData(){
    Data d;
    time_t t;
    int b;
    char s[4];
    time(&t);
    sscanf(ctime(&t), "%3s %3s %2d %2d:%2d:%2d %4d", s, s, &d.dia, &b, &b, &b, &d.ano);
    d.mes = formatMes(s);
    return d;
}

int formatMes(char *s){
    if(!strcmp(s, "Jan"))
        return 1;
    else if(!strcmp(s, "Feb"))
        return 2;
    else if(!strcmp(s, "Mar"))
        return 3;
    else if(!strcmp(s, "Apr"))
        return 4;
    else if(!strcmp(s, "May"))
        return 5;
    else if(!strcmp(s, "Jun"))
        return 6;
    else if(!strcmp(s, "Jul"))
        return 7;
    else if(!strcmp(s, "Aug"))
        return 8;
    else if(!strcmp(s, "Sep"))
        return 9;
    else if(!strcmp(s, "Oct"))
        return 10;
    else if(!strcmp(s, "Nov"))
        return 11;
    else if(!strcmp(s, "Dec"))
        return 12;
}
Hora getHora(){
    Hora h;
    time_t t;
    int b;
    char s[5];
    time(&t);
    sscanf(ctime(&t), "%3s %3s %2d %2d:%2d:%2d %4d", s, s, &b, &h.h, &h.m, &b, &b);
    return h;
}

int getDiaSemana(){
    time_t t;
    time(&t);
    char d[4];
    strncpy(d, ctime(&t), 3);
    d[3] = '\0';
    if(!strcmp(d, "Sun")){
        return 1;
    }else if(!strcmp(d, "Mon")){
        return 2;
    }else if(!strcmp(d, "Tue")){
        return 3;
    }else if(!strcmp(d, "Wed")){
        return 4;
    }else if(!strcmp(d, "Thu")){
        return 5;
    }else if(!strcmp(d, "Fri")){
        return 6;
    }else if(!strcmp(d, "Sat")){
        return 7;
    }
}

int getDiaSemanaE(Data d){
    int dia = getDiaSemana(); // = 5
    int dif = diffDate(d, getData());
    
    if(dif < 0){
        for(int i = 1; i <= abs(dif); i++){
            dia++;
            if(dia > 7)
                dia = 1;
        }
    }else{
        for(int i = 1; i <= dif; i++){
            dia--;
            if(dia < 7)
                dia = 7;
        }
    }
    
    return dia;
}

int diffDate(Data i, Data f){
    int d;
    if(i.mes == f.mes){
        d = f.dia - i.dia;
        return d;
    }

}

int validaData(Data d){
    if((d.dia >= 1 && d.dia <= 31) && (d.mes >= 1 && d.mes <= 12) && (d.ano > 2000 && d.ano <= 2100)){
        if(d.mes == 2){
            if(!(d.ano % 4)){
                if(d.dia <= 29)
                    return 1;
            }else{
                if(d.dia <= 28)
                    return 1;
            }
            return 0;    
        }else if(d.mes <= 7){
            if(isPar(d.mes) && d.dia <= 30)
                return 1;
            else if(!isPar(d.mes) && d.dia <= 31)
                return 1;
            return 0;            
        }else if(d.mes >= 8){
            if(isPar(d.mes) && d.dia <= 31)
                return 1;
            else if(!isPar(d.mes) && d.dia <= 30)
                return 1;
            return 0;
        }
    }
    return 0;
}

int validaHora(Hora h){
    if((h.h >= 0 && h.h <= 23) && (h.m >= 0 && h.m <= 59))
        return 1;
    return 0;
}