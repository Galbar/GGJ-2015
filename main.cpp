#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
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
	int num_players = 4;
	if (argc == 2)
	{
		num_players = atoi(argv[1]);
	}
	srand (time(NULL));
	hb::RenderWindowManager window_manager1(new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML works!"));

	PhysicsWorld::instance()->setGravity(Vector2d(0.0f, 15.0f));

	Player* player1 = new Player(hb::Vector3d(9, 17, 0), 1, false, 1);
	Player* player2 = new Player(hb::Vector3d(10, 17, 0), 2, true, 0);
	Player* player3 = new Player(hb::Vector3d(11, 17, 0), 3, true, 1);
	Player* player4 = new Player(hb::Vector3d(12, 17, 0), 4, true, 2);
	new HUDplayer(player1, &window_manager1);
	new HUDplayer(player2, &window_manager1);
	new HUDplayer(player3, &window_manager1);
	new HUDplayer(player4, &window_manager1);
	hb::AnimatedSpriteComponent* sc1 = new hb::AnimatedSpriteComponent(&window_manager1);
	sc1->setTexture("Asd");
	sc1->setFrameSize(hb::Vector2d(32, 32));
	sc1->setFrameInterval(0, 2);
	hb::AnimatedSpriteComponent* sc2 = new hb::AnimatedSpriteComponent(&window_manager1);
	sc2->setTexture("Asd");
	sc2->setFrameSize(hb::Vector2d(32, 32));
	sc2->setFrameInterval(0, 2);
	hb::AnimatedSpriteComponent* sc3 = new hb::AnimatedSpriteComponent(&window_manager1);
	sc3->setTexture("Asd");
	sc3->setFrameSize(hb::Vector2d(32, 32));
	sc3->setFrameInterval(0, 2);
	hb::AnimatedSpriteComponent* sc4 = new hb::AnimatedSpriteComponent(&window_manager1);
	sc4->setTexture("Asd");
	sc4->setFrameSize(hb::Vector2d(32, 32));
	sc4->setFrameInterval(0, 2);
	player1->addComponent(sc1);
	player2->addComponent(sc2);
	player3->addComponent(sc3);
	player4->addComponent(sc4);
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

	Scene scene(&window_manager1, Scene::LVL1);
	sf::Clock clk;
	Time lastTime = Time::microseconds(clk.getElapsedTime().asMicroseconds());
	double camera_previous_x = -1;
	std::vector<Player*> players = hb::GameObject::getGameObjectsByName<Player>("player");
	assert(players.size() != 0);
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


		int Xmax = 0;
		int Xmin = 0;
		int Ymax = 0;
		int Ymin = 0;
		bool first = true;
		for (Player* p : players)
		{
			if (not p->isAlive())
				continue;
			if (first)
			{
				first = false;
				Xmax = p->getPosition().x;
				Xmin = p->getPosition().x;
				Ymax = p->getPosition().y;
				Ymin = p->getPosition().y;
			}
			else
			{
				if (Xmax < p->getPosition().x and p->isAlive())
					Xmax = p->getPosition().x;

				if (Xmin > p->getPosition().x and p->isAlive())
					Xmin = p->getPosition().x;

				if (Ymax < p->getPosition().y and p->isAlive())
					Ymax = p->getPosition().y;

				if (Ymin > p->getPosition().y and p->isAlive())
					Ymin = p->getPosition().y;
			}
			
			if (camera_previous_x - window_manager1.getWindow()->getSize().x/2 >= p->getPosition().x)
				p->die();

			if (p->getPosition().y > 1800)
				p->die();

		}
		scene.update(Xmax);

		if (camera_previous_x == -1)
		{
			camera_previous_x = (Xmax*1.4+Xmin)/2.4;
		}

		auto view = window_manager1.getWindow()->getView();
		if (camera_previous_x > (Xmax*1.4+Xmin)/2.4)
		{
			view.setCenter(sf::Vector2f(camera_previous_x, (Ymax+Ymin)/2.0));
		}
		else
		{
			view.setCenter(sf::Vector2f((Xmax*1.4+Xmin)/2.4, (Ymax+Ymin)/2.0));
			camera_previous_x = (Xmax*1.4+Xmin)/2.4;
		}
		window_manager1.getWindow()->setView(view);


		GameObject::updateHUD();
		window_manager1.draw();
	}

	hb::GameObject::destroyAll();
	return 0;
}
