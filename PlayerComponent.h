#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H
#include "Hummingbird-Base.h"

using namespace hb;

class PlayerComponent : public GameObject::Component
{
public:
	PlayerComponent(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed);

	void update() override;

private:
	int cur_hp;
	int max_hp;
	bool alive;

	int player_number;
	int run_speed;
	int jump_speed;

};


#endif