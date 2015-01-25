#include "HUDplayer.h"

HUDplayer::HUDplayer(Player* p, RenderWindowManager* r):
HUD(),
player(p)
{
	HUDplayerComponent* hpc = new HUDplayerComponent(p, r);
	addComponent(hpc);

	sf::Shape* s = new sf::RectangleShape(sf::Vector2f(200, 30));

	StaminaComponent* sc = new StaminaComponent(s, r, player->player_controller);
	addComponent(sc);

	s = new sf::RectangleShape(sf::Vector2f(200, 30));
	s->setFillColor(sf::Color::Transparent);
	s->setOutlineThickness(4);
	s->setOutlineColor(sf::Color::Black);
	ShapeComponent* rect = new ShapeComponent(s, r);
	addComponent(rect);
}