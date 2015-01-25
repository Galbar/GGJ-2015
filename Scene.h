#ifndef SCENE_H
#define SCENE_H
#include <cstdlib>
#include <ctime>
#include "Hummingbird-Base.h"
#include "Hummingbird-SFML.h"
#include "Hummingbird-Box2D.h"
#include "LavaField.h"

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
	void loadFragment(std::string path, hb::RenderWindowManager* window_manager);
	virtual void update();

protected:
	static std::string getLevelPath();
	hb::GameObject* m_tilemap_obj;
	LavaField* m_lava_fields;
	hb::RenderWindowManager* m_window_manager;
};
#endif