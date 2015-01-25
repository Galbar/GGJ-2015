#ifndef PLAYER_H
#define PLAYER_H
#include "PlayerComponent.h"

class Player : public GameObject
{
public:
	Player(Vector3d init_pos, int player_number, bool controller, int controllerId);

	int player_number;
	PlayerComponent* player_controller;

};


#endif