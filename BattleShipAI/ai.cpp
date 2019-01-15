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
    
    int x,y;
    
    do
    {
        // AI code goes here
        x = rand() % BOARDX; // Pick a random x
        y = rand() % BOARDY; // Pick a random y
        
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
