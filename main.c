#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

int i, j, gameover, score;
int x, y, fruitX, fruitY, flag;
int tailX[100], tailY[100];
int tailLength;

void setup() {
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;

    // Seed the random number generator with the current time
    srand(time(0));

    // Place the fruit at a random position
    fruitX = rand() % WIDTH;
    while (fruitX == 0) {
        fruitX = rand() % WIDTH;
    }

    fruitY = rand() % HEIGHT;
    while (fruitY == 0) {
        fruitY = rand() % HEIGHT;
    }

    score = 0;
}

void draw() {
    system("cls");
    for (i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == x && j == y)
                printf("O");
            else if (i == fruitX && j == fruitY)
                printf("F");
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (i == tailX[k] && j == tailY[k]) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        int ch = _getch();

        if (ch == 0xE0) { // Arrow keys are prefixed with 0xE0 in Windows
            switch (_getch()) {
                case 72: flag = 4; break; // Up arrow key
                case 80: flag = 2; break; // Down arrow key
                case 75: flag = 1; break; // Left arrow key
                case 77: flag = 3; break; // Right arrow key
            }
        } else if (ch == 'x' || ch == 'X') {
            gameover = 1;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (flag) {
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        case 4:
            x--;
            break;
        default:
            break;
    }

    if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH) {
        gameover = 1;
    }

    for (i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = 1;
        }
    }

    if (x == fruitX && y == fruitY) {
        fruitX = rand() % WIDTH;
        while (fruitX == 0) {
            fruitX = rand() % WIDTH;
        }

        fruitY = rand() % HEIGHT;
        while (fruitY == 0) {
            fruitY = rand() % HEIGHT;
        }

        score += 10;
        tailLength++;
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(100); // to slow down the game
    }
    printf("Game Over!\n");
    printf("Final Score: %d\n", score);
    return 0;
}
