#include <stdbool.h>
#include <stdio.h>
#include "Logic.h"


int main()
{
    bool quitGame = false;
    bool isEndOfGame = false;
    srand(time(NULL));

    do
    {
        Settings();
        //SimulateGame(&isEndOfGame, StartGame(&isEndOfGame));
    } while (!NewGame());



    return 0;
}
