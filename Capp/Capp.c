#include <stdbool.h>
#include <stdio.h>
#include "Logic.h"


int main()
{
    srand(time(NULL));

    do
    {
        ParseMenu(NewState());
        system("cls");
    } while (!quitGame);


    return 0;
}
