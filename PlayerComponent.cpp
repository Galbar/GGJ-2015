#include "PlayerComponent.h"
#include <iostream>

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
		last_key = e.code;
		if (e.code == sf::Keyboard::Key::D) xDir = 1;
		else if (e.code == sf::Keyboard::Key::A) xDir = -1;
		else if (e.code == sf::Keyboard::Key::Space || !jumping) yDir = 1, jumping = true;
	});

	listen_key_released = InputManager::instance()->listen([this](const KeyReleased& e)
	{
		if (e.code == sf::Keyboard::Key::D || e.code == sf::Keyboard::Key::A)
		{
			if (last_key != e.code) return;
			xDir = 0;
		}
		else if (e.code == sf::Keyboard::Key::Space) jumping = false;

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
	std::vector<CollisionComponent*> collider = getGameObject()->getComponents<CollisionComponent>();
	
	b2Body* body = collider[0]->getBody();
	body->SetLinearVelocity(b2Vec2(run_speed*xDir, yDir));
	if (yDir == 1) yDir = 0;

	getGameObject()->setPosition(Vector3d(body->GetPosition().x, body->GetPosition().y, 0));
}