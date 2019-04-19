#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

uint borrar_bits(uint x, uint pat, int len){
    //reemplaza por 0's todas las instancias del patron pat de largo len en x
    int m, c = 33 -len, n = -1;
    m = len == 32 ? -1 : (1<<len)-1;
    while(c--){
        uint y = x&m;
        if(y == pat) n &= ~m;
        pat <<= 1;
        m <<= 1;
    }
    return x&n;
}

char *reemplazo(char *s, char c, char *pal){
    //reemplaza todas las instancias de c por pal en s (retorna el nuevo string)
    if(!*s) return "";
    char* r = s;
    int t = 0;
    while(*r){
        if(*r == c) t++;
        r++;
    }
    char* p = pal;
    while(*p) p++;
    int lp = p - pal;
    int l = r + (lp-1)*t -s;
    char* ns = malloc(l*sizeof(char*));
    char* aux = ns;
    while(*s){
        if(*s == c){
            p = pal;
            while(*p){
                *aux = *p;
                aux++;
                p++;
            }
        }
        else{
            *aux = *s;
            aux++;
        }
        s++;
    }
    return ns;
}

void reemplazar(char *s, char c, char *pal){
    //reemplaza todas las instancias de c por pal en s (modifica s)
    if(!*s) return;
    char* r = s;
    int t = 0;
    while(*r){
        if(*r == c) t++;
        r++;
    }
    int lo = r - s;
    if(*pal){
        char* p = pal;
        while(*p) p++;
        int lp = p - pal;
        int lm = lo + (lp-1)*t;
        char* a = s + lo;
        char* b = s + lm;
        while(a-s){
            if(*a == c){
                p = pal + lp - 1;
                while(p-pal+1){
                    *b = *p;
                    b--;
                    p--;
                }
            } 
            else{
                *b = *a;
                b--;
            }
            a--;
        }
    }
    else{
        char* a = s;
        char* b = s;
        while(lo--){
            if(*a != c){
                *b = *a;
                b++;
            }
            a++;
        }
        *b = '\0';
    }
}