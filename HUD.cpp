#include "HUD.h"

HUD::HUD():
GameObject()
{
	setName("HUD");
}

Vector3d HUD::windowToWorldCoord(Vector2d p, RenderWindowManager* render)
{
	sf::Vector2f viewpos = render->getWindow()->getView().getCenter();
	int xDif = (render->getWindow()->getSize().x/2)-p.x;
	int yDif = (render->getWindow()->getSize().y/2)-p.y;
	return Vector3d(viewpos.x-xDif, viewpos.y-yDif, 10000000);
}
