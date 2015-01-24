#include "PhysicsWorld.h"
using namespace hb;

PhysicsWorld* PhysicsWorld::s_instance = nullptr;


class MyRayCastCallback : public b2RayCastCallback
{
public:
	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;
	MyRayCastCallback()
	{
		m_fixture = NULL;
	}
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		return fraction;
	}
};


PhysicsWorld::PhysicsWorld(b2Vec2 gravity)
{
	world = new b2World(gravity);
	world->SetContactListener(this);
}


PhysicsWorld* PhysicsWorld::instance()
{
	if (s_instance == nullptr)
		s_instance = new PhysicsWorld(b2Vec2(0.0, 0.0));

	return s_instance;
}


void PhysicsWorld::clear()
{
	b2Vec2 gravity = s_instance->world->GetGravity();
	delete s_instance->world;
	s_instance->world = new b2World(gravity);
}


b2World* PhysicsWorld::getWorld()
{
	return world;
}


const b2World* PhysicsWorld::getWorld() const
{
	return world;
}


void PhysicsWorld::setGravity(Vector2d g)
{
	world->SetGravity(b2Vec2(g.x, g.y));
}


const Vector2d PhysicsWorld::getGravity()
{
	b2Vec2 v = world->GetGravity();
	return Vector2d(v.x, v.y);
}


b2Body* PhysicsWorld::addBody(b2BodyDef* bd)
{
	return world->CreateBody(bd);
}


void PhysicsWorld::BeginContact(b2Contact* contact)
{
	CollisionComponent* cA = (CollisionComponent*) contact->GetFixtureA()->GetBody()->GetUserData();
	CollisionComponent* cB = (CollisionComponent*) contact->GetFixtureB()->GetBody()->GetUserData();

	if (cA == nullptr || cB == nullptr) return;
	cA->addCollision(cB);
	cB->addCollision(cA);
}


void PhysicsWorld::update()
{
	world->Step(Time::deltaTime.asSeconds(), 8, 3);
}


float PhysicsWorld::GetRayCastDistance(b2Vec2 p1, b2Vec2 p2, b2Fixture*& fixt)
{
	MyRayCastCallback callback;
	b2Vec2 point1(p1.x, p1.y);
	b2Vec2 point2(p2.x, p2.y);
	world->RayCast(&callback, point1, point2);
	if (callback.m_fixture == NULL) return 123456;
	fixt = callback.m_fixture;
	return callback.m_fraction;
}
