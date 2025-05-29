#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "game.h"
#include "funcs.h"

int main(void)
{
    mkdirSaves();
    srand(time(NULL));

    while(true) gameMenu();

    return 0;
}
