#include "PhysicsWorld.h"
using namespace hb;

PhysicsWorld* PhysicsWorld::s_instance = nullptr;

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


	cA->addCollision(cB);
	cB->addCollision(cA);
}


void PhysicsWorld::update()
{
	world->Step(Time::deltaTime.asSeconds(), 8, 3);
}