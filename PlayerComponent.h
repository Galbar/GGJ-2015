#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H
#include "Hummingbird-Base.h"
#include "Hummingbird-Box2D.h"
#include "Hummingbird-SFML.h"
#include "InputManager.h"
#include <vector>
#include <iostream>

#define JUMP_STAMINA 20.0

using namespace hb;

class PlayerComponent : public GameObject::Component
{
public:
	PlayerComponent(int player_number, bool controller, int controllerId);
	virtual ~PlayerComponent();

	void update() override;
	int getXDir() const;

	double getStamina();
	const double getStamina() const;

	bool isAlive();
	void die();

	int player_number;

private:
	//Player attributes
	bool active;
	bool alive;
	bool controller;
	int controllerId;
	double run_speed;
	double jump_speed;
	double stamina;


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
	InputManager::ListenerId<JoyAxis> listen_joy_axis;

};


#endif