#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed):
GameObject::Component(),
player_number(player_number),
max_hp(max_hp),
cur_hp(cur_hp),
alive(alive),
run_speed(run_speed),
jump_speed(jump_speed)
{}

void PlayerComponent::update()
{

}