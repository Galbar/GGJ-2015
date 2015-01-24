#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H
#include "Hummingbird-Base.h"
#include "Hummingbird-Box2D.h"
#include "InputManager.h"
#include <vector>

using namespace hb;

class PlayerComponent : public GameObject::Component
{
public:
	PlayerComponent(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed);
	~PlayerComponent();

	void update() override;
	int getXDir() const;

	static int current_player;
	static GameObject* active_player;

private:
	//Player attributes
	int cur_hp;
	int max_hp;
	bool alive;
	bool active;

	int player_number;
	int run_speed;
	int jump_speed;

	// State attributes
	int xDir;
	int yDir;
	bool jumping;
	bool clickedJump;
	sf::Keyboard::Key last_key;


	InputManager::ListenerId<KeyPressed> listen_key_pressed;
	InputManager::ListenerId<KeyReleased> listen_key_released;
	InputManager::ListenerId<MouseButtonWindow> listen_mouse_window;
	InputManager::ListenerId<MouseButtonWorld> listen_mouse_world;

};


#endif