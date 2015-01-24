#include "Scene.h"

Scene::Scene(hb::RenderWindowManager* window_manager, levels lvl)
{
	m_tilemap_obj = new hb::GameObject();
	sf::Image tilemap;
	tilemap.loadFromFile(getLevelPath(lvl));
	sf::Vector2u size = tilemap.getSize();
	m_tilemap_obj->setPosition(hb::Vector3d(0, 0, -1000));
	for (unsigned int i = 0; i < size.x; ++i)
	{
		for (unsigned int j = 0; j < size.y; ++j)
		{
			hb::SpriteComponent* t;
			t = new hb::SpriteComponent(window_manager);
			if (tilemap.getPixel(i, j).r < 122)
			{
				t->setTexture("tilemap.png", sf::IntRect(138, 308, 32, 32));
			}
			else
			{
				t->setTexture("tilemap.png", sf::IntRect(36, 308, 32, 32));
			}
			t->setPosition(hb::Vector3d(32 * i, 32 * j , 0));
			m_tilemap_obj->addComponent(t);
		}
	}
}


Scene::~Scene()
{
	hb::GameObject::destroyAll();
	hb::TextureManager::instance()->clear();
	hb::SoundManager::instance()->clear();
}


void Scene::update()
{
	hb::GameObject::updateAll();
}


std::string Scene::getLevelPath(levels lvl)
{
	std::vector<std::string> v(COUNT);
	v[LVL1] = "lvl-demo.png";

	return v[lvl];
}