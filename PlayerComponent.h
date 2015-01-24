#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H
#include "Hummingbird-Base.h"
#include "Hummingbird-Box2D.h"
#include "InputManager.h"
#include <vector>
#include <iostream>

using namespace hb;

class PlayerComponent : public GameObject::Component
{
public:
	PlayerComponent(int player_number, bool controller, int controllerId);
	~PlayerComponent();

	void update() override;
	int getXDir() const;

private:
	//Player attributes
	bool active;
	bool alive;
	bool controller;
	int controllerId;
	double run_speed;
	double jump_speed;


	// State attributes
	int xDir;
	int yDir;
	bool jumping;
	bool clickedJump;
	sf::Keyboard::Key last_key;


	InputManager::ListenerId<KeyPressed> listen_key_pressed;
	InputManager::ListenerId<KeyReleased> listen_key_released;
	InputManager::ListenerId<JoyButtonPressed> listen_joy_pressed;
	InputManager::ListenerId<JoyButtonReleased> listen_joy_released;

};


#endif