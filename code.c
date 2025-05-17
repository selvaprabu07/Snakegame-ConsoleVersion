#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define ROW_COUNT 20
#define COL_COUNT 40
int headX, headY;
int foodX, foodY;
int tailPositionsX[100], tailPositionsY[100];
int tailSize = 0;
int moveDir = 0;
int isRunning = 1;
int totalScore = 0;
char username[50];

void startGame()
 {
    srand((unsigned int)time(NULL));
    headX = COL_COUNT / 3;
    headY = ROW_COUNT / 3;
    foodX = rand() % COL_COUNT;
    foodY = rand() % ROW_COUNT;
    totalScore = 0;
    tailSize = 0;
    moveDir = 0;
}


void drawScene()
{
    system("cls");
    for (int i = 0; i < COL_COUNT + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    for (int y = 0; y < ROW_COUNT; y++)
    {
        printf("#");
        for (int x = 0; x < COL_COUNT; x++)
        {
            if (x == headX && y == headY)
                printf("O");
            else if (x == foodX && y == foodY)
                printf("*");
            else
            {
                int onTail = 0;
                for (int i = 0; i < tailSize; i++)
                {
                    if (tailPositionsX[i] == x && tailPositionsY[i] == y)
                    {
                        printf("o");
                        onTail = 1;
                        break;
                    }
                }
                if (!onTail) printf(" ");
            }

            if (x == COL_COUNT - 1) printf("#");
        }
        printf("\n");
    }
    for (int i = 0; i < COL_COUNT + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    printf("Score: %d\n", totalScore);
    printf("Use W A S D | Quit: X\n");
}


void processKeyInput()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
            case 'a': case 'A':
                if (moveDir != 2)
                    moveDir = 1;
                    break;
            case 'd': case 'D':
                if (moveDir != 1)
                    moveDir = 2;
                    break;
            case 'w': case 'W':
                if (moveDir != 4)
                    moveDir = 3;
                    break;
            case 's': case 'S':
                if (moveDir != 3)
                    moveDir = 4;
                    break;
            case 'x': case 'X':
                isRunning = 0;
                break;
        }
    }
}


int isOccupied(int x, int y)
{
    if (x == headX && y == headY)
        return 1;
    for (int i = 0; i < tailSize; i++)
    {
        if (tailPositionsX[i] == x && tailPositionsY[i] == y)
        return 1;
    }
    return 0;
}


void updateGameState()
{

    int prevX = tailPositionsX[0];
    int prevY = tailPositionsY[0];
    int tempX, tempY;
    tailPositionsX[0] = headX;
    tailPositionsY[0] = headY;

    for (int i = 1; i < tailSize; i++)
    {
        tempX = tailPositionsX[i];
        tempY = tailPositionsY[i];
        tailPositionsX[i] = prevX;
        tailPositionsY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }


    switch (moveDir)
    {
        case 1: headX--;
                break;
        case 2: headX++;
                break;
        case 3: headY--;
                break;
        case 4: headY++;
                break;
    }


    if (headX < 0 || headX >= COL_COUNT || headY < 0 || headY >= ROW_COUNT)
        isRunning = 0;


    for (int i = 0; i < tailSize; i++)
    {
        if (tailPositionsX[i] == headX && tailPositionsY[i] == headY)
            isRunning = 0;
    }


    if (headX == foodX && headY == foodY)
    {
        totalScore += 10;
        tailSize++;


        do
        {
            foodX = rand() % COL_COUNT;
            foodY = rand() % ROW_COUNT;
        } while (isOccupied(foodX, foodY));
    }
}


void saveFinalScore()
{
    FILE *file = fopen("scores.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s: %d\n", username, totalScore);
        fclose(file);
    }
}

int main()
{
    printf("Enter your name: ");
    fgets(username, sizeof(username),stdin);
    // fgets(char *str,int n ,FILE *stream)

    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n')
        username[len - 1] = '\0';
    startGame();
    printf("Get ready! The game starts in 3 seconds...");
    Sleep(3000);

    while (isRunning)
    {
        drawScene();
        processKeyInput();
        updateGameState();
        Sleep(100);
    }

    printf("\nGame Over, %s! Final Score: %d\n", username, totalScore);
    saveFinalScore();
    printf("Thanks for playing!\n");

    return 0;
}
