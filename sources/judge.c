
#include <stdio.h>
#include "graph.h"
#include "judge.h"
#include <time.h>
#include "timeHandler.h"
#include "fileHandler.h"
#include <string.h>
#include "mergeSort.h"
#include "binarySearch.h"



char * setUser(void) {
    printf("Enter Your name:\nYou are permitted 9 characters any more characters will be truncated\n");
    char user[10];
    scanf("%s", &user);
    //printf("%s",user);
    /*char c ;
    for (int i=0;i<9;i++){
        
        scanf("%c",&c);
        strcat(user,c);
    }
    while (strcmp(c,'\0') != 0){
        scanf("%c",&c);
    }*/
    return user;
}

void setLose(judge_t *judge) {
    judge->gameState = 0;
    return;
}

void openEmpty(graph_t *graph, judge_t *judge, int v) {
    depthFirstSearch(graph, v);
    return;
}

graph_p createJudge(void) {
    judge_p judge = (judge_p) malloc(sizeof (judge_t));
    judge->gameScore = 0;
    judge->gameState = 1;
    return judge;
}

__inline graph_p getGraph(judge_t *judge) {
    return judge->grid;
}

void judgeCreateGraph(judge_t *judge, int width, int height, graph_type_e type) {
    judge->grid = createGraph(width*height, DIRECTED);
    //setWidth(getGraph(judge),width);
    //setHeight(getGraph(judge),height);
    judge->grid->height = height;
    judge->grid->width = width;
}

void gamePlay(judge_t *judge) {
    setTime(&judge->gameStartTime);
    printGrid(judge);

    printf("\nGame is starting...\n");

    while (judge->gameState) {
        takeInput(judge);
        printGrid(judge);
        printf("I will check you now,opened cells =%d \n", getGraph(judge)->openedCells);
        printf("time elapsed in seconds = %d \n", judge->gameTime);
        printf("Your score Now is %d \n\n", getScore(judge, judge->gameTime));
    }
}

void loadGame() {
    judge_p judge = openFile();
    gamePlay(judge);
}

void startGame(void) {
    printf("\nGame is starting .. \n");
    printf("MAY THE ODDS BE EVER IN YOUR FAVOR!\n\n");

    judge_p judge = createJudge();
    strcpy(judge->user, setUser());

    int width, height;

    printf("Please enter the width followed by the height."
            "\nRow and coloumns limitations are [2,1000]\n");
    fflush(stdin);
    //while(getchar() == '\n');
    scanf("%d %d", &width, &height);
    while ((width <= 1 || width > 1000) || (height <= 1 || height > 1000)) {

        printf("Inappropriate Inputs try again:\n");
        while (getchar() == "\n" || getchar() == '\0');
        scanf("%d %d", &width, &height);
        //printf("scanned values ->%d<- ->%d<-", width, height);

    }


    printf("\n\nThe grid is gonna have %d coloumns and %d rows.\n\n", width, height);

    //printf("game play is about to be called");

    judgeCreateGraph(judge, width, height, DIRECTED);
    populateGraph(judge);


    //setMine(getGraph(judge),0);
    //displayGraph(getGraph(judge));
    getGraph(judge)->mines = 1 + (getGraph(judge)->width * getGraph(judge)->height) / 10;
    getGraph(judge)->flags = 0;
    getGraph(judge)->openedCells = 0;
    getGraph(judge)->startingNode = -1;
    judge->moves = 0;
    gamePlay(judge);
    return;
}

void openCell(judge_p *judge, graph_t *graph, int v) {
    printf("\nOpening..\n ");
    int state = getState(graph, v);
    int mines, flags;
    switch (state) {
        case 0:
            if (getMine(graph, v)) {
                setState(graph, v, 1);
                lose(judge);
            } else {
                setState(graph, v, 2);
                graph->openedCells++;
                if (getAdjacentMine(graph, v) == 0) {
                    depthFirstSearch(graph, v);
                }
            }
            break;
        case 2:
            mines = getAdjacentMine(graph, v);
            flags = getAdjacentFlag(graph, v);
            if (mines != 0 && flags == mines) {
                adjlist_node_p node = graph->adjListArr[v].head;
                while (node) {
                    if (node->state != 3) {
                        openCell(judge, graph, node->vertex);
                    }
                    node = node->next;
                }
            }
            break;
        case 3:
            if (getMine(graph, v)) {
                setState(graph, v, 1);
                lose(judge);
            } else {
                setState(graph, v, 2);
                graph->openedCells++;
            }
            break;
        case 4:
            if (getMine(graph, v)) {
                setState(graph, v, 1);
                lose(judge);
            } else {
                setState(graph, v, 2);
                graph->openedCells++;
            }
            break;

    }
    return;
}

void flagCell(graph_t *graph, int v) {
    int state = getState(graph, v);
    switch (state) {
        case 0:

            setState(graph, v, 3);
            graph->flags++;
            break;
        case 2:
            printf("You can NOT flag an open cell.\n");
            break;
        case 3:
            printf("You can NOT flag a flagged cell.\n");
            break;
        case 4:
            setState(graph, v, 3);
            graph->flags++;
            break;


    }
}

void questionCell(graph_t *graph, int v) {
    int state = getState(graph, v);
    switch (state) {
        case 0:

            setState(graph, v, 4);
            break;



        case 2:
            printf("You can NOT question an open cell.\n");
            break;

        case 4:

            setState(graph, v, 4);
            break;


    }
}

void checkWin(judge_t *judge) {
    graph_p grid = judge->grid;
    if (grid->mines == grid->flags && grid->flags + grid->openedCells == grid->num_vertices) {
        int score = getScore(judge);
        judge->gameState = 0;
        printf("\nYou win\n\a");
        FILE *scores = fopen("./saved/tmp/leaderboard.dat", "r+");
        int users;
        fscanf(scores, "%d", &users);
        printf("the users in users = %d\n", users);
        int scoresList[users + 1];
        for (int i = 0; i < users; i++) {
            char user[100];
            int score;
            fscanf(scores, "%s %d", &user, &score);
            if (strcmp(user, judge->user) == 0) {
                printf("\n\nscaneed score:%d\n\njudge score = %d", score, judge->gameScore);
                //int pos = log(score)+1;
                score += judge->gameScore;
                fseek(scores, -10, SEEK_CUR);
                fprintf(scores, "%10d\n", score);
                fclose(scores);
                finishGame(judge, score);
            }

        }

        fseek(scores, 0, SEEK_END);
        fprintf(scores, "\n%s %10d", judge->user, judge->gameScore);
        fseek(scores, 0, SEEK_SET);
        users++;
        fprintf(scores, "%d", users);
        fclose(scores);
        finishGame(judge, score);
    }
}

void finishGame(judge_t *judge, int score) {
    FILE *leaderboard = fopen("./saved/tmp/leaderboard.dat", "r");
    int users;
    fscanf(leaderboard, "%d", &users);
    player players[users];
    for (int i = 0; i < users; i++) {
        
        fscanf(leaderboard, "%s", &players[i].name);
        fscanf(leaderboard, "%d", &players[i].score);
        
        //printf("%d  ", scoresList[i]);
    }
    fclose(leaderboard);
    printf("score = %d\n", score);
    mergeSort(players, users);
    printf("\nYour rank is %d out of %d.\n", users - binarySearch(players, 0, users - 1, score), users);
    printf("Try again?\n[Y/N]\n");
    char choice;
    fflush(stdin);
    scanf("%c", &choice);
    //while(getchar() == '\n');
    choice = tolower(choice);

    while (choice != 'y' && choice != 'n') {

        scanf("%c", &choice);

    }
    printf("you chose %c\n", choice);
    switch (choice) {
        case 'y':
            printf("choose y");
            main();
            break;
        case 'n':
            exit(0);

    }
}

void lose(judge_t *judge) {
    judge->gameState = 0;
    judge->gameScore = 0;
    printf("\nYOULOSE\n");
    printf("Try again?\n[Y/N]\n");
    char choice;
    fflush(stdin);
    scanf("%c", &choice);
    //while(getchar() == '\n');
    choice = tolower(choice);

    while (choice != 'y' && choice != 'n') {

        scanf("%c", &choice);

    }
    printf("you chose %c", choice);
    switch (choice) {
        case 'y':
            printf("choose y");
            main();
            break;
        case 'n':
            exit(0);

    }

}

void unmark(graph_t *graph, int v) {
    int state = getState(graph, v);
    switch (state) {
        case 0:
            printf("This cell is already unmarked");
            break;
        case 2:
            printf("You can NOT unmark an open cell.\n");
            break;
        case 3:
            setState(graph, v, 0);
            break;
        case 4:
            setState(graph, v, 0);
            break;


    }
}