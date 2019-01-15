#ifndef BATTLE_SHIP_H
#define BATTLE_SHIP_H

#define BOARDX 8
#define BOARDY 8
enum SPACE_TYPE{BLANK, HIT, MISS, SHIP};

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

class ComputerPlayer : public Player{
private:
public:
    void turn(Player &target);
};

#endif
