#include "Player.h"

Player::Player(int player_number, int max_hp, int cur_hp int run_speed, int jump_speed):
GameObject(),
player_number(player_number),
max_hp(max_hp),
hp(cur_hp),
run_speed(run_speed),
jump_speed(jump_speed)
{
	PlayerComponent* pc = new PlayerComponent(player_number, max_hp, cur_hp, run_speed, jump_speed);
	addComponent(pc);
}

int Player::current_player;


#endif