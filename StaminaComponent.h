#ifndef STAMINA_COMPONENT_H
#define STAMINA_COMPONENT_H
#include "Hummingbird-SFML.h"
#include "PlayerComponent.h"

using namespace hb;

class StaminaComponent : public ShapeComponent
{
public:
	StaminaComponent(sf::Shape* s, RenderWindowManager* r, PlayerComponent* pc);

	void update() override;

private:
	PlayerComponent* player;
};

#endif