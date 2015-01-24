#include "Scene.h"

bool pixel_is_corner(const sf::Image& img, int x, int y)
{
	sf::Vector2u size = img.getSize();
	if (x != size.x -1 and img.getPixel(x+1, y).r < 122 and y != size.y-1 and img.getPixel(x, y+1).r < 122)
		return true;
	if (x != size.x -1 and img.getPixel(x+1, y).r < 122 and y != 0 and img.getPixel(x, y-1).r < 122)
		return true;
	if (x != 0 and img.getPixel(x-1, y).r < 122 and y != size.y-1 and img.getPixel(x, y+1).r < 122)
		return true;
	if (x != 0 and img.getPixel(x-1, y).r < 122 and y != 0 and img.getPixel(x, y-1).r < 122)
		return true;
	return false;
}

Scene::Scene(hb::RenderWindowManager* window_manager, levels lvl)
{
	m_tilemap_obj = new hb::GameObject();
	sf::Image tilemap;
	tilemap.loadFromFile(getLevelPath(lvl));
	sf::Vector2u size = tilemap.getSize();
	m_tilemap_obj->setPosition(hb::Vector3d(0.5, 0, -1000));

	bool in_collider = false;
	hb::Vector2d collider_begin;
	for (unsigned int j = 0; j < size.y; ++j)
	{
		for (unsigned int i = 0; i < size.x; ++i)
		{
			hb::SpriteComponent* t;
			t = new hb::SpriteComponent(window_manager);
			if (tilemap.getPixel(i, j) == sf::Color::Black) // if background
			{
				t->setTexture("tilemap.png", sf::IntRect(138, 308, 32, 32));
				if (in_collider)
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(((double)i - collider_begin.x) / 2.0, 0.5); //a 4x2 rectangle
					myBodyDef.position.Set(((double)i + collider_begin.x) / 2.0, collider_begin.y + 0.5); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef);

				}
			}
			else if (tilemap.getPixel(i, j) == sf::Color::White)
			{
				t->setTexture("tilemap.png", sf::IntRect(36, 308, 32, 32));
				if (((j != 0 and tilemap.getPixel(i, j - 1).r < 122) or (j != size.y-1 and tilemap.getPixel(i, j + 1).r < 122)) and not in_collider)
				{
					in_collider = true;
					collider_begin = hb::Vector2d(i, j);

				}
				else if (in_collider and not ((j != 0 and tilemap.getPixel(i, j - 1).r < 122) or (j != size.y-1 and tilemap.getPixel(i, j + 1).r < 122)))
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(((double)i - collider_begin.x) / 2.0, 0.5); //a 4x2 rectangle
					myBodyDef.position.Set(((double)i + collider_begin.x) / 2.0, collider_begin.y + 0.5); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef); //add a fixture to the body
				}
			}
			t->setPosition(hb::Vector3d(32 * i, 32 * j , 0));
			m_tilemap_obj->addComponent(t);

		}
		if (in_collider)
		{
			in_collider = false;
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody;

			b2PolygonShape collider_shape;
			collider_shape.SetAsBox(((double)size.x - collider_begin.x) / 2.0, 0.5); //a 4x2 rectangle
			myBodyDef.position.Set(((double)size.x + collider_begin.x) / 2.0, collider_begin.y + 0.5); //a bit to the right

			b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &collider_shape;
			body->CreateFixture(&myFixtureDef); //add a fixture to the body
		}
	}

	for (unsigned int i = 0; i < size.x; ++i)
	{
		for (unsigned int j = 0; j < size.y; ++j)
		{
			if (tilemap.getPixel(i, j) == sf::Color::Black)// if background
			{
				if (in_collider)
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(0.5, ((double)j - collider_begin.y) / 2.0); //a 4x2 rectangle
					myBodyDef.position.Set(collider_begin.x + 0.5, ((double)j + collider_begin.y) / 2.0); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef);

				}
			}
			else if (tilemap.getPixel(i, j) == sf::Color::White)
			{
				if (((i != 0 and tilemap.getPixel(i - 1, j).r < 122) or (i != size.x-1 and tilemap.getPixel(i + 1, j).r < 122)) and not in_collider)
				{
					if (not pixel_is_corner(tilemap, i, j))
					{
						in_collider = true;
						collider_begin = hb::Vector2d(i, j);
					}

				}
				else if (in_collider and not ((i != 0 and tilemap.getPixel(i - 1, j).r < 122) or (i != size.x-1 and tilemap.getPixel(i + 1, j).r < 122)))
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(0.5, ((double)j - collider_begin.y) / 2.0); //a 4x2 rectangle
					myBodyDef.position.Set(collider_begin.x + 0.5, ((double)j + collider_begin.y) / 2.0); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef); //add a fixture to the body
				}
			}
		}
		if (in_collider)
		{
			in_collider = false;
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody;

			b2PolygonShape collider_shape;
					collider_shape.SetAsBox(0.5, ((double)size.y - collider_begin.y) / 2.0); //a 4x2 rectangle
					myBodyDef.position.Set(collider_begin.x + 0.5, ((double)size.y + collider_begin.y) / 2.0); //a bit to the right

			b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &collider_shape;
			body->CreateFixture(&myFixtureDef); //add a fixture to the body
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