#include "PlayerComponent.h"
#include "Scene.h"
#include <iostream>

int PlayerComponent::current_player = 1;
int PlayerComponent::numFootContacts = 1;

PlayerComponent::PlayerComponent(int player_number, bool controller, int controllerId):
GameObject::Component()
{
	// Initial values
	xDir = 0;
	yDir = 0;
	jumping = false;
	clickedJump = false;

	// Config
	fl = new FootListener();
	//PhysicsWorld::instance()->getWorld()->SetContactListener(fl);

	// Input events
	listen_key_pressed = InputManager::instance()->listen([this](const KeyPressed& e)
	{
		if (!controller)
		{
			if (e.code == sf::Keyboard::Key::D) xDir = 1, last_key = e.code;
			else if (e.code == sf::Keyboard::Key::A) xDir = -1, last_key = e.code;
			else if (e.code == sf::Keyboard::Key::Space && !jumping && !clickedJump) 
				yDir = 1, jumping = true, clickedJump = true, grounded = false;
		}
		
	});

	listen_key_released = InputManager::instance()->listen([this](const KeyReleased& e)
	{
		if (e.code == sf::Keyboard::Key::D || e.code == sf::Keyboard::Key::A)
		{
			if (last_key != e.code) return;
			xDir = 0;
		}
		else if (e.code == sf::Keyboard::Key::Space) jumping = false, clickedJump = false;

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

	body->SetLinearVelocity(b2Vec2(run_speed*xDir, body->GetLinearVelocity().y));
	if (jumping)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jump_speed));
		jumping = false;
	}

	grounded = (numFootContacts >= 1);

	getGameObject()->setPosition(Vector3d(body->GetPosition().x*32, body->GetPosition().y*32, getGameObject()->getPosition().z));
}