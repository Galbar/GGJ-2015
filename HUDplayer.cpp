#include "HUDplayer.h"

HUDplayer::HUDplayer(Player* p, RenderWindowManager* r):
HUD(),
player(p)
{
	HUDplayerComponent* hpc = new HUDplayerComponent(p, r);
	addComponent(hpc);

	sf::Shape* s = new sf::RectangleShape(sf::Vector2f(100, 20));

	StaminaComponent* sc = new StaminaComponent(s, r, player->player_controller);
	addComponent(sc);
}