#include "includes.h"


// adicionado em main.c
int main(void)
{
    srand(time(NULL));
    criarPastaSaves();

    while(true)
        menu();

    return 0;
}
