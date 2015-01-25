#include "StaminaComponent.h"

StaminaComponent::StaminaComponent(sf::Shape* s, RenderWindowManager* r, PlayerComponent* pc):
ShapeComponent(s, r),
player(pc)
{}

void StaminaComponent::update()
{
	double stamina = player->getStamina();
	sf::Shape* aux = new sf::RectangleShape(sf::Vector2f(stamina, 20.0));
	setShape(aux);
}