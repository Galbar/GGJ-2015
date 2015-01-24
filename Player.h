#ifndef PLAYER_H
#define PLAYER_H
#include "Hummingbird-Base/GameObject.h"
#include "PlayerComponent.h"

using namespace hb;

class Player : public GameObject
{
public:
	Player(int player_number, int max_hp, int cur_hp, int run_speed, int jump_speed);

	static int current_player;

private:
	int hp;
	int max_hp;
	bool alive;

	int player_number;
	int run_speed;
	int jump_speed;


};


#endif