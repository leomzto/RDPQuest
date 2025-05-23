#include "includes.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void limparBuffer(void) {
    while(getchar() != '\n');
}

void animacaoCarregamento(int tempo, char caractere, int espera) {
    for(int i = 0; i < tempo; i++) {
        #ifdef _WIN32
        Sleep(250);
        #else
        usleep(250000);
        #endif
        putchar(caractere);
        fflush(stdout);
    }
    
    #ifdef _WIN32
    Sleep(espera * 1000);
    #else
    sleep(espera);
    #endif
}

void limparTela(int espera) {
    #ifdef _WIN32
    Sleep(espera * 1000);
    system("cls");
    #else
    sleep(espera);
    system("clear");
    #endif
}