#include "stdio.h"
#include "raylib.h"
#include "algorithm"

int main(){

    //Algorithm

    int inputNumbers[3][3] = {0};
    int valda[3] = {0};
    int maximum[3] = {0};
    int routhHurwitz[3] = {0};
    float routhHurwitzCoef = 0;
    int laplas[3] = {0};
    float laplasCoefs[3] = {0};

    FILE *inputFile = fopen("./input.txt","r");
    for (int i = 0; i < 3; i++){
        fscanf(inputFile, "%d %d %d\n", &inputNumbers[i][0], &inputNumbers[i][1], &inputNumbers[i][2]);
    }
    fscanf(inputFile, "%f\n", &routhHurwitzCoef);
    fscanf(inputFile, "%f %f %f\n", &laplasCoefs[0], &laplasCoefs[1], &laplasCoefs[2]);

    // for (int i = 0; i < 3; i++){
    //     printf("%d %d %d\n", inputNumbers[i][0], inputNumbers[i][1], inputNumbers[i][2]);
    // }

    // - Valda (min)
    for (int i = 0; i < 3; i++){
        valda[i] = *std::min_element(inputNumbers[i],inputNumbers[i]+3);
    }
    
    // - Maximum
    for (int i = 0; i < 3; i++){
        maximum[i] = *std::max_element(inputNumbers[i],inputNumbers[i]+3);
    }

    // - Routh-Hurwitz (min < solution < max)
    for (int i = 0; i < 3; i++){
        routhHurwitz[i] = routhHurwitzCoef*valda[i] + (1-routhHurwitzCoef)*maximum[i];
    }

    // - Laplas
    for (int i = 0; i < 3; i++){
        laplas[i] = 0;
        for (int j = 0; j < 3; j++){
            laplas[i] += laplasCoefs[j]*inputNumbers[i][j];
        }
    }

    //Window

    int fontSize = 16;
    int numbersFontSize = 40;

    InitWindow(800, 400, "Lab 1");

    Font comfortaFont = LoadFontEx("./Comfortaa-Regular.ttf", 32, 0, 250);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);

            DrawRectangle(100, 50, 690, 2, DARKGRAY);
            DrawRectangle(100, 10, 2, 40, DARKGRAY);
            DrawRectangle(400, 10, 2, 40, DARKGRAY);

            for (int i = 0; i < 7; i++){
                DrawRectangle(100*i+100, 50, 2, 340, DARKGRAY);
            }

            for (int i = 0; i < 3; i++){
                DrawRectangle(10, 100+(100*i), 780, 2, DARKGRAY);
            }

            // DrawTextEx(comfortaFont, "Alternative\nsolutions", (Vector2){10, 10}, fontSize, 0, RAYWHITE);
            DrawText("Alternative\nsolutions", 10, 10, fontSize, RAYWHITE);
            DrawText("Environment states", 105, 10, fontSize, RAYWHITE);
            DrawText("Criteria", 405, 10, fontSize, RAYWHITE);

            DrawText("Keep\nworking", 10, 105, fontSize, RAYWHITE);
            DrawText("Same level", 105, 55, fontSize, RAYWHITE);
            DrawText("Increased\nrivalry", 205, 55, fontSize, RAYWHITE);
            DrawText("High rivalry", 305, 55, fontSize, RAYWHITE);
            DrawText("Valda", 405, 55, fontSize, RAYWHITE);
            DrawText("Maximum", 505, 55, fontSize, RAYWHITE);
            DrawText("Routh\nHurwitz", 605, 55, fontSize, RAYWHITE);
            DrawText("Laplas", 705, 55, fontSize, RAYWHITE);

            DrawText(TextFormat("Activate\nadvertising"), 10, 205, fontSize, RAYWHITE);

            DrawText(TextFormat("Activate\nadvertising\nand reduce\npricing"), 10, 305, fontSize, RAYWHITE);

            for (int i = 0; i < 3; i++){
                DrawText(TextFormat("%02.02f", routhHurwitzCoef),
                         667, 100*i+181, numbersFontSize/3+1, GOLD);
            }

            for (int i = 0; i < 3; i++){
                DrawText(TextFormat("%02.02f %02.02f %02.02f", laplasCoefs[0], laplasCoefs[1], laplasCoefs[2]),
                         707, 100*i+181, numbersFontSize/3+1, GOLD);
            }
            
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    DrawText(TextFormat("%i", inputNumbers[i][j]), 100*j+110, 100*i+105, numbersFontSize, LIME);
                }
            }

            for (int i = 0; i < 4; i++){

                int *curCriteria;
                switch (i){
                case 0:
                    curCriteria = valda;
                    break;
                case 1:
                    curCriteria = maximum;
                    break;
                case 2:
                    curCriteria = routhHurwitz;
                    break;
                case 3:
                    curCriteria = laplas;
                    break;
                }

                for (int j = 0; j < 3; j++){
                    DrawText(TextFormat("%i", curCriteria[j]), 100*i+410, 100*j+105, numbersFontSize, LIME);
                }
            }

            // DrawText(TextFormat("Score: %08i", 1), 200, 80, 20, RED);
            // DrawText(TextFormat("іваівп: %08i", 2), 200, 100, 20, RED);

        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}