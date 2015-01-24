#ifndef KNIGHT_COMPONENT_H
#define KNIGHT_COMPONENT_H
#include "Hummingbird-Base.h"
#include "Hummingbird-Box2D.h"
#include "InputManager.h"
#include "PlayerComponent.h"

using namespace hb;

class KnightComponent : public GameObject::Component
{
public:
	KnightComponent();

	void update() override;

private:
	PlayerComponent* m_player_component;
};

#endif