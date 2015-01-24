#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <SFML/Window.hpp>
#include "Hummingbird-Base/EventManager.h"
#include "Hummingbird-SFML/RenderWindowManager.h"

struct MouseButtonWindow
{
	sf::Mouse::Button button;
	int x, y;
	explicit MouseButtonWindow(const sf::Event::MouseButtonEvent& ev):
	button(ev.button),
	x(ev.x),
	y(ev.y)
	{}
};

struct MouseButtonWorld
{
	sf::Mouse::Button button;
	int x, y;
	explicit MouseButtonWorld(const sf::Event::MouseButtonEvent& ev, const hb::RenderWindowManager& window):
	button(ev.button),
	x(ev.x),
	y(ev.y)
	{
		x += window.getWindow()->getView().getCenter().x - window.getWindow()->getSize().x / 2;
		y += window.getWindow()->getView().getCenter().y - window.getWindow()->getSize().y / 2;
	}
};

struct KeyPressed
{
	sf::Keyboard::Key code;
	bool alt, control, shift, system;
	explicit KeyPressed(const sf::Event::KeyEvent& ev):
	code(ev.code),
	alt(ev.alt),
	control(ev.control),
	shift(ev.shift),
	system(ev.system)
	{}
};

struct KeyReleased
{
	sf::Keyboard::Key code;
	bool alt, control, shift, system;
	explicit KeyReleased(const sf::Event::KeyEvent& ev):
	code(ev.code),
	alt(ev.alt),
	control(ev.control),
	shift(ev.shift),
	system(ev.system)
	{}
};


class InputManager : public hb::EventManager<MouseButtonWindow, MouseButtonWorld, KeyPressed, KeyReleased>
{
public:
	static InputManager* instance()
	{
		if (s_instance == nullptr)
			s_instance = new InputManager();
		return s_instance;
	}

private:
	static InputManager* s_instance;
};
InputManager* InputManager::s_instance = nullptr;
#endif