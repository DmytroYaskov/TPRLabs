#include <stdio.h>

int main(){

    float weights[4] = {};
    int points[4][7] = {};
    float summ[7] = {0};
    char parameters[][10] = {
        "Acurracy",
        "Min Range",
        "Max Range",
        "Price"
    };
    int best = 0;
    float max;

    FILE *inputFile = fopen("input.txt", "r");

    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            if(j==0){
                fscanf(inputFile, "%f", &weights[i]);
            } else {
                fscanf(inputFile, "%d", &points[i][j-1]);
            }
        }
    }

    for(int i=0; i <7; i++){
        summ[i] = 0;
        for(int j=0; j<4; j++){
            summ[i] += weights[j] * points[j][i];
        }
        if(summ[i] > max){
            max = summ[i];
            best = i;
        }
    }


    printf("| № | Criteria      | Weight | A   | B   | C   | D   | E   | F   | G   |\n");

    for(int i=0; i<72; i++) printf("-");
    printf("\n");

    for(int i=0; i<4; i++){
        printf("| %d | %-13s | %6.1f |", i, parameters[i], weights[i]);
        for(int j=0; j<7; j++){
            printf(" %3d |", points[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<72; i++) printf("-");
    printf("\n");

    printf("| Summ \t\t\t     |");

    for(int j=0; j<7; j++){
        if(best == j){
            printf("[%3.1f]|", summ[j]);
        } else {
            printf(" %3.1f |", summ[j]);
        }
    }

    printf("\n\n");

    printf("Best choise is %c\n\n", 65+best);

    return 0;
}