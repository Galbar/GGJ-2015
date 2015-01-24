#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hummingbird-Base/Time.h"
#include "Hummingbird-Base/Vector3d.h"
#include "Hummingbird-Base/GameObject.h"
#include "Hummingbird-Base/FunctionComponent.h"
#include "Hummingbird-Base/EventManager.h"
#include "Hummingbird-SFML/TextureManager.h"
#include "Hummingbird-SFML/RenderWindowManager.h"
#include "Hummingbird-SFML/AnimatedSpriteComponent.h"

void hello(const sf::Event::KeyEvent)
{
	std::cout << "world" << std::endl;
}


class InputMove : public hb::GameObject::Component
{
public:
	std::function<void(const sf::Event::KeyEvent&)> handleEvent;
};

int main(int argc, char const *argv[])
{
	hb::EventManager<sf::Event::MouseButtonEvent, sf::Event::KeyEvent> event_manager;
	auto hello_id = event_manager.listen(std::function<void(const sf::Event::KeyEvent&)>(hello));
	hb::RenderWindowManager window_manager1(new sf::RenderWindow(sf::VideoMode(600, 600), "SFML works!1"));

	hb::GameObject go1;
	hb::AnimatedSpriteComponent* sp1 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp1->setTexture("asd");
	go1.addComponent(sp1);
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
	go1.addComponent(move);

	hb::GameObject go2;
	event_manager.listen([&] (const sf::Event::KeyEvent& ev)
	{
		if (ev.code == sf::Keyboard::Key::Up)
			go2.setPosition(go2.getPosition() + hb::Vector3d(0,-1,0));
		if (ev.code == sf::Keyboard::Key::Down)
			go2.setPosition(go2.getPosition() + hb::Vector3d(0,1,0));
		if (ev.code == sf::Keyboard::Key::Right)
			go2.setPosition(go2.getPosition() + hb::Vector3d(1,0,0));
		if (ev.code == sf::Keyboard::Key::Left)
			go2.setPosition(go2.getPosition() + hb::Vector3d(-1,0,0));
		if (ev.code == sf::Keyboard::Key::A)
			event_manager.ignore(hello_id);
	});
	hb::AnimatedSpriteComponent* sp2 = new hb::AnimatedSpriteComponent(&window_manager1);
	sp2->setFrameTime(hb::Time::seconds(0.3));
	sp2->setFrameInterval(0, 47);
	sp2->setFrameMargin(hb::Vector2d(1, 1));
	sp2->setFrameSize(hb::Vector2d(32, 32));
	sp2->setTexture("tiles.png");
	go2.addComponent(sp2);
	go2.setPosition(hb::Vector3d(60, 60, 1));

	std::cout << "go1 # FunctionComponent: " << go1.getComponents<hb::FunctionComponent>().size() << std::endl;
	hb::Time::deltaTime = hb::Time::seconds(0.001);
	while (window_manager1.getWindow()->isOpen())
	{
		sf::Event event;
		while (window_manager1.getWindow()->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window_manager1.getWindow()->close();
					break;
				case sf::Event::MouseButtonPressed:
					event_manager.message(event.mouseButton);
					break;
				case sf::Event::KeyPressed:
					event_manager.message(event.key);
					break;
			}

		}
		hb::GameObject::updateAll();
		window_manager1.draw();
	}
	return 0;
}
