#ifndef BATTLE_SHIP_H
#define BATTLE_SHIP_H

#define BOARDX 8
#define BOARDY 8
enum SPACE_TYPE{BLANK, HIT, MISS, SHIP};
enum STATE{RAND, CHECK, FOLLOW, FOLLOW2};

class Player{
private:
    void place_ships();
    void render_map(int map[BOARDX][BOARDY]);
    
public:
    int map[BOARDX][BOARDY];
    int hit_map[BOARDX][BOARDY];
    
    Player();
    virtual ~Player() {}
    virtual void turn(Player &target) = 0;
    void render_board();
    bool check_for_hit(int x, int y);
    bool ships_left();
};

class HumanPlayer : public Player{
private:
public:
    void turn(Player &target);
};

class Point {
public:
    Point(){x=y=0;}
    void set(int x, int y) { this->x = x; this->y = y; }
    
    int x;
    int y;
};

class ComputerPlayer : public Player{
private:
    void advanceState();
    STATE state;
    int lastx, lasty;
    Point firstHit;
    bool runLoop;
public:
    ComputerPlayer(){lasty=lastx=0; state=RAND; runLoop=true;}
    void turn(Player &target);
};

#endif
