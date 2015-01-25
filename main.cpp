#include <iostream>
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
	srand (time(NULL));
	hb::RenderWindowManager window_manager1(new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML works!"));

	PhysicsWorld::instance()->setGravity(Vector2d(0.0f, 15.0f));

	Player* player1 = new Player(hb::Vector3d(9, 17, 0), 1, false, 1);
	Player* player2 = new Player(hb::Vector3d(10, 17, 0), 2, true, 0);
	Player* player3 = new Player(hb::Vector3d(11, 17, 0), 3, true, 1);
	Player* player4 = new Player(hb::Vector3d(12, 17, 0), 4, true, 2);
	std::cout << "hai" << std::endl;
	HUDplayer* hud_player1 = new HUDplayer(player1, &window_manager1);
	HUDplayer* hud_player2 = new HUDplayer(player2, &window_manager1);
	HUDplayer* hud_player3 = new HUDplayer(player3, &window_manager1);
	HUDplayer* hud_player4 = new HUDplayer(player4, &window_manager1);
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
	//std::cout << "haisus" << std::endl;
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
		int max = 0;
		if (player1->isAlive()) max = player1->getPosition().x;
		if (max < player2->getPosition().x && player2->isAlive()) max = player2->getPosition().x;
		if (max < player3->getPosition().x && player3->isAlive()) max = player3->getPosition().x;
		if (max < player4->getPosition().x && player4->isAlive()) max = player4->getPosition().x;

		int min = 0;
		if (player1->isAlive()) min = player1->getPosition().x;
		if (min > player2->getPosition().x && player2->isAlive()) min = player2->getPosition().x;
		if (min > player3->getPosition().x && player3->isAlive()) min = player3->getPosition().x;
		if (min > player4->getPosition().x && player4->isAlive()) min = player4->getPosition().x;

		int Ymax= 0;
		if (player1->isAlive()) Ymax = player1->getPosition().y;
		if (Ymax < player2->getPosition().y && player2->isAlive()) Ymax = player2->getPosition().y;
		if (Ymax < player3->getPosition().y && player3->isAlive()) Ymax = player3->getPosition().y;
		if (Ymax < player4->getPosition().y && player4->isAlive()) Ymax = player4->getPosition().y;

		int Ymin=0;
		if (player1->isAlive()) Ymin = player1->getPosition().y;
		if (Ymin > player2->getPosition().y && player2->isAlive()) Ymin = player2->getPosition().y;
		if (Ymin > player3->getPosition().y && player3->isAlive()) Ymin = player3->getPosition().y;
		if (Ymin > player4->getPosition().y && player4->isAlive()) Ymin = player4->getPosition().y;

		if (max-min >= 10)
		{
			if (min == player1->getPosition().x) player1->die();
			if (min == player2->getPosition().x) player2->die();
			if (min == player3->getPosition().x) player3->die();
			if (min == player4->getPosition().x) player4->die();
		}

		auto view = window_manager1.getWindow()->getView();
		view.setCenter(sf::Vector2f((max*1.4+min)/2, (Ymax*1.4+Ymin)/2));
		window_manager1.getWindow()->setView(view);

		GameObject::updateHUD();
		window_manager1.draw();

	}

	hb::GameObject::destroyAll();
	return 0;
}
