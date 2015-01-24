#ifndef PLAYER_H
#define PLAYER_H
#include "PlayerComponent.h"

class Player : public GameObject
{
public:
	Player(Vector3d init_pos, int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed);

};


#endif