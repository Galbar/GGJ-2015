#include <iostream>
#include "Scene.h"

bool pixel_is_corner(const sf::Image& img, int x, int y)
{
	sf::Vector2u size = img.getSize();
	if (x != (int)size.x -1 and img.getPixel(x+1, y) == sf::Color::Black and y != (int)size.y-1 and img.getPixel(x, y+1) == sf::Color::Black)
		return true;
	if (x != (int)size.x -1 and img.getPixel(x+1, y) == sf::Color::Black and y != 0 and img.getPixel(x, y-1) == sf::Color::Black)
		return true;
	if (x != 0 and img.getPixel(x-1, y) == sf::Color::Black and y != (int)size.y-1 and img.getPixel(x, y+1) == sf::Color::Black)
		return true;
	if (x != 0 and img.getPixel(x-1, y) == sf::Color::Black and y != 0 and img.getPixel(x, y-1) == sf::Color::Black)
		return true;
	return false;
}

Scene::Scene(hb::RenderWindowManager* window_manager, levels lvl):
m_i(0),
m_window_manager(window_manager)
{
	loadFragment(getLevelPath(), m_window_manager);
}


Scene::~Scene()
{
	hb::GameObject::destroyAll();
	hb::TextureManager::instance()->clear();
	hb::SoundManager::instance()->clear();
}


void Scene::loadFragment(std::string path, hb::RenderWindowManager* window_manager)
{
	std::cout << "Cargando fragmento: " << path << std::endl;
	sf::Image tilemap;
	tilemap.loadFromFile(path);
	sf::Vector2u size = tilemap.getSize();
	hb::GameObject* tilemap_obj = new hb::GameObject();
	tilemap_obj->setPosition(hb::Vector3d(0.5, 0, -1000));
	hb::GameObject* lava_fields = new hb::GameObject();
	//lava_fields->setName("Lava");
	std::queue<b2Body*> curr_b2Body_queue;

	bool in_collider = false;
	hb::Vector2d collider_begin;
	for (unsigned int j = 0; j < size.y; ++j)
	{
		bool in_lava_pool = false;
		hb::Vector2d lava_pool_begin;
		for (unsigned int i = 0; i < size.x; ++i)
		{
			std::cout << "Pixel (" << i << ", " << j << "): (";
			std::cout << (int)tilemap.getPixel(i, j).r << ", " << (int)tilemap.getPixel(i, j).g << ", " << (int)tilemap.getPixel(i, j).b << ")";
			hb::SpriteComponent* t;
			t = new hb::SpriteComponent(window_manager);
			//t->setTexture("tilemap.png", sf::IntRect(138, 308, 32, 32));
			t->setTexture("tilemap.png", sf::IntRect(274, 410, 32, 32));

			if (tilemap.getPixel(i, j) != sf::Color::White) // if background
			{
				std::cout << "\tEs fondo" << std::endl;
				if (in_collider)
				{
					std::cout << "\tTermina colider";
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					std::cout << "\t w/h: (" << ((double)(m_i + i) - collider_begin.x) / 2.0 << " / " << 0.5 << ")";
					std::cout << "\t x/y: (" << ((double)(m_i + i) + collider_begin.x) / 2.0 << " / " << collider_begin.y + 0.5 <<  ")";
					collider_shape.SetAsBox(((double)(m_i + i) - collider_begin.x) / 2.0, 0.5); //a 4x2 rectangle
					myBodyDef.position.Set(((double)(m_i + i) + collider_begin.x) / 2.0, collider_begin.y + 0.5); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					curr_b2Body_queue.push(body);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef);

				}
			}
			else if (tilemap.getPixel(i, j) == sf::Color::White)
			{
				std::cout << "\tEs frente";
				t->setTexture("tilemap.png", sf::IntRect(548, 240, 32, 32));
				//t->setTexture("tilemap.png", sf::IntRect(36, 308, 32, 32));
				if (((j != 0 and tilemap.getPixel(i, j - 1) == sf::Color::Black) or (j != size.y-1 and tilemap.getPixel(i, j + 1) == sf::Color::Black)) and not in_collider)
				{
					std::cout << "\tEmpieza colider";
					in_collider = true;
					collider_begin = hb::Vector2d((m_i + i), j);

				}
				else if (in_collider and not ((j != 0 and tilemap.getPixel(i, j - 1) == sf::Color::Black) or (j != size.y-1 and tilemap.getPixel(i, j + 1) == sf::Color::Black)))
				{
					std::cout << "\tTermina colider";
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					std::cout << "\t w/h: (" << ((double)(m_i + i) - collider_begin.x) / 2.0 << " / " << 0.5 << ")";
					std::cout << "\t x/y: (" << ((double)(m_i + i) + collider_begin.x) / 2.0 << " / " << collider_begin.y + 0.5 <<  ")";
					collider_shape.SetAsBox(((double)(m_i + i) - collider_begin.x) / 2.0, 0.5); //a 4x2 rectangle
					myBodyDef.position.Set(((double)(m_i + i) + collider_begin.x) / 2.0, collider_begin.y + 0.5); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					curr_b2Body_queue.push(body);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef); //add a fixture to the body
				}
			}

			if (in_lava_pool and tilemap.getPixel(i, j) != sf::Color(255, 0, 0))
			{
				in_lava_pool = false;
				b2BodyDef myBodyDef;
				myBodyDef.type = b2_staticBody;

				b2PolygonShape collider_shape;
				collider_shape.SetAsBox(((double)(m_i + i) - collider_begin.x) / 2.0 -1, 0.25); //a 4x2 rectangle
				myBodyDef.position.Set(((double)(m_i + i) + collider_begin.x) / 2.0, collider_begin.y + 0.75); //a bit to the right

				b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
				curr_b2Body_queue.push(body);
				b2FixtureDef myFixtureDef;
				myFixtureDef.shape = &collider_shape;
				myFixtureDef.isSensor = true;
				body->CreateFixture(&myFixtureDef);
				hb::CollisionComponent* cc = new hb::CollisionComponent(body);
				lava_fields->addComponent(cc);
			}

			if (tilemap.getPixel(i, j) == sf::Color(255, 0, 0))
			{
				hb::AnimatedSpriteComponent* at = new hb::AnimatedSpriteComponent(window_manager);
				at->setTexture("tilemap.png", sf::IntRect(512, 136, 275, 70));
				if (j == 0 or tilemap.getPixel(i, j - 1) != sf::Color(255, 0, 0))
				{
					if (not in_lava_pool)
					{
						in_lava_pool = true;
						lava_pool_begin = hb::Vector2d((m_i + i), j);
					}
					at->setFrameSize(hb::Vector2d(32, 32));
					at->setFrameInterval(0, 6);
					at->setFrameTime(hb::Time::seconds(0.3));
					at->setFrameMargin(hb::Vector2d(2, 2));
					at->setPosition(hb::Vector3d(at->getPosition().x, at->getPosition().y, 1000));
				}
				else
				{
					at->setFrameSize(hb::Vector2d(32, 32));
					at->setFrameInterval(8, 14);
					at->setFrameTime(hb::Time::seconds(0.3));
					at->setFrameMargin(hb::Vector2d(2, 2));
					at->setPosition(hb::Vector3d(at->getPosition().x, at->getPosition().y, 1000));
				}
				at->setPosition(hb::Vector3d(32 * (m_i + i), 32 * j , 1000));
				tilemap_obj->addComponent(at);
			}
			t->setPosition(hb::Vector3d(32 * (m_i + i), 32 * j , -999));
			tilemap_obj->addComponent(t);

		}
		if (in_collider)
		{
			std::cout << "\tTermina colider";
			in_collider = false;
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody;

			b2PolygonShape collider_shape;
			collider_shape.SetAsBox(((double)(m_i + size.x) - collider_begin.x) / 2.0, 0.5); //a 4x2 rectangle
			myBodyDef.position.Set(((double)(m_i + size.x) + collider_begin.x) / 2.0, collider_begin.y + 0.5); //a bit to the right

			b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
			curr_b2Body_queue.push(body);
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &collider_shape;
			body->CreateFixture(&myFixtureDef); //add a fixture to the body
		}
		std::cout << std::endl;
	}

	for (unsigned int i = 0; i < size.x; ++i)
	{
		bool in_lava_column = false;
		hb::Vector2d lava_column_begin;
		for (unsigned int j = 0; j < size.y; ++j)
		{
			if (in_lava_column and tilemap.getPixel(i, j) != sf::Color(127, 0, 0))
			{
				in_lava_column = false;
				b2BodyDef myBodyDef;
				myBodyDef.type = b2_staticBody;

				b2PolygonShape collider_shape;
				collider_shape.SetAsBox(0.5, ((double)j - lava_column_begin.y) / 2.0); //a 4x2 rectangle
				myBodyDef.position.Set(lava_column_begin.x + 0.5, ((double)j + lava_column_begin.y) / 2.0); //a bit to the right

				b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
				curr_b2Body_queue.push(body);
				b2FixtureDef myFixtureDef;
				myFixtureDef.shape = &collider_shape;
				myFixtureDef.isSensor = true;
				body->CreateFixture(&myFixtureDef);
				hb::CollisionComponent* cc = new hb::CollisionComponent(body);
				lava_fields->addComponent(cc);
			}

			hb::SpriteComponent* t = nullptr;
			if (tilemap.getPixel(i, j).r <= 7 and tilemap.getPixel(i, j).r >= 0 and tilemap.getPixel(i, j).g == 255 and tilemap.getPixel(i, j).b == 255)
			{
				hb::AnimatedSpriteComponent* at = new hb::AnimatedSpriteComponent(window_manager);
				at->setTexture("tilemap.png", sf::IntRect(102, 170, 272, 36));
				at->setFrameInterval(tilemap.getPixel(i, j).r, tilemap.getPixel(i, j).r);
				at->setFrameSize(hb::Vector2d(32, 32));
				at->setFrameMargin(hb::Vector2d(2, 2));
				hb::Vector3d p = at->getPosition();
				p.z = 1000;
				at->setPosition(p);
				t = at;
			}
			else if (tilemap.getPixel(i, j) == sf::Color(127, 0, 0))
			{
				if (j == 0 or tilemap.getPixel(i, j - 1) != sf::Color(127, 0, 0))
				{
					in_lava_column = true;
					lava_column_begin = hb::Vector2d((m_i + i), j);
					hb::AnimatedSpriteComponent* at = new hb::AnimatedSpriteComponent(window_manager);
					at->setTexture("tilemap.png", sf::IntRect(512, 0, 275, 70));
					at->setFrameSize(hb::Vector2d(32, 32));
					at->setFrameInterval(0, 15);
					at->setFrameTime(hb::Time::seconds(0.3));
					at->setFrameMargin(hb::Vector2d(2, 2));
					at->setPosition(hb::Vector3d(at->getPosition().x, at->getPosition().y, 1000));
					t = at;
				}
				else
				{
					hb::AnimatedSpriteComponent* at = new hb::AnimatedSpriteComponent(window_manager);
					at->setTexture("tilemap.png", sf::IntRect(512, 68, 275, 70));
					at->setFrameSize(hb::Vector2d(32, 32));
					at->setFrameInterval(0, 15);
					at->setFrameTime(hb::Time::seconds(0.3));
					at->setFrameMargin(hb::Vector2d(2, 2));
					at->setPosition(hb::Vector3d(at->getPosition().x, at->getPosition().y, 1000));
					t = at;
				}
			}
			else if (tilemap.getPixel(i, j) == sf::Color::Black)	// if background
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
					curr_b2Body_queue.push(body);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef);

				}
			}
			else if (tilemap.getPixel(i, j) == sf::Color::White)
			{
				if ((((m_i + i) != 0 and tilemap.getPixel(i - 1, j) == sf::Color::Black) or ((m_i + i) != size.x-1 and tilemap.getPixel(i + 1, j) == sf::Color::Black)) and not in_collider)
				{
					if (not pixel_is_corner(tilemap, (m_i + i), j))
					{
						in_collider = true;
						collider_begin = hb::Vector2d((m_i + i), j);
					}

				}
				else if (in_collider and not (((m_i + i) != 0 and tilemap.getPixel(i - 1, j) == sf::Color::Black) or ((m_i + i) != size.x-1 and tilemap.getPixel(i + 1, j) == sf::Color::Black)))
				{
					in_collider = false;
					b2BodyDef myBodyDef;
					myBodyDef.type = b2_staticBody;

					b2PolygonShape collider_shape;
					collider_shape.SetAsBox(0.5, ((double)j - collider_begin.y) / 2.0); //a 4x2 rectangle
					myBodyDef.position.Set(collider_begin.x + 0.5, ((double)j + collider_begin.y) / 2.0); //a bit to the right

					b2Body* body = hb::PhysicsWorld::instance()->addBody(&myBodyDef);
					curr_b2Body_queue.push(body);
					b2FixtureDef myFixtureDef;
					myFixtureDef.shape = &collider_shape;
					body->CreateFixture(&myFixtureDef); //add a fixture to the body
				}
			}
			if (t != nullptr)
			{
				t->setPosition(hb::Vector3d(32 * (m_i + i), 32 * j , t->getPosition().z));
				tilemap_obj->addComponent(t);
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
			curr_b2Body_queue.push(body);
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &collider_shape;
			body->CreateFixture(&myFixtureDef); //add a fixture to the body
		}
	}
	m_i += size.x;
	m_b2Fragments.push(curr_b2Body_queue);
	m_tilemap_objs.push(tilemap_obj);
	m_lava_fields.push(lava_fields);
}


void Scene::update()
{
	auto players = hb::GameObject::getGameObjectsByName("player");
	double max;
	for (int i = 0; i < players.size(); ++i)
	{
		if (i == 0)
			max = players[i]->getPosition().x;
		else
			if (max < players[i]->getPosition().x)
				max = players[i]->getPosition().x;
	}
	if (max > m_i * 32.0 - 50.0 *32.0)
	{
		std::cout << "Cargando nuevo fragmento" << std::endl;
		std::cout << m_b2Fragments.size() << std::endl;
		loadFragment(getLevelPath(), m_window_manager);
	}
	if (m_b2Fragments.size() > 3)
	{
		std::cout << "Eliminando bdBodies viejos" << std::endl;
		std::cout << m_b2Fragments.size() << std::endl;
		/*auto q = m_b2Fragments.front();
		m_b2Fragments.pop();
		while (not q.empty())
		{
			b2Body* b = q.front();
			q.pop();
			hb::PhysicsWorld::instance()->getWorld()->DestroyBody(b);
		}
		hb::GameObject* o = m_tilemap_objs.front();
		m_tilemap_objs.pop();
		std::cout << "tamaaaaaaaaaanyo " << o->getComponents<hb::GameObject::Component>().size() << std::endl;
		delete o;
		if (m_lava_fields.empty()) return;
		hb::GameObject* l = m_lava_fields.front();
		m_lava_fields.pop();
		std::cout << "tamaaaaaaaaaanyo " << l->getComponents<hb::CollisionComponent>().size() << std::endl;
		delete l;*/
	}
	hb::GameObject::updateAll();
}


std::string Scene::getLevelPath()
{
	std::vector<std::string> v(5);
	v[0] = "lvl-part0.png";
	v[1] = "lvl-part1.png";
	v[2] = "lvl-part2.png";
	v[3] = "lvl-part3.png";
	v[4] = "lvl-part4.png";

	//return v[1];
	return v[rand() % 5];
}