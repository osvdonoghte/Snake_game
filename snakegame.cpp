#include "clui.h"
#include <iostream>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77

bool gameover;

const int HEIGHT = 30;
const int WIDTH = 50;
int tail_length1 = 4, tail_length2 = 4;
int tailX1[105];
int tailY1[105];
int tailX2[105];
int tailY2[105];
string Firstplayer;
string Secondplayer;
const int snakesize = 4;
int bombX, bombY;
int fruitX, fruitY, x1, x2, y1, y2;
int score1 = 0, score2 = 0;
int choice;
string usernames[100];
int scores[100];
int counter;

struct position
{
    int x, y;
};

position snake1[snakesize];
position snake2[snakesize];

enum directions
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

directions movement1, movement2;


void setup()
{
    gameover = false;
    movement1 = UP;
    movement2 = UP;
    fruitX = rand() % (((HEIGHT * WIDTH) / 50)) + 2;
    fruitY = rand() % (((HEIGHT * WIDTH) / 50)) + 3;

    for (int i = 1; i < tail_length1; i++) {
    tailX1[i] = x1;
    tailY1[i] = y1 - i;
    }

    for (int i = 1; i < tail_length2; i++) {
    tailX2[i] = x2;
    tailY2[i] = y2 - i;
    }

    x1 = WIDTH / 2 + 5;
    y2 = HEIGHT / 2 + 10;
    x2 = WIDTH / 2 + 10;
    y1 = HEIGHT / 2 + 5;

    bombX = rand() % (((HEIGHT * WIDTH) / 50)) + 2;
    bombY = rand() % (((HEIGHT * WIDTH) / 50)) + 3;
}

void draw()
{

    system("clear");
    // clear_screen();
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            if (i == WIDTH - 1 || j == HEIGHT - 1 || i == 0 || j == 0)
            {
                cout << "#";
            }
            else if (i == x1 && j == y1)
            {
                cout << "o";
            }
            else if (i == x2 && j == y2)
            {
                cout << "0";
            }
            else if (i == bombX && j == bombY)
            {
                cout << "B";
            }
            else if (i == fruitX && j == fruitY)
            {
                // edited
                /*if (fruitX == WIDTH - 1 || fruitY == HEIGHT - 1 || fruitX == 0 || fruitY == 0)
                    break;
                else*/
                    cout << "*";
            }
            else
            {
                bool working = false;
                for (int k = 0; k < tail_length1; k++)
                {
                    if (tailY1[k] == j && tailX1[k] == i)
                    {
                        cout << "o";
                        working = true;
                    }
                }
                for (int k = 0; k < tail_length2; k++)
                {
                    if (tailY2[k] == j && tailX2[k] == i)
                    {
                        cout << "O";
                        working = true;
                    }
                }

                if (!working)
                {
                    cout << " ";
                }
            }
        }

        cout << endl;
    }
    cout << Firstplayer << " = " << score1 << endl;
    cout << Secondplayer << " = " << score2 << endl;
}


void choiceMode()
{
    cout << "Choose your mode by pressing the number:)" << endl;
    cout << "1)slow" << endl;
    cout << "2)medium" << endl;
    cout << "3)fast" << endl;
}

int SpeedChoice()
{
    choice = getch();
    switch (choice)
    {
    case '1':
        return 150000;
        break;
    case '2':
        return 55000;
        break;
    case '3':
        return 3000;
        break;
    default:
        return 150000;
    }
}


void listUpdate(const string& name, int score) {
    int userIndex = -1;

    for (int i = 0; i < counter; ++i) {
        if (usernames[i] == name) {
            userIndex = i;
            break;
        }
    }

    if (userIndex != -1) {
        scores[userIndex] += score;
    } 
    else {
            usernames[counter] = name;
            scores[counter] = score;
            counter++; 
    }
}



void sort() // edited
{
    for (int i = 0; i < counter - 1; ++i)
    {
        for (int j = 0; j < counter - i - 1; ++j)
        {
            if (scores[j] < scores[j + 1])
            {
                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;

                string tempUsername = usernames[j];
                usernames[j] = usernames[j + 1];
                usernames[j + 1] = tempUsername;
            }
        }
    }
}

void displayLeaderboard()
{
    sort();
    cout << "Leaderboard:\n";
    for (int i = 0; i < counter; ++i)
    {
        cout << i + 1 << ". " << usernames[i] << " - " << scores[i] << endl;
    }
}

void PlayersName(string &player1, string &player2) // edited
{
    cout << "First player, enter your name: ";
    getline(cin, player1);
    cout << "Second player, enter your name: ";
    getline(cin, player2);
}

void logic()
{
    // edited

    int prevX1 = x1;
int prevY1 = y1;
int tempX, tempY;
for (int i = 0; i < tail_length1; i++) {
    tempX = tailX1[i];
    tempY = tailY1[i];
    tailX1[i] = prevX1;
    tailY1[i] = prevY1;
    prevX1 = tempX;
    prevY1 = tempY;
}


int prevX2 = x2;
int prevY2 = y2;
for (int i = 0; i < tail_length2; i++) {
    tempX = tailX2[i];
    tempY = tailY2[i];
    tailX2[i] = prevX2;
    tailY2[i] = prevY2;
    prevX2 = tempX;
    prevY2 = tempY;
}




    switch (movement1)
    {
    case LEFT:
        x1--;
        break;
    case UP:
        y1--;
        break;
    case RIGHT:
        x1++;
        break;
    case DOWN:
        y1++;
        break;
    default:
        break;
    }


    for (int i = 0; i < tail_length1; i++)
    {
        int tempX = tailX1[i];
        int tempY = tailY1[i];
        tailX1[i] = prevX1;
        tailY1[i] = prevY1;
        prevX1 = tempX;
        prevY1 = tempY;
    }


    switch (movement2)
    {
    case LEFT:
        x2--;
        break;
    case UP:
        y2--;
        break;
    case RIGHT:
        x2++;
        break;
    case DOWN:
        y2++;
        break;
    default:
        break;
    }


    for (int i = 0; i < tail_length2; i++)
    {
        int tempX = tailX2[i];
        int tempY = tailY2[i];
        tailX2[i] = prevX2;
        tailY2[i] = prevY2;
        prevX2 = tempX;
        prevY2 = tempY;
    }
    if (x1 < 0 || y1 < 0 || x1 > WIDTH || y1 > HEIGHT)
    {
        gameover = true;
    }

    if (x2 < 0 || y2 < 0 || x2 > WIDTH || y2 > HEIGHT)
    {
        gameover = true;
    }

    if (x1 == bombX && y1 == bombY)
    {
        gameover = true;
    }

    if (x2 == bombX && y2 == bombY)
    {
        gameover = true;
    }

    for (int i = 2; i < tail_length1; i++)
    {
        if (x1 == tailX1[i] && y1 == tailY1[i]) // edited
            gameover = true;
    }

    for (int i = 2; i < tail_length2; i++)
    {
        if (x2 == tailX2[i] && y2 == tailY2[i]) // edited
            gameover = true;
    }

    if (x1 == bombX && y1 == bombY)
    {
        gameover = true;
    }

    if (x1 == fruitX && y1 == fruitY) // edited
    {
    score1 += 10;
    tail_length1++;
    fruitX = rand() % (((HEIGHT * WIDTH) / 50)) + 2;
    fruitY = rand() % (((HEIGHT * WIDTH) / 50)) + 3;
    }

    if (x2 == fruitX && y2 == fruitY) // edited
    {
    score2 += 10;
    tail_length2++;
    fruitX = rand() % (((HEIGHT * WIDTH) / 50)) + 2;
    fruitY = rand() % (((HEIGHT * WIDTH) / 50)) + 3;
    }


    if (gameover)
    {
        listUpdate(Firstplayer, score1);
        listUpdate(Secondplayer, score2);
        displayLeaderboard();
    }
}


void input() // edited
 {
    if (is_keyboard_hit()) {
        char ch = getch();

        if(ch != '\033') {
            switch(ch) {
            case 'w':
                    movement2 = UP;
                break;
            case 'a':
                    movement2 = LEFT;
                break;
            case 'd':
                    movement2 = RIGHT;
                break;
            case 's':
                    movement2 = DOWN;
                break;
            }
        }
        else {
            getch();
            ch = getch();
            switch(ch) {
            case 'A':
                    movement1 = UP;
                break;
            case 'D':
                    movement1 = LEFT;
                break;
            case 'C':
                    movement1 = RIGHT;
                break;
            case 'B':
                    movement1 = DOWN;
                break;
            }
            
        }
    }
}




void result()
{

    if (score1 > score2)
    {
        cout << Firstplayer << "'s score's  = " << score1 << " fisrtplayer won the game" << endl;
        cout << Secondplayer << "'s score's = " << score2 << " lost the game" << endl;
    }
    else if (score1 < score2)
    {
        cout << Secondplayer << "'s score's = " << score2 << " won the game" << endl;
        cout << Firstplayer << "'s score's  = " << score1 << " lost the game" << endl;
    }
    else
    {
        cout << Firstplayer << "'s score's = " << score1 << endl;
        cout << Secondplayer << "'s score's = " << score2 << endl;
        cout << "Draw , no body one the game" << endl;
    }
}

int main() {
    init_clui();

    PlayersName(Firstplayer, Secondplayer);

    choiceMode();
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3) {
            cout << "Invalid input. Please enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    }


    int speed = SpeedChoice();

    while(true) {
        setup();
        while (!gameover) {
            draw();
            input();
            logic();

             usleep(speed);
        }
        system("clear");
         result();
        cout << "Do you want to play again? (y/n)" << endl;
        char ch;
        cin >> ch;
        if(ch == 'n') {
            break;
        }
    }

    quit();
    return 0;
}