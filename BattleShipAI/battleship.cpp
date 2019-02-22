#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "battleship.h"

using namespace std;

Player::Player()
{
    for (int i=0; i<BOARDY; i++)
    {
        for (int j=0; j<BOARDX; j++)
        {
            map[i][j] = BLANK;
            hit_map[i][j] = BLANK;
        }
    }
    place_ships();
}

bool Player::check_for_hit(int x, int y)
{
    switch (map[x][y])
    {
        case MISS:
        case HIT:
        case BLANK:
            cout<<"\nMiss!\n";
            map[x][y] = MISS;
            break;
            
        case SHIP:
            cout<<"\nHit!\n";
            map[x][y] = HIT;
            return true;
            break;
    }
    return false;
}

void Player::place_ships()
{
    int ship_size = 5;
    bool vert;
    bool cont = false;//to check if we should continue outside of the loop
    bool pos; //should the ship be placed in a positive direction?
    int x, y;
    while (ship_size != 1)
    {
        cont = false;//so that we don't get inf loops
        x = rand() % BOARDX;
        y = rand() % BOARDY;
        if (rand() % 100+1 < 50){vert = true;}
        else{vert = false;}
        if (rand() % 100+1 < 50){pos = false;}
        else{pos = true;}
        //check if ship is placed legaly
        if (vert)
        {
            if (pos){
                if (y + ship_size > BOARDY) {pos = false;}}
            if (!pos){
                if (y - ship_size < 0) {continue;}}
            for (int i=0; i<ship_size; i++)
            {
                if (pos){
                    if (map[x][y+i] == SHIP) {cont = true;}}
                else{
                    if (map[x][y-i] == SHIP) {cont = true;}}
            }
            if (cont) {continue;}
        }
        else
        {
            if (pos){
                if (x + ship_size > BOARDX) {continue;}}
            else{
                if (x - ship_size < 0) {continue;}}
            for (int i=0; i<ship_size; i++)
            {
                if (pos){
                    if (map[x+i][y] == SHIP) {cont = true;}}
                else{
                    if (map[x-i][y] == SHIP) {cont = true;}}
            }
            if (cont) {continue;}
        }
        //place the ship
        for (int i=0; i<ship_size; i++)
        {
            map[x][y] = SHIP;
            if (vert)
            {
                if (pos) y++;
                else y--;
            }
            else
            {
                if (pos) x++;
                else x--;
            }
        }
        ship_size--;
    }
}

bool Player::ships_left()
{
    for (int i=0; i<BOARDY; i++)
    {
        for (int j=0; j<BOARDX; j++)
        {
            if (map[j][i] == SHIP)
            {return true;}
        }
    }
    return false;
}

void Player::render_map(int map[BOARDX][BOARDY])
{
    cout<<"   ";
    for (int k=0; k<BOARDX; k++){
        cout<<k+1<<"  ";
    }
    cout<<endl;
    
    for (int i=0; i<BOARDY; i++)
    {
        cout<<i+1<<' ';
        for (int j=0; j<BOARDX; j++)
        {
            cout<<"[";
            switch (map[j][i])
            {
                case BLANK:
                    cout<<" ";
                    break;
                    
                case HIT:
                    cout<<"O";
                    break;
                    
                case MISS:
                    cout<<"X";
                    break;
                    
                case SHIP:
                    cout<<"S";
                    break;
            }
            cout<<"]";
        }
        cout<<endl;
    }
}

void Player::render_board()
{
    render_map(hit_map);
    
    cout<<"--";
    for (int i=0; i<BOARDX; i++)
    {
        cout<<"---";
    }
    cout<<endl;
    
    render_map(map);
}


void HumanPlayer::turn(Player &target)
{
    int x, y;
    
    do{
        cout<<"x = ";
        cin>>x;
        if (x < 0 || x > BOARDX){
            cout<<"\n\""<<x<<"\" is not a valid tile!\n";
        }
        else break;
    }while(true);
    
    do{
        cout<<"y = ";
        cin>>y;
        if (y < 0 || y > BOARDX){
            cout<<"\n\""<<y<<"\" is not a valid tile!\n";
        }
        else break;
    }while(true);
    x--;
    y--;
    cout<<"\n\n";
    
    if (target.check_for_hit(x, y))
        hit_map[x][y] = HIT;
    else
        hit_map[x][y] = MISS;
}
