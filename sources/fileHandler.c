#include <stdio.h>
#include "judge.h"
#include "graph.h"
#include <string.h>
#include "mergeSort.h"
void showLeaderBoard(void) {
    FILE *leaderBoard = fopen("./saved/tmp/leaderboard.dat", "r");
    printf("\nMinesWeeper leaderboard\n------------------------\n");
    int n;
    fscanf(leaderBoard, "%d", &n);
    player players[n];
    for (int i = 0; i < n; i++) {
        fscanf(leaderBoard, "%s", &players[i].name);
        fscanf(leaderBoard, "%d", &players[i].score);
        
    }
    fclose(leaderBoard);
    mergeSort(players,n);
    for (int i = n-1; i >=0; i--) {
        printf(" %d | player: %20s  score: %10d\n", n-i,players[i].name, players[i].score);
        
    }
    
    main();
}
void modifyIndex(char *user) {
    FILE *index = fopen("./saved/tmp/index.dat", "r+");
    int users;
    //fscanf(index,"%d",users);
    //fprintf(index,"%d",users++);
    //fclose(index);
    //FILE *indexList = fopen("./saved/tmp/index.dat","r+");

    fscanf(index, "%d", &users);
    fseek(index, 0, SEEK_SET);
    users++;
    fprintf(index, "%d", users);
    fseek(index, 0, SEEK_END);
    fprintf(index, "\n%s", user);
    fclose(index);
}

char * getUser(void) {
    char user[10];
    printf("Enter the user name:\n");

    FILE * users = fopen("./saved/tmp/index.dat", "r");
    int n;
    fscanf(users, "%d", &n);
    if (n == 0) {
        return "-1";
    }
    printf("[");
    for (int i = 0; i < n; i++) {
        fscanf(users, "%s", &user);
        n - i != 1 ? printf("%s,", user) : printf("%s", user);
    }
    printf("]\n");
    fclose(users);
    scanf("%s", &user);
    users = fopen("./saved/tmp/index.dat", "r");
    char indexedUser[10];
    for (int i = 0; i <= n; i++) {
        fscanf(users, "%s", &indexedUser);
        if (strcmp(indexedUser, user) == 0) {
            fclose(users);
            return user;
        }
    }
    printf("this user doesn't have any saved games. Type another name");
    return getUser();

}

void saveFile(judge_t *judge) {
    printf("Saving..\n");
    FILE *game;
    char *user = judge->user;
    char path [100] = "./saved/tmp/";
    strcat(path, user);
    strcat(path, ".dat");
    game = fopen(path, "w+");

    fprintf(game, "%d %d %d\n", judge->grid->num_vertices, judge->grid->width, judge->grid->height);
    fprintf(game, "%d %ld\n", judge->gameTime, judge->gameScore);
    for (int i = 0; i < judge->grid->num_vertices; i++) {
        adjlist_node_p node = judge->grid->adjListArr[i].head;
        int members = judge->grid->adjListArr[i].num_members;
        fprintf(game, "%d ", members);
        while (node) {
            fprintf(game, "%d ", node->vertex);
            node = node->next;
        }
        fprintf(game, "\n");
    }
    for (int i = 0; i < judge->grid->num_vertices; i++) {
        adjlist_node_p node = judge->grid->adjListArr[i].node;

        fprintf(game, "%d ", node->state);

        fprintf(game, "\n");
    }
    fprintf(game, "%d\n", judge->grid->mines);
    int printedMines = 0;
    for (int i = 0; printedMines != judge->grid->mines; i++) {
        if (getMine(judge->grid, i)) {
            fprintf(game, "%d ", i);
            printedMines++;
        }
    }
    fprintf(game, "\n%d", judge->moves);
    fprintf(game, "\n%d", judge->grid->openedCells);
    fprintf(game, "\n%d", judge->grid->flags);
    fclose(game);
    modifyIndex(judge->user);
    main();
}

judge_p openFile(void) {
    char user[10];
    strcpy(user, getUser());
    if(strcmp(user,"-1")==0){
        printf("\nNo Saved Files Found.\nLet's Start Fresh.\n");
        main();
    }
    printf("%s", user);
    judge_p judge = createJudge();
    strcpy(judge->user, user);
    
    char path [100] = "./saved/tmp/";
    strcat(path, user);
    strcat(path, ".dat");
    FILE *game = fopen(path, "r");
    if (game == NULL) {
        printf("Failed to open file");
        return;
    }
    int numVertices, height, width, gameTime,  mines;
    long int gameScore;
    fscanf(game, "%d %d %d", &numVertices, &width, &height);
    //printf("%d %d %d",numVertices,width,height);
    fscanf(game, "%d %ld\n", &judge->gameTime, &judge->gameScore);


    judgeCreateGraph(judge, width, height, DIRECTED);

    for (int i = 0; i < numVertices; i++) {
        int members;
        fscanf(game, "%d", &members);

        for (int j = 0; j < members; j++) {
            int dest;
            fscanf(game, "%d", &dest);
            addEdge(judge->grid, i, dest);
        }
    }
    for (int i = 0; i < judge->grid->num_vertices; i++) {
        adjlist_node_p node = judge->grid->adjListArr[i].node;
        int state;
        fscanf(game, "%d ", &state);
        setState(judge->grid, i, state);
    }
    fscanf(game, "%d\n", &judge->grid->mines);


    for (int i = 0; i < judge->grid->mines; i++) {
        int cell;
        fscanf(game, "%d", &cell);
        setMine(judge->grid, cell);
    }

    fscanf(game, "%d", &judge->moves);
    fscanf(game, "%d", &judge->grid->openedCells);
    fscanf(game, "%d", &judge->grid->flags);
    fclose(game);
    return judge;
}