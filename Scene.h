#ifndef SCENE_H
#define SCENE_H
#include "Hummingbird-Base.h"
#include "Hummingbird-SFML.h"
#include "Hummingbird-Box2D.h"

class Scene
{
public:
	enum levels
	{
		LVL1,
		COUNT
	};
	Scene(hb::RenderWindowManager* window_manager, levels lvl);
	virtual ~Scene();
	virtual void update();

protected:
	static std::string getLevelPath(levels lvl);
	hb::GameObject* m_tilemap_obj;
};
#endif