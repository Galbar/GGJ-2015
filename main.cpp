#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Knight.h"
#include "Hummingbird-Base.h"
#include "Hummingbird-SFML.h"
#include "Scene.h"

class MoveToClick : public hb::GameObject::Component
{
public:
	MoveToClick()
	{
		listener_id = InputManager::instance()->listen([this](const MouseButtonWorld& e)
		{
			getGameObject()->setPosition(hb::Vector3d(e.x, e.y, getGameObject()->getPosition().z));
		});
	}
	~MoveToClick()
	{
		InputManager::instance()->ignore(listener_id);
	}
private:
	InputManager::ListenerId<MouseButtonWorld> listener_id;

};

int main(int argc, char const *argv[])
{
	hb::RenderWindowManager window_manager1(new sf::RenderWindow(sf::VideoMode(600, 600), "SFML works!"));

	PhysicsWorld::instance()->setGravity(Vector2d(0.0f, 5.0f));

	Knight* go1 = new Knight(Vector3d(5, 5, 0), 1, 0, 0, true, 5, -10);
	PlayerComponent::active_player = go1;
	hb::AnimatedSpriteComponent* sp1 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp1->setTexture("asd");
	sp1->setFrameSize(hb::Vector2d(32, 32));
	//sp1->setScale(hb::Vector3d(1, 2, 1));
	go1->addComponent(sp1);


	go1 = new Knight(Vector3d(7, 5, 0), 2, 0, 0, true, 5, -10);
	
	sp1 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp1->setTexture("asd");
	sp1->setFrameSize(hb::Vector2d(32, 32));
	//sp1->setScale(hb::Vector3d(1, 2, 1));
	go1->addComponent(sp1);


	go1 = new Knight(Vector3d(3, 5, 0), 3, 0, 0, true, 5, -10);
	
	sp1 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp1->setTexture("asd");
	sp1->setFrameSize(hb::Vector2d(32, 32));
	//sp1->setScale(hb::Vector3d(1, 2, 1));
	go1->addComponent(sp1);


	go1 = new Knight(Vector3d(9, 5, 0), 4, 0, 0, true, 5, -10);
	
	sp1 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp1->setTexture("asd");
	sp1->setFrameSize(hb::Vector2d(32, 32));
	//sp1->setScale(hb::Vector3d(1, 2, 1));
	go1->addComponent(sp1);


	hb::FunctionComponent* move = new hb::FunctionComponent();
	move->setUpdateFunction([&] (hb::GameObject* go)
	{
		if (go->getPosition().x > 600)
			go->setPosition(hb::Vector3d(0, go->getPosition().y, go->getPosition().z));

		if (go->getPosition().y > 600)
			go->setPosition(hb::Vector3d(go->getPosition().x, 0, go->getPosition().z));

		go->setPosition(hb::Vector3d(go->getPosition().x+0.5, go->getPosition().y+0.5, go->getPosition().z));
		go->setRotation(hb::Vector3d(0, 0, go->getRotation().z+0.5));
	});
	//go1.addComponent(move);

	hb::GameObject* go2 = new GameObject();
	InputManager::instance()->listen([&] (const KeyPressed& ev)
	{
		if (ev.code == sf::Keyboard::Key::Up)
			go2->setPosition(go2->getPosition() + hb::Vector3d(0,-1,0));
		if (ev.code == sf::Keyboard::Key::Down)
			go2->setPosition(go2->getPosition() + hb::Vector3d(0,1,0));
		if (ev.code == sf::Keyboard::Key::Right)
			go2->setPosition(go2->getPosition() + hb::Vector3d(1,0,0));
		if (ev.code == sf::Keyboard::Key::Left)
			go2->setPosition(go2->getPosition() + hb::Vector3d(-1,0,0));
	});

	go2->addComponent(new MoveToClick());
	hb::AnimatedSpriteComponent* sp2 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp2->setFrameTime(hb::Time::seconds(0.3));
	sp2->setFrameInterval(0, 47);
	sp2->setFrameMargin(hb::Vector2d(1, 1));
	sp2->setFrameSize(hb::Vector2d(32, 32));
	sp2->setTexture("tilemap.png");
	go2->addComponent(sp2);
	go2->setPosition(hb::Vector3d(60, 60, 1));

	//std::cout << "go1 # FunctionComponent: " << go1.getComponents<hb::FunctionComponent>().size() << std::endl;
	hb::Time::deltaTime = hb::Time::seconds(0.001);
	Scene scene(&window_manager1, Scene::LVL1);
	sf::Clock clk;
	Time lastTime = Time::microseconds(clk.getElapsedTime().asMicroseconds());
	while (window_manager1.getWindow()->isOpen())
	{
		Time::deltaTime = Time::microseconds(clk.getElapsedTime().asMicroseconds())-lastTime;
		lastTime = Time::microseconds(clk.getElapsedTime().asMicroseconds());

		sf::Event event;
		if (window_manager1.getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_manager1.getWindow()->close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				MouseButtonWorld mbw(event.mouseButton, window_manager1);
				InputManager::instance()->message(mbw);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				KeyPressed kp(event.key);
				InputManager::instance()->message(kp);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				KeyReleased kr(event.key);
				InputManager::instance()->message(kr);
			}
		}

		hb::PhysicsWorld::instance()->update();
		hb::GameObject::updateAll();

		auto view = window_manager1.getWindow()->getView();
		view.setCenter(sf::Vector2f(PlayerComponent::active_player->getPosition().x, PlayerComponent::active_player->getPosition().y));
		window_manager1.getWindow()->setView(view);

		window_manager1.draw();

	}
	hb::GameObject::destroyAll();
	return 0;
}
