#ifndef HUD_H
#define HUD_H
#include "Hummingbird-Base.h"
#include "Hummingbird-SFML.h"

using namespace hb;

class HUD : public GameObject
{
public:
	HUD();
	static Vector3d windowToWorldCoord(Vector2d, RenderWindowManager* render);

};


#endif