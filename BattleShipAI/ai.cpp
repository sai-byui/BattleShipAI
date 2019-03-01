#include "battleship.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;


void SliceAndDice::turn(Player &target){
    int x, y;
    static bool lastHit = false;
    
    
    do{
        // Code
        if (hitlist.size() > 0){
            x = hitlist.front().x;
            y = hitlist.front().y;
            hitlist.pop();
            cout<<"Popped an Point("<<x<<", "<<y<<")\n";
        }
        else{
            x = rand() % BOARDX;
            y = rand() % BOARDY;
        }
        
        // Check for valid
        if (x < 0 || x >= BOARDX || y < 0 || y >= BOARDY)
            continue;
        if (target.map[x][y] == HIT || target.map[x][y] == MISS) {continue;}
        else if (target.map[x][y] == SHIP)
        {
            cout<<"\nThe computer hit your battleship! ("<<x<<','<<y<<")\n";
            target.map[x][y] = HIT;
            hit_map[x][y] = HIT;
            lastHit = true;
            runLoop = false;
        }
        else if (target.map[x][y] == BLANK)
        {
            cout<<"\nThe computer missed! ("<<x<<','<<y<<")\n";
            target.map[x][y] = MISS;
            hit_map[x][y] = MISS;
            lastHit = false;
            runLoop = false;
        }
        else{
            cout<<"\nSomething went very wrong with the AI targeting system.\n";
        }
    }while(runLoop);
}


void ComputerPlayer::turn(Player &target)
{
  //enum STATE{RAND, CHECK, FOLLOW, FOLLOW2};
  
    //static STATE state = RAND;
    static bool lastHit = false;
    runLoop = true;
  
    /*static int lastx = 0;
    static int lasty = 0;
	static Point firstHit;*/

    
    int x,y;
    
    static int direction = -1;
    
    // Check if we need to switch state
    switch (state) {
        case RAND:
            if (lastHit){
                state = CHECK;
                firstHit.set(lastx, lasty);
            }
            break;
        case CHECK:
            if (lastHit)
                state = FOLLOW;
            break;
        case FOLLOW:
            if (!lastHit){
                state = FOLLOW2;
                direction = (direction + 2) % 4;
                lastx = firstHit.x;
                lasty = firstHit.y;
            }
            break;
        case FOLLOW2:
            if (!lastHit)
                state = RAND;
            break;
        default:
            break;
    }
    
    
    int count = 0;
    do
    {
        count++;
        if (count > 10000){
            cout<<"We've looped over 10k times...\n";
            cout<<"Current state: "<<(int)state<<endl;
            cout<<"Last X: "<<lastx<<endl;
            cout<<"Last Y: "<<lasty<<endl;
            break;
        }
        // AI code goes here
        
        
        // Now execute behavior based on the state.
      switch (state)
        {
        case RAND:
            x = rand() % BOARDX; // Pick a random x
            y = rand() % BOARDY; // Pick a random y
            lastx = x;
            lasty = y;
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
                /*if (target.map[x][y]==MISS || target.map[x][y]==HIT){
                    state = FOLLOW2;
                    continue;
                }*/
                /*if (target.map[x][y]==BLANK){
                    direction = (direction + 2) % 4;
                    state = FOLLOW2;
                }*/
                // In case we target off the edge of the board
                if (x < 0 || x >= BOARDX || y < 0 || y >= BOARDY)
                {
                    state = FOLLOW2;
                    direction = (direction + 2) % 4;
                    lastx = firstHit.x;
                    lasty = firstHit.y;
                    continue;
                }
          break;

		case FOLLOW2:
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
            // In case we target off the edge of the board
            if (x < 0 || x >= BOARDX || y < 0 || y >= BOARDY)
            {
                state = RAND;
                continue;
            }
			// If we've already hit there before.
			if (target.map[x][y]==MISS || target.map[x][y]==HIT){
                    state = RAND;
                    continue;
                }

			/*if (target.map[x][y] == BLANK)
				state = RAND;*/
			break;
        }
        
        if (x < 0 || x >= BOARDX || y < 0 || y >= BOARDY)
            continue;
        
        // End AI code
        
        // Message the user with the results of your shot
        //cout<<"Testing the shot...\n";
        if (target.map[x][y] == HIT || target.map[x][y] == MISS) {continue;}
        else if (target.map[x][y] == SHIP)
        {
            cout<<"\nThe computer hit your battleship! ("<<x<<','<<y<<")\n";
            target.map[x][y] = HIT;
            hit_map[x][y] = HIT;
            lastHit = true;
            runLoop = false;
        }
        else if (target.map[x][y] == BLANK)
        {
            cout<<"\nThe computer missed! ("<<x<<','<<y<<")\n";
            target.map[x][y] = MISS;
            hit_map[x][y] = MISS;
            lastHit = false;
            runLoop = false;
        }
        else{
            cout<<"\nSomething went very wrong with the AI targeting system.\n";
        }
        //cout<<"You should have recieved a message by now\n";
    }while (runLoop);
    //cout<<"Exiting the loop x="<<x<<"   y="<<y<<"  state: "<<(int)state<<"\n";
}


void ComputerPlayer::advanceState(){
    switch (state) {
        case RAND:
            break;
            
        default:
            break;
    }
}

SliceAndDice::SliceAndDice(){
    runLoop=true;
    state=SLICE;
    Point point;
    for (int i=0; i<BOARDX; i++){
        point.set(i,i);
        hitlist.push(point);
    }
    for (int i=BOARDX-1; i>=0; i--){
        point.set(i,(BOARDY-i)-1);
        hitlist.push(point);
    }
}
