#include "Scene.h"

Scene::Scene(hb::RenderWindowManager* window_manager, levels lvl)
{
	m_tilemap_obj = new hb::GameObject();
	sf::Image tilemap;
	tilemap.loadFromFile(getLevelPath(lvl));
	sf::Vector2u size = tilemap.getSize();
	m_tilemap_obj->setPosition(hb::Vector3d(0, 0, -1000));

	bool in_collider = false;
	hb::Vector2d collider_begin;
	for (unsigned int j = 0; j < size.y; ++j)
	{
		for (unsigned int i = 0; i < size.x; ++i)
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
				if ((j != 0 and tilemap.getPixel(i, j - 1).r < 122) or (j != size.y and tilemap.getPixel(i, j + 1).r < 122))
				{
					if (not in_collider)
					{
						in_collider = true;
						collider_begin = hb::Vector2d(i, j);
					}
				}
				else if (in_collider)
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox((i - collider_begin.x) / 2, 0.5); //a 4x2 rectangle
					myBodyDef.position.Set((i + collider_begin.x) / 2, j + 0.5); //a bit to the right

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
			collider_shape.SetAsBox((size.x - collider_begin.x) / 2, 0.5); //a 4x2 rectangle
			myBodyDef.position.Set((size.x + collider_begin.x) / 2, j + 0.5); //a bit to the right

			b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &collider_shape;
			body->CreateFixture(&myFixtureDef); //add a fixture to the body
		}
	}

	in_collider = false;
	for (unsigned int i = 0; i < size.x; ++i)
	{
		for (unsigned int j = 0; j < size.y; ++j)
		{
			if (tilemap.getPixel(i, j).r >= 122)
			{
				if ((i != 0 and tilemap.getPixel(i - 1, j).r < 122) or (i != size.x and tilemap.getPixel(i + 1, j).r < 122))
				{
					if (not in_collider)
					{
						in_collider = true;
						collider_begin = hb::Vector2d(i, j);
					}
				}
				else if (in_collider)
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(0.5, (j - collider_begin.y) / 2); //a 4x2 rectangle
					myBodyDef.position.Set(i + 0.5, (j + collider_begin.y) / 2); //a bit to the right

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
			collider_shape.SetAsBox(0.5, (size.y - collider_begin.y) / 2); //a 4x2 rectangle
			myBodyDef.position.Set(i + 0.5, (size.y + collider_begin.y) / 2); //a bit to the right

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