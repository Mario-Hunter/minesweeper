#include <stdio.h>
#include "graph.h"
#include "judge.h"

void printGrid(judge_t *judge) {
    system("cls");
    printf("\n   ");
    for (int j = 1; j <= getGraph(judge)->width; j++) {
        printf("|%3d", j);
    }
    printf("\n");
    for (int j = 1; j <= getGraph(judge)->width + 1; j++) {
        printf("---|");
    }
    printf("\n");
    for (int i = 0; i < getGraph(judge)->height; i++) {
        printf("%2c%c", (char) (i / 26) + 'a', (char) (i + 97) - 26 * (i / 26));
        for (int j = 0; j < getGraph(judge)->width; j++) {
            int v = i * getGraph(judge)->width + j;
            int num;
            switch (judge->gameState) {
                case 1:
                    switch (getState(getGraph(judge), v)) {
                        case 0:

                            printf("|  X");
                            break;

                        case 2:
                            num = getAdjacentMine(getGraph(judge), v);
                            if (num == 0) {
                                printf("|   ");
                            } else {
                                printf("|%3d", num);
                            }
                            break;
                        case 3:

                            printf("|  F");
                            break;
                        case 4:
                            printf("|  ?");
                            break;
                    }
                    break;
                case 2:
                    switch (getState(getGraph(judge), v)) {
                        case 0:

                            if (getGraph(judge)->adjListArr[v].node->isMine == 1) {
                                printf("|  F");
                            }

                            break;
                        case 1:
                            printf("|  !");
                            break;
                        case 2:
                            num = getAdjacentMine(getGraph(judge), v);
                            if (num == 0) {
                                printf("|   ");
                            } else {
                                printf("|%3d", num);
                            }
                            break;
                        case 3:

                            printf("|  F");
                            break;
                        case 4:
                            printf("|  F");
                            break;


                    }
                    break;
                case 3:
                    switch (getState(getGraph(judge), v)) {
                        case 0:

                            if (getGraph(judge)->adjListArr[v].node->isMine == 1) {
                                printf("|  M");
                                break;
                            }

                            num = getAdjacentMine(getGraph(judge), v);
                            if (num == 0) {
                                printf("|   ");
                            } else {
                                printf("|%3d", num);
                            }
                            break;
                        case 1:
                            printf("|  !");
                            break;
                        case 2:
                            num = getAdjacentMine(getGraph(judge), v);
                            if (num == 0) {
                                printf("|   ");
                            } else {
                                printf("|%3d", num);
                            }
                            break;
                        case 3:

                            if (judge->grid->adjListArr[v].node->isMine == 1) {
                                printf("|  *");
                            } else {
                                printf("|  -");
                            }
                            break;



                        case 4:
                            if (judge->grid->adjListArr[v].node->isMine == 1) {
                                printf("|  *");
                            } else {
                                printf("|  -");
                            }
                            break;


                    }
                    break;

            }
            
        }
        printf("\n");
        for (int j = 1; j <= getGraph(judge)->width + 1; j++) {
            printf("---|");
        }
        printf("\n");
    }
}
