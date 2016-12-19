#include "graph.h"
#include "judge.h"

void mineNotify(graph_t *graph,int v){
    adjlist_node_p parent = graph->adjListArr[v].head;
    printf("mine = %d\n",v);     
    //displayGraph(graph);
    while(parent  != NULL){
        adjlist_node_p child =graph->adjListArr[parent->vertex].head;
        //printf("child->vertex %d\n",child->vertex);
        while(child != NULL && child->vertex != v){
            child =child->next;
            
        }
        if(child != NULL){
                child->isMine = true;
            }
            
        parent = parent->next;
    }
    return;
}

void stateNotify(graph_t *graph,int v,int state){
    adjlist_node_p parent = graph->adjListArr[v].head;
    while(parent){
        adjlist_node_p child =graph->adjListArr[parent->vertex].head;
        while(child->vertex != v){
            child =child->next;
        }
        child->state = state;
        parent = parent->next;
    }
    return;
}
/*
void loseNotify(judge_t *judge){
    setLost(judge);
}*/
void emptyNotify(graph_t *graph,judge_t *judge,int v){
    openEmpty(graph,judge,v);
}
