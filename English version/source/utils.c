#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* Configurações específicas por sistema operacional */
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define CLEAR_COMMAND "cls"
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define CLEAR_COMMAND "clear"
    #define Sleep(ms) usleep(ms * 1000)
#endif

void clearBuffer(void)
{
    while(getchar() != '\n');
}

void loadingScreen(int time, char c, int pos_waiting)
{
    for(int i = 0; i < time; i++)
    {
        Sleep(250);
        putchar(c);
        fflush(stdout);
    }
    Sleep(pos_waiting * 1000);
}

void clearScreen(int waiting)
{
    Sleep(waiting * 1000);
    system(CLEAR_COMMAND);
}
