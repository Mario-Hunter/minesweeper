#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include "graph.h"
#include "judge.h"
#include "minePopulation.h"
#include <stdbool.h>
#include <math.h>


/*
int hash (char query[],int width,int height){
    char queryLow[100];
    char row[100];
    int length=0;
    int coloumn;
    for (int i = 0; query[i]; i++) {
        queryLow[i] = tolower(query[i]);
        length++;
    }
    if (queryLow[0]>= 'a' && queryLow[0]<='z'){
        for(int i=0;query[i]>= 'a' && query[i]<='z';i++){
            row[i]=query[i];
        }
        for(int i=length-1;query[i]>= '1' && query[i]<='9';i++){
            coloumn
        }
    }
}

*/

bool validateCol(int col,int width){
    return col>=0 && col<=width;
}
int hash(char query[], int width, int height) {

    char queryLow[100];
    int rows=0;
    int coloumns=0;
    int length=0;
    int vertex=0;
    for (int i = 0; query[i]; i++) {
        queryLow[i] = tolower(query[i]);
        length++;
        if (queryLow[i]>= 'a' && queryLow[i]<='z'){
            rows++;
        }
    }
    //printf("length is %d\n",length);
    if (queryLow[0]>= 'a' && queryLow[0]<='z'){
        for(int i=0;queryLow[i]>= 'a' && queryLow[i]<='z';i++){
            vertex+=(queryLow[i] - 97) * width*pow(26,rows-1-i)+width*26*(rows-1-i);
            //printf("query of i is  vertex is %d \n",vertex);
            //rows++;
        }
        //printf("%d\n", vertex);
        for(int i =rows;i<length;i++){
            //printf("i=%d,length=%d\n,addedValue=%f\n",i,length,pow(10,length-i-1)*(queryLow[i] - 48));
             coloumns +=  pow(10,length-i-1)*(queryLow[i] - 48);
        }
        if(validateCol(coloumns,width)==false){
            printf("This cell doesn't exist\n");
            scanCell(width,height);
        }
        vertex+=coloumns-1;
    //printf("%d\n", vertex);
    return vertex;
    }
}

char scanQuery(void) {
    char query = "\n";
    printf("Enter Your query:\n[open,flag,question,unmark,save game,load game]\n[o,f,q,,u,s,l]\n");
    while (getchar() != '\n');
    scanf("%c", &query);
    while (query == "\n" || query == " " || query == '\0') {
        scanf("%c", &query);
    }
    //printf("the query scanned %c\n", query);

    char queries[] = {'o', 'f', 'q','u', 's', 'l'};
    int queriesNumber = 5;
    for (int i = 0; i < queriesNumber; i++) {
        if (query == queries[i]) {
            return query;
        }
    }
    if (query != '\n') {
        printf("This query doesn't exist\n");
    }
    return scanQuery();
}

bool validateCell(int n, int v) {

    if (v >= n && v >= 0) {

        return false;
    }
    return true;
}

int scanCell(int width,int height){
    char cell[10];
    printf("print the cell:\n");
    while (getchar() != '\n');
    scanf("%s", &cell);
    while (cell[1] == '\0') {
        printf("Enter an appropriate cell as the instructions dictates\n");
        scanf("%s", &cell);
    }
    return hash(cell, width, height);
}

void takeInput(judge_t *judge) {
    
    char query;
    char cell[10];
    query = scanQuery();
    if(query == 's' || query == 'l'){
        goto action;
    }
    printf("print the cell:\n");
    while (getchar() != '\n');
    scanf("%s", &cell);
    while (cell[1] == '\0') {
        printf("Enter an appropriate cell as the instructions dictates\n");
        scanf("%s", &cell);
    }
    graph_p grid = getGraph(judge);
    int height = grid->height;
    int width = grid->width;
    int v = hash(cell, width, height);

    while (!validateCell(judge->grid->num_vertices, v)) {
        printf("This cell doesn't exist. More focus would help. The clock is ticking.\nprint the cell:\n");
        while (getchar() != '\n');
        scanf("%s", &cell);
        v = hash(cell, width, height);
    }

    if (getGraph(judge)->startingNode == -1) {
        getGraph(judge)->startingNode = v;
        getMinePosition(getGraph(judge), getGraph(judge)->startingNode);
    }
    judge->moves++;
    //printf("judge incremented");
action:
    switch (query) {
        case 'o':
            printf("\nOpening..\n");
            openCell(judge, grid, v);
            checkWin(judge);
            break;
        case 'f':
            flagCell(grid, v);
            checkWin(judge);
            break;
        case 'q':
            questionCell(grid, v);
            break;
        case 'u':
            unmark(grid,v);
            break;
        case 's':
            saveFile(judge);
            break;
        case 'l':
            openFile(judge);
            break;
    }

    return;

}
