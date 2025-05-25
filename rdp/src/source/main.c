#include "includes.h"

int main(void)
{
    srand(time(NULL));
    criarPastaSaves();

    while(true)
        menu();

    return 0;
}