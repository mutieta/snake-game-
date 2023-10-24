#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int height = 20;
const int width = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;

enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;

bool gameOver;
int lives;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    // score should not be reset to 0
    // score = 0;
    lives--;
    nTail = 0;
}

void Draw()
{
    system("CLS");

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (i == tailY[k] && j == tailX[k])
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "Lives: " << lives << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;
            default:
                break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        lives--;
        if (lives == 0)
            gameOver = true;
        else
            Setup();
    }

    for (int i = 0; i < nTail; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            lives--;
            if (lives == 0)
                gameOver = true;
            else
                Setup();
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        // Increase the size of the snake tail
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    cout << "Game Over!" << endl;
    cout << "Your final score: " << score << endl;
    return 0;
}