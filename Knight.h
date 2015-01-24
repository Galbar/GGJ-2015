#ifndef KNIGHT_H
#define KNIGHT_H
#include "Player.h"
#include "KnightComponent.h"
#include "Hummingbird-Box2D.h"

class Knight : public Player
{
public:
	Knight(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed);


private:

};

#endif