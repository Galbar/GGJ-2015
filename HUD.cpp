#include "HUD.h"

HUD::HUD():
GameObject()
{}

Vector3d HUD::windowToWorldCoord(Vector2d p)
{
	return Vector3d(p.x, p.y, 10000000);
}
