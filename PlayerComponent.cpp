#include "PlayerComponent.h"

PlayerComponent::PlayerComponent(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed):
GameObject::Component(),
cur_hp(cur_hp),
max_hp(max_hp),
alive(alive),
player_number(player_number),
run_speed(run_speed),
jump_speed(jump_speed)
{
	// Input events
	listen_key_pressed = InputManager::instance()->listen([this](const KeyPressed& e)
	{
		
	});

	listen_key_released = InputManager::instance()->listen([this](const KeyReleased& e)
	{

	});

	listen_mouse_window = InputManager::instance()->listen([this](const MouseButtonWindow& e)
	{

	});

	listen_mouse_world = InputManager::instance()->listen([this](const MouseButtonWorld& e)
	{

	});
}


PlayerComponent::~PlayerComponent()
{
	InputManager::instance()->ignore(listen_key_pressed);
	InputManager::instance()->ignore(listen_key_released);
	InputManager::instance()->ignore(listen_mouse_window);
	InputManager::instance()->ignore(listen_mouse_world);
}


void PlayerComponent::update()
{

}