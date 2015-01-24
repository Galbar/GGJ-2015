#include "Scene.h"

Scene::Scene(hb::RenderWindowManager* window_manager, levels lvl)
{
	sf::Image tilemap;
	tilemap.loadFromFile(getLevelPath(lvl));
	sf::Vector2u size = tilemap.getSize();
	m_tilemap_obj.setPosition(hb::Vector3d(0, 0, -1000));
	for (unsigned int i = 0; i < size.x; ++i)
	{
		for (unsigned int j = 0; j < size.y; ++j)
		{
			hb::SpriteComponent* t;
			if (tilemap.getPixel(i, j).r == 0)
			{
				t = new hb::SpriteComponent(window_manager);
				t->setTexture("tilemap.png", sf::IntRect(138, 308, 32, 32));
			}
			else if (tilemap.getPixel(i, j).b == 99)
			{
				hb::AnimatedSpriteComponent* at = new hb::AnimatedSpriteComponent(window_manager);
				at->setTexture("tilemap.png", sf::IntRect(0, 204, 274, 68));
				at->setFrameTime(hb::Time::seconds(0.1));
				at->setFrameInterval(0, 7);
				at->setFrameSize(hb::Vector2d(32, 32));
				at->setFrameMargin(hb::Vector2d(2, 2));
				t = at;
			}
			else if (tilemap.getPixel(i, j).b == 100)
			{
				hb::AnimatedSpriteComponent* at = new hb::AnimatedSpriteComponent(window_manager);
				at->setTexture("tilemap.png", sf::IntRect(0, 204, 274, 68));
				at->setFrameTime(hb::Time::seconds(0.1));
				at->setFrameInterval(8, 15);
				at->setFrameSize(hb::Vector2d(32, 32));
				at->setFrameMargin(hb::Vector2d(2, 2));
				t = at;
			}
			else
			{
				t = new hb::SpriteComponent(window_manager);
				t->setTexture("tilemap.png", sf::IntRect(36, 308, 32, 32));
			}
			t->setPosition(hb::Vector3d(32 * i, 32 * j , 0));
			m_tilemap_obj.addComponent(t);
		}
	}
}


Scene::~Scene()
{
	hb::TextureManager::instance()->clear();
	hb::SoundManager::instance()->clear();
	hb::GameObject::destroyAll();
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