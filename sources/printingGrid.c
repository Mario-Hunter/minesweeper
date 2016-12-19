#include <stdio.h>

#include "graph.h"
#include "judge.h"

void printGrid(judge_p *judge){
    printf("\n ");
    for(int j=1;j<=getGraph(judge)->width;j++){
        printf("|%2d",j);
    }
    printf("\n");
    for(int j=1;j<=getGraph(judge)->width+1;j++){
        printf("--|");
    }
    printf("\n");
    for(int i=0;i<getGraph(judge)->height;i++){
        printf("%2c",(char)i+97);
        for(int j=0;j<getGraph(judge)->width;j++){
            int v =i*getGraph(judge)->width+j;
            int num;
            switch (getState(getGraph(judge),v)){
                case 0:
                    printf("| X");
                    break;
                case 1 :
                    
                        printf("| *");
                        
                        break;
                case 2:
                    num= getAdjacentMine(getGraph(judge),v);
                    if (num == 0){
                        printf("|  ");
                    }else{  
                
                        printf("|%2d",num);
                    }
                        break;
                case 3:
                    printf("| F");
                    break;
                case 4:
                    printf("| ?");
                    break;
                    
                    
            }
        }
        printf("\n");
        for(int j=1;j<=getGraph(judge)->width+1;j++){
            printf("--|");
        }
        printf("\n");
    }
}
