#include "HUDplayerComponent.h"

HUDplayerComponent::HUDplayerComponent(Player* p, RenderWindowManager* r):
GameObject::Component(),
player(p),
window(r)
{}


void HUDplayerComponent::preUpdate()
{
	xCoords[1] = 0.2*window->getWindow()->getSize().x;
	xCoords[2] = 0.4*window->getWindow()->getSize().x;
	xCoords[3] = 0.6*window->getWindow()->getSize().x;
	xCoords[4] = 0.8*window->getWindow()->getSize().x;

	yCoords = 0.8*window->getWindow()->getSize().y;

	Vector3d spritePos = HUD::windowToWorldCoord(Vector2d(xCoords[player->player_number], yCoords));
	getGameObject()->setPosition(spritePos);
}