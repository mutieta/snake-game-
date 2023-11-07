#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 20;

int x, y, fruitX, fruitY, scores;

int tailX[100], tailY[100], nTail;

enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;

int lives; // Number of lives

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    scores = 0;
    lives = 3; // Set initial lives to 3
    nTail = 0;
}

void Draw()
{
    system("CLS");

    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                cout << "#";
            }
            else if (i == y && j == x)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Set color to yellow
                cout << "O";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset color
            }
            else if (i == fruitY && j == fruitX)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Set color to red
                cout << "F";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset color
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (i == tailY[k] && j == tailX[k])
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Set color to yellow
                        cout << "o";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Reset color
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << endl;
    cout << "Scores: " << scores << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
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

    tailX[0] = x;
    tailY[0] = y;

    int prev2X, prev2Y;

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
        lives--; // Decrement lives when the player hits the boundary
        if (lives == 0)
            gameOver = true;
        else
            Setup();
    }

    for (int i = 0; i < nTail; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            lives--; // Decrement lives when the player hits its own tail
            if (lives == 0)
                gameOver = true;
            else
                Setup();
        }
    }

    if (x == fruitX && y == fruitY)
    {
        scores += 10;
        fruitX = rand() % width;
fruitY = rand() % height;
        nTail++;
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
        Sleep(40);
    }

    cout << "Game Over!" << endl;
    cout << "Your final score: " << scores << endl;
    return 0;
}