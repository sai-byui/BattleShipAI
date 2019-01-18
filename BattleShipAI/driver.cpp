#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "battleship.h"

bool chance(float percent){
    if ((float)(rand() % 1000000)/10000 <= percent) return true;
    else return false;
}
void render_logo();

using namespace std;

int main()
{
    srand((long)time(NULL));
    bool done = false;
    
    //Allocate players
    Player *p1 = new HumanPlayer();
    Player *p2 = new ComputerPlayer();
    
    render_logo();
    
    p1->render_board();
    //cout<<"Entering Game loop\n";
    
    while (!done)
    {
        //cout<<"Starting turn p1\n";
        p1->turn(*p2);
        // Check if player one hit the last ship
        if (!p2->ships_left())
        {
            cout<<"\n\nPlayer One Wins!!!\n";
            done = true;
            continue;
        }
        //cout<<"Done:\nStarting turn p2\n";
        p2->turn(*p1);
        // Check if player two hit the last ship
        if (!p1->ships_left())
        {
            cout<<"\n\nPlayer Two Wins!!!\n";
            done = true;
            continue;
        }
        //cout<<"Done:\n";

        p1->render_board();
    }
    
    delete p1;
    delete p2;
    
    cin.ignore();
    cin.ignore();
    cin.ignore();
    return 0;
}

void render_logo()
{
    cout<<"|---------------|"<<endl;
    cout<<"|  Battle Ship  |"<<endl;
    cout<<"|---------------|"<<endl;
    
    cout<<endl;
}
