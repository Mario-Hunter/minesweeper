#include <stdio.h>
#include <stdlib.h>
#include "adj.h"
#include "graph.h"
#include "populating.h"
#include "minePopulation.h"
//#include "printingGrid.h"
#include "judge.h"
#include "inputHandler.h"
#include "fileHandler.h"


int main()
{
    
    printf("\n\nWelcome to MinesWeeper game, Mario's Special edition\n\n"
            "You are obligated now to enter a query\n"
            "Please refrain to the instructions, any misspelling would cause you to start all over\n"
            "Do You want to start a new game,or open an existing one,\n"
            "or maybe you wanna grab a look on the leaderboard?\n[n,o,l]\n");
    char query ;
    fflush(stdin);

    scanf("%c",&query);
    switch (query){
        case 'n':
            startGame();
            break;
        case 'o':
            loadGame();
            break;
        case 'l':
            showLeaderBoard();
            break;
        default:
            main();
            break;
        
    }
    
    return 0;
}
