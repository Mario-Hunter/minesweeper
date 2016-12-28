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
bool validateRow(int row,int height){
    return row>=0 && row<=height;
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
            vertex=vertex+ceil((queryLow[i] - 'a') * width*(pow(26,rows-1-i)));//+width*26*(rows-1-i);
            //printf("\n\t\t\t\t %d %lf %d %d %d\n",queryLow[i] - 'a',pow(26,rows-1-i)*30,rows-1-i,width,vertex);
            //rows++;
        }
        
        for(int i =rows;i<length;i++){
            //printf("i=%d,length=%d\n,addedValue=%f\n",i,length,pow(10,length-i-1)*(queryLow[i] - 48));
             coloumns +=  ceil(pow(10,length-i-1)*(queryLow[i] - '0'));
        }
        coloumns--;
        printf("\n%d\n",coloumns);
        if(validateCol(coloumns,width)==false){
            printf("This cell doesn't exist\n");
            scanCell(width,height);
        }
        vertex+=coloumns;
    //printf("%d\n", vertex);
    return vertex;
    }
}

char scanQuery(void) {
    char query = "\n";
    printf("Enter Your query:\n[open,flag,question,unmark,save game,load game]\n[o,f,q,,u,s,l]\n");
    while (getchar() != '\n');
    fflush(stdin);
    scanf("%c", &query);
    resetAlarm();
    while (query == "\n" || query == " " || query == '\0') {
        scanf("%c", &query);
        resetAlarm();
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
    resetAlarm();
    printf("%c is incluseive  %d\n ",cell[1],!(cell[1]>='a'&& cell[1]<='Z'));
    while (cell[1] == '\0' || cell[2]=='\0' || !(cell[0]>='a'&& cell[0]<='Z') || !(cell[1]>='a'&& cell[1]<='Z') ) {
        printf("Enter an appropriate cell as the instructions dictates\n");
        scanf("%s", &cell);
        resetAlarm();
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
    resetAlarm();
    while (cell[1] == '\0' || cell[2]=='\0' || !(cell[0]>='A'&& cell[0]<='z') || !(cell[1]>='A'&& cell[1]<='z')) {
        printf("Enter an appropriate cell as the instructions dictates\n");
        scanf("%s", &cell);
        resetAlarm();
    }
    graph_p grid = getGraph(judge);
    int height = grid->height;
    int width = grid->width;
    int v = hash(cell, width, height);

    while (!validateCell(judge->grid->num_vertices, v)) {
        printf("This cell doesn't exist. More focus would help. The clock is ticking.\nprint the cell:\n");
        while (getchar() != '\n');
        scanf("%s", &cell);
        resetAlarm();
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
