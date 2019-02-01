#include "battleship.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

void ComputerPlayer::turn(Player &target)
{
  enum STATE{RAND, CHECK, FOLLOW};
  
    static STATE state = RAND;
  
    static int lastx = 0;
    static int lasty = 0;
    static int hitstreak = 0;
    
    int x,y;
    
    static int direction = -1;
    
    do
    {
        // AI code goes here
      switch (state)
        {
        case RAND:
            x = rand() % BOARDX; // Pick a random x
            y = rand() % BOARDY; // Pick a random y
            if (target.map[x][y]==SHIP)
            {
                lastx = x;
                lasty = y;
                state = CHECK;
            }
          break;
          
        case CHECK:
            direction = rand() % 4;
                switch (direction)
                {
                    case 0: // south
                        x = lastx;
                        y = lasty + 1;
                        break;
                    case 1: //east
                        x = lastx + 1;
                        y = lasty;
                        break;
                    case 2: // north
                        x = lastx;
                        y = lasty - 1;
                        break;
                    case 3: // west
                        x = lastx - 1;
                        y = lasty;
                        break;
                }
             if (target.map[x][y]==SHIP)
               state = FOLLOW;
          break;
          
        case FOLLOW:
           switch (direction)
                {
                    case 0: // south
                        x = lastx;
                        y = ++lasty;
                        break;
                    case 1: //east
                        x = ++lastx;
                        y = lasty;
                        break;
                    case 2: // north
                        x = lastx;
                        y = --lasty;
                        break;
                    case 3: // west
                        x = --lastx;
                        y = lasty;
                        break;
                }
                // This is so we don't keep going if the next spot in the grid is already marked
                if (target.map[x][y]==MISS || target.map[x][y]==HIT){
                    state = RAND;
                    continue;
                }
           if (target.map[x][y]==BLANK)
             state = RAND;
          break;
        }
        
        if (x < 0 || x >= BOARDX || y < 0 || y >= BOARDY)
            continue;
        
        // End AI code
        
        // Message the user with the results of your shot
        if (target.map[x][y] == HIT || target.map[x][y] == MISS) {continue;}
        else if (target.map[x][y] == SHIP)
        {
            cout<<"\nThe computer hit your battleship! ("<<x+1<<','<<y+1<<")\n";
            target.map[x][y] = HIT;
            hit_map[x][y] = HIT;
            break;
        }
        else if (target.map[x][y] == BLANK)
        {
            cout<<"\nThe computer missed! ("<<x+1<<','<<y+1<<")\n";
            target.map[x][y] = MISS;
            hit_map[x][y] = MISS;
            break;
        }
        else{
            cout<<"\nSomething went very wrong with the AI targeting system.\n";
        }
    }while (target.map[x][y] != BLANK);
}
