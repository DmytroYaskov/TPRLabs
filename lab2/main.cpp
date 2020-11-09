#include <stdio.h>

struct solution {
    int cost = 0,
        profit = 0,
        loss = 0;
    float percent = 0;
};

int main(){

    solution solutions[2] = {0};
    float percent[2] = {0}; 

    int best = 0, max = 0;

    float buff;

    FILE *inputFile = fopen("input.txt", "r");

    for(int i=0; i<3; i++){
        if( i != 2){
            for(int j=0; j<5; j++){
                switch (j){
                    case 0:
                        fscanf(inputFile, "%d", &solutions[i].cost);
                        break;
                    
                    case 1:
                        fscanf(inputFile, "%d", &solutions[i].profit);
                        break;
                    
                    case 2:
                        fscanf(inputFile, "%f", &solutions[i].percent);
                        break;
                    
                    case 3:
                        fscanf(inputFile, "%d", &solutions[i].loss);
                        break;
                    
                    default:
                        fscanf(inputFile, "%e", &buff);
                        break;
                }
            }
        } else {
            for(int j=0; j<3; j++){
                switch (j){
                    case 0:
                    case 2:
                        fscanf(inputFile, "%e", &percent[j == 0 ? 0 : 1]);
                        break;
                    
                    default:
                        fscanf(inputFile, "%e", &buff);
                        break;
                }
            }
        }
        
    }

    //draw tree
    printf("Tree:\n");
    printf("        (?)\n");
    printf("      /  |  \\\n");
    printf("   [-1] {M1} {M2}\n");
    printf("   /  \\\n");
    printf("{M1^} {M2^}\n\n");

    for (int  i = 0; i < 4; i++){
        
        buff = ( i < 2 ? (solutions[i].profit*5) : (solutions[i-2].profit*4) );
        if( max < buff ){
            best = i;
            max = buff;
        }
        
        switch (i){
        case 0:
        case 1:
            printf("Solution M%d:\n", 1+i);
            printf("\tCost: %4d \n", solutions[i].cost);
            printf("\tProfit: %4d | %3.0f%%\n", solutions[i].profit*5, solutions[i].percent*100);
            printf("\tLoss: %4d | %3.0f%%\n", solutions[i].loss*5, (1. - solutions[i].percent)*100);
            break;
        
        case 2:
        case 3:
            printf("Solution M%d^:\n", -1+i);
            printf("\tCost: %4d \n", solutions[i-2].cost);
            printf("\tProfit: %4d | %3.0f%%\n", solutions[i-2].profit*4, percent[i-2]*100);
            printf("\tLoss: %4d | %3.0f%%\n", solutions[i-2].loss*4, (1. - percent[i-2])*100);
            break;
        
        default:
            break;
        }
        printf("\n");
    }
    
    char buffer[3];
    sprintf(buffer, "%d%c\0", best < 2 ? best + 1 : best - 1, best > 1 ? '^' : '\0' );
    printf("Best solution is M%s\n", buffer);

    return 0;
}