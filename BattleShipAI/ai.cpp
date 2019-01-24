#include "battleship.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

void ComputerPlayer::turn(Player &target)
{
    static int lastx = 0;
    static int lasty = 0;
    static int hitstreak = 0;
    static bool prevHit = false;

    int x,y;
    
    do
    {
        // AI code goes here
        if (prevHit == false)
        {
        x = rand() % BOARDX; // Pick a random x
        y = rand() % BOARDY; // Pick a random y
        }

        else
        {
            int direction = rand() % 4;
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
                    y + lasty - 1;
                    break;
                case 3: // west
                    x = lastx - 1;
                    y = lasty;
                    break;
            }
            if (x < 0 || x >= BOARDX || y < 0 || y >= BOARDY)
                continue;
            
        }
        if (target.map[x][y]==SHIP)
        {
            lastx = x;
            lasty = y;
            prevHit = true;
        }        
        // End AI code
        // Message the user with the results of your shot
        if (target.map[x][y] == HIT || target.map[x][y] == MISS) {continue;}
        if (target.map[x][y] == SHIP)
        {
            cout<<"\nThe computer hit your battleship!\n";
            target.map[x][y] = HIT;
            hit_map[x][y] = HIT;
            break;
        }
        if (target.map[x][y] == BLANK)
        {
            cout<<"\nThe computer missed!\n";
            target.map[x][y] = MISS;
            hit_map[x][y] = MISS;
            break;
        }
    }while (target.map[x][y] != BLANK);
}
