#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Knight.h"
#include "Hummingbird-Base.h"
#include "Hummingbird-SFML.h"
#include "Scene.h"
#include "HUDplayer.h"

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

	PhysicsWorld::instance()->setGravity(Vector2d(0.0f, 15.0f));

	Player* player = new Player(hb::Vector3d(9, 17, 0), 1, false, 0);
	HUDplayer* hud_player1 = new HUDplayer(player, &window_manager1);
	hb::AnimatedSpriteComponent* sc = new hb::AnimatedSpriteComponent(&window_manager1);
	sc->setTexture("Asd");
	sc->setFrameSize(hb::Vector2d(32, 32));
	sc->setFrameInterval(0, 2);
	player->addComponent(sc);
	hb::GameObject* go2 = new GameObject();

	go2->addComponent(new MoveToClick());
	hb::AnimatedSpriteComponent* sp2 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp2->setFrameTime(hb::Time::seconds(0.3));
	sp2->setFrameInterval(0, 47);
	sp2->setFrameMargin(hb::Vector2d(1, 1));
	sp2->setFrameSize(hb::Vector2d(32, 32));
	sp2->setTexture("tilemap.png");
	go2->addComponent(sp2);
	go2->setPosition(hb::Vector3d(60, 60, 1));

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
			else if (event.type == sf::Event::JoystickButtonPressed)
			{
				JoyButtonPressed jbp(event.joystickButton);
				InputManager::instance()->message(jbp);
			}
			else if (event.type == sf::Event::JoystickButtonReleased)
			{
				JoyButtonReleased jbr(event.joystickButton);
				InputManager::instance()->message(jbr);
			}
			else if (event.type == sf::Event::JoystickMoved)
			{
				JoyAxis ja(event.joystickMove);
				InputManager::instance()->message(ja);
			}
			else if (event.type == sf::Event::Resized)
			{
				auto view = window_manager1.getWindow()->getView();
				view.setSize(sf::Vector2f(event.size.width, event.size.height));
				window_manager1.getWindow()->setView(view);
			}
		}

		hb::PhysicsWorld::instance()->update();
		scene.update();

		auto view = window_manager1.getWindow()->getView();
		view.setCenter(sf::Vector2f(player->getPosition().x, player->getPosition().y));
		window_manager1.getWindow()->setView(view);

		window_manager1.draw();

	}
	hb::GameObject::destroyAll();
	return 0;
}
