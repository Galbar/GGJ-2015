#ifndef HUD_PLAYER_COMPONENT_H
#define HUD_PLAYER_COMPONENT_H
#include "Hummingbird-Base.h"
#include "Hummingbird-SFML.h"
#include "Player.h"
#include "HUD.h"
#include "StaminaComponent.h"

using namespace hb;

class HUDplayerComponent : public GameObject::Component
{
public:
	HUDplayerComponent(Player* p, RenderWindowManager* r);

	void preUpdate() override;

private:
	Player* player;
	RenderWindowManager* window;

	int xCoords[5], yCoords;
};


#endif