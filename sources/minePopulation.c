#include <stdlib.h>
#include "graph.h"
#include <time.h>
#include <stdio.h>

bool containsMine(graph_t* graph,int vertex){
    return getMine(graph,vertex);
}
void plantMine(graph_t *graph,int vertex){
    setMine(graph,vertex);
}

void getMinePosition(graph_p graph,int startingNode){
    for(int i=0;i<graph->mines;i++){
        int pos;
        srand(time(NULL));
        do{
            
            pos = rand() % graph->num_vertices;
            
        }while(containsMine(graph,pos) || pos == startingNode);
        //printf("mine position: %d  \n",pos);
        plantMine(graph,pos);
        //printf("planted\n");
        
    }
    return;
}
