#include "stdio.h"

struct vote{
    int count = 0;
    char priority[3] = "\0";
};


int main(){

    int votesCount = 5;
    enum candidates{A,B,C};
    struct vote votes[votesCount];

    printf(" - Input:\n");

    FILE *inputFile = fopen("input.txt", "r");
    for(int i=0; i<votesCount; i++){
        fscanf(inputFile,"%d %s\n", &votes[i].count, votes[i].priority);
        printf("%d - %s\n", votes[i].count, votes[i].priority);
    }
    fclose(inputFile);

    //Borda

    printf("\n - Borda:\n");

    int points[3] = {0};

    for(int i=0; i<votesCount; i++){
        for(int j=0; j<3; j++){
            switch (votes[i].priority[j]){
                case 'A':
                    points[0] += votes[i].count * (3-j);
                    break;

                case 'B':
                    points[1] += votes[i].count * (3-j);
                    break;

                case 'C':
                    points[2] += votes[i].count * (3-j);
                    break;
                
                default:
                    break;
            }
        }
    }

    char winner = 0;

    printf("Results:\n");
    for(int i=0; i<3; i++){
        printf("%d\n",points[i]);
        winner = points[i] > points[winner] ? i : winner;
    }

    printf("\n%c - Winner\n", winner+65);

    //Kondorse 

    printf("\n - Kondorse:\n");

    int pointsMatrix[3][3] = {0};

    for(int v=0; v<votesCount; v++){
        for(int i=0; i<2; i++){
            for(int j=i+1; j<3; j++){
                pointsMatrix[votes[v].priority[i]-65][votes[v].priority[j]-65] += votes[v].count;
            }
        }

    }

    printf("Results:\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ",pointsMatrix[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<3; i++){
        for(int k=0; k<3; k++){
            if(i==k) continue;
            if(pointsMatrix[i][k] > pointsMatrix[k][i]){
                winner = 65+i;
            } else {
                winner = '\0';
                break;
            }
        }
        if(winner != '\0') break;
    }

    printf("\n%c - Winner\n\n", winner);

}
