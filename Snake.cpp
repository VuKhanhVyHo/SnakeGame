/*
    #Made by Tichu (Vu Khanh Vy Ho)_2023
    #"Snake Game" only operated on the Mac OS, using C++
    #If you want to compile this file, you need to use Command
            gcc -o SnakeGame Snake.cpp -lncurses
*/

#include <cstdlib>
#include <ncurses.h> // input output
#include <unistd.h> // sleep function

//Global Variable
bool gameOver;
const int width = 20;
const int height = 20;
int x, y; //snake head
int fruitX, fruitY;
int score;
int level=0;

enum eDirection {STOP =0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// snake tail
int tailX[50], tailY[50];
int numTail=0;

void SetUp()
{
    //Shell Screen Init, functions from ncurses.h
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width/2; // start xpos
    y = height/2; // start ypos
    fruitX = (rand() % width)+1; 
    fruitY = (rand() % height)+1; 
    score = 0;  
}



void Draw() {
    clear();
    //Draw map, snake head, fruit, and tail
    for (int i=0; i<height+2; i++) {
        for (int j=0; j<width+2; j++) {
            if ((i==0 | i==21)|(j==0 | j==21)) {
                //Draw map
                mvprintw(i, j, "#");
            } else if (i==y && j==x) {
                //Draw snake head
                mvprintw(i, j, "O");
            } else if (i==fruitY && j==fruitX) {
                //Draw fruit
                mvprintw(i, j, "@");
            } else {   
                //Draw Tail
                for (int k=0; k<numTail; k++) {
                    if (tailX[k]==j && tailY[k]==i) {
                        mvprintw(i,j, "o");
                    }
                }
            }
        }
    }    
    //Draw Information
    mvprintw(3, 29, "------------------------------------");
    mvprintw(4, 29, "| Snake Game made by Vu Khanh Vy Ho |");
    mvprintw(5, 29, "------------------------------------");
    mvprintw(7, 29, "Use direction keys to eat fruit");
    mvprintw(9, 43, "   ^ ");
    mvprintw(10, 43, "<     >");
    mvprintw(11, 43, "   v  ");
    if (level == 1) {mvprintw(13, 29, "You are at level Nightmare");}
    else if(level == 2){mvprintw(13, 29, "You are at level Medium");}
    else {mvprintw(13, 29, "You are at level Easy");}
    mvprintw(14, 29, "** If you collide with wall or tail, Snake will die");
    mvprintw(15, 29, "** Press q if you want to quit");
    mvprintw(16, 29, "$$ Score = %d", score);
    refresh();
}

void Input() {
    // Check whether there is input, function from ncurses
    keypad(stdscr, TRUE);
    halfdelay(level); 

    switch(getch()) {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_DOWN: // definition is opposite between up and down
            dir = UP;
            break;
        case KEY_UP:
            dir = DOWN;
            break;
        case 'q':
            gameOver = true;
            break;
    }    

}

void Update() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    // add new position and other one copy
    for (int i=1; i<numTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case UP:
            y++;
            break;
        case DOWN:
            y--;
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

// if snake goes outside from the map, game will be over    
    if (x>width || x<1 || y<1 || y>height) {
        gameOver=true;
    }

//if snake bites itself, game will be over
    for (int i=0; i<numTail; i++) {
        if(tailX[i]==x && tailY[i]==y) {
            gameOver=true;
        }
        
    }

// if snake eats the fruit on the map, score will increase    
    if (x==fruitX && y==fruitY) {
        score ++;
        fruitX = (rand() % width)+1;
        fruitY = (rand() % height)+1;
        numTail++;
    }
}


int main(void) {
    SetUp();
    mvprintw(0,0,
    "Choose the difficult level, E for Easy, M for Medium and N for Nightmare");
    switch(getch()) {
        case 'E':
            level=3;
            break;
        case 'M':
            level=2;
            break;
        case 'N':
            level=1;
    }
    while(!gameOver) {
        Draw();
        Input();
        Update();

    }
    clear();
    getch(); 
    endwin();
    return 0;
}
