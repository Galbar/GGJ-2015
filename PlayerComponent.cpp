#include "PlayerComponent.h"
#include "Scene.h"
#include <iostream>

int PlayerComponent::current_player = 1;

PlayerComponent::PlayerComponent(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed):
GameObject::Component(),
cur_hp(cur_hp),
max_hp(max_hp),
alive(alive),
player_number(player_number),
run_speed(run_speed),
jump_speed(jump_speed)
{
	// Initial values
	xDir = 0;
	yDir = 0;
	jumping = false;
	clickedJump = false;
	grounded = true;

	// Input events
	listen_key_pressed = InputManager::instance()->listen([this](const KeyPressed& e)
	{
		if (e.code == sf::Keyboard::Key::Num1) current_player = 1;
		else if (e.code == sf::Keyboard::Key::Num2) current_player = 2;
		else if (e.code == sf::Keyboard::Key::Num3) current_player = 3;
		else if (e.code == sf::Keyboard::Key::Num4) current_player = 4;
		if (current_player == this->player_number)
		{
			if (e.code == sf::Keyboard::Key::D) xDir = 1, last_key = e.code;
			else if (e.code == sf::Keyboard::Key::A) xDir = -1, last_key = e.code;
			else if (e.code == sf::Keyboard::Key::Space && !jumping && !clickedJump && grounded) yDir = 1, jumping = true, clickedJump = true;
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

	body->SetLinearVelocity(b2Vec2(run_speed*xDir, body->GetLinearVelocity().y));
	if (jumping)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jump_speed));
		jumping = false;
	}

	b2Fixture* fixt = NULL;
	grounded = false;
	float size = getGameObject()->getScale().y;
	Vector3d p = getGameObject()->getPosition();
	float dist = PhysicsWorld::instance()->GetRayCastDistance(b2Vec2(p.x, p.y), b2Vec2(p.x, p.y-0.55), fixt);
	if (fixt != NULL)
	{
		GameObject* ptr = (GameObject*) fixt->GetBody()->GetUserData();
		grounded |= (dist < 1.0 && dist > 0.0 && ptr == nullptr);
	}
	dist = PhysicsWorld::instance()->GetRayCastDistance(b2Vec2(p.x-0.55, p.y), b2Vec2(p.x-0.55, p.y-0.55), fixt);
	if (fixt != NULL)
	{
		GameObject* ptr = (GameObject*) fixt->GetBody()->GetUserData();
		grounded |= (dist < 1.0 && dist > 0.0 && ptr == nullptr);
	}
	dist = PhysicsWorld::instance()->GetRayCastDistance(b2Vec2(p.x+0.55, p.y), b2Vec2(p.x+0.55, p.y-0.55), fixt);
	if (fixt != NULL)
	{
		GameObject* ptr = (GameObject*) fixt->GetBody()->GetUserData();
		grounded |= (dist < 1.0 && dist > 0.0 && ptr == nullptr);
	}

	getGameObject()->setPosition(Vector3d(body->GetPosition().x*32, body->GetPosition().y*32, getGameObject()->getPosition().z));
}