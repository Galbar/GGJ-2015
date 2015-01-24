#include "Player.h"

Player::Player(Vector3d init_pos, int player_number, bool controller, int controllerId):
GameObject(init_pos)
{
	PlayerComponent* pc = new PlayerComponent(player_number, controller, controllerId);
	addComponent(pc);
}