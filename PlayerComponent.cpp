#include "PlayerComponent.h"
#include "Scene.h"
#include <iostream>

PlayerComponent::PlayerComponent(int player_number, bool cont, int contId):
GameObject::Component(),
player_number(player_number)
{
	// Initial values
	xDir = 0;
	yDir = 0;
	jumping = false;
	clickedJump = false;
	alive = true;
	controller = cont;
	controllerId = contId;
	run_speed = 25.0;
	jump_speed = -22.0;
	stamina = 100.0;

	// Input events
	listen_key_pressed = InputManager::instance()->listen([this](const KeyPressed& e)
	{
		if (!controller and alive)
		{
			if (e.code == sf::Keyboard::Key::D) xDir = 1, last_key = e.code;
			else if (e.code == sf::Keyboard::Key::A) xDir = -1, last_key = e.code;
			else if (e.code == sf::Keyboard::Key::Space && !jumping && !clickedJump && stamina >=JUMP_STAMINA) 
				yDir = 1, jumping = true, clickedJump = true;
		}
		
	});

	listen_key_released = InputManager::instance()->listen([this](const KeyReleased& e)
	{
		if (!controller and alive)
		{
			if (e.code == sf::Keyboard::Key::D || e.code == sf::Keyboard::Key::A)
			{
				if (last_key != e.code) return;
				xDir = 0;
			}
			else if (e.code == sf::Keyboard::Key::Space) jumping = false, clickedJump = false;
		}

	});

	listen_joy_pressed = InputManager::instance()->listen([this](const JoyButtonPressed& e)
	{
		if (controller && (int)e.joystickId == controllerId && alive)
		{
			if (e.button == 0 && !jumping && !clickedJump && stamina >= 20.0)
				yDir = 1, jumping = true, clickedJump = true;
		}
	});

	listen_joy_released = InputManager::instance()->listen([this](const JoyButtonReleased& e)
	{
		if (controller && (int)e.joystickId == controllerId && alive)
		{
			if (e.button == 0) jumping = false, clickedJump = false;
		}
	});

	listen_joy_axis = InputManager::instance()->listen([this](const JoyAxis& e)
	{
		if (controller && (int)e.joystickId == controllerId && alive)
		{
			if (e.axis == sf::Joystick::Axis::X)
			{
				if (e.position > 30) xDir = 1;
				else if (e.position < -30) xDir = -1;
				else xDir = 0;
			}
		}
	});
}


PlayerComponent::~PlayerComponent()
{
	InputManager::instance()->ignore(listen_key_pressed);
	InputManager::instance()->ignore(listen_key_released);
	InputManager::instance()->ignore(listen_joy_pressed);
	InputManager::instance()->ignore(listen_joy_released);
}


bool PlayerComponent::isAlive()
{
	return alive;
}


void PlayerComponent::die()
{
	alive = false;
}


void PlayerComponent::update()
{
	std::vector<CollisionComponent*> collider = getGameObject()->getComponents<CollisionComponent>();

	b2Body* body = collider[0]->getBody();
	if (alive)
	{
		stamina += 15.0*Time::deltaTime.asSeconds();
		if (stamina > 100.0) stamina = 100.0;
		auto q = collider[0]->getCollisionQueue();
		while (not q.empty())
		{
			CollisionComponent* cc = q.front();
			q.pop();
			GameObject* go = cc->getGameObject();
			if (go->getName() == "Lava")
			{
				die();
			}
		}
	
		body->SetLinearVelocity(b2Vec2(run_speed*xDir, body->GetLinearVelocity().y));
		if (jumping)
		{
			stamina -= JUMP_STAMINA;
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jump_speed));
			jumping = false;
		}
	}
	getGameObject()->setPosition(Vector3d(body->GetPosition().x*32, body->GetPosition().y*32, getGameObject()->getPosition().z));
}

int PlayerComponent::getXDir() const
{
	return xDir;
}


double PlayerComponent::getStamina()
{
	return stamina;
}
