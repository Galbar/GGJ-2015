#include "Player.h"

Player::Player(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed):
GameObject()
{
	PlayerComponent* pc = new PlayerComponent(player_number, max_hp, cur_hp, alive, run_speed, jump_speed);
	addComponent(pc);
}