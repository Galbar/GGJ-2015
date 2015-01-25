#include "CollisionComponent.h"
#include <iostream>

using namespace hb;

CollisionComponent::CollisionComponent(b2Body* b):
DataComponent<b2Body*>(b)
{
	b->SetUserData(this);
}


CollisionComponent::~CollisionComponent()
{
	std::cerr << "hai_lol" << std::endl;
	PhysicsWorld::instance()->getWorld()->DestroyBody(getData());
	std::cerr << "hai_lol" << std::endl;
}


void CollisionComponent::setBody(b2Body* b)
{
	setData(b);
}


std::queue<CollisionComponent*>& CollisionComponent::getCollisionQueue()
{
	return cqueue;
}


b2Body* CollisionComponent::getBody()
{
	return getData();
}


const b2Body* CollisionComponent::getBody() const
{
	return getData();
}


const Vector3d CollisionComponent::getPosition()
{
	return pos;
}


void CollisionComponent::addCollision(CollisionComponent* b)
{
	cqueue.push(b);
}


void CollisionComponent::preUpdate()
{
	b2Body* b = getData();
	pos = Vector3d(b->GetPosition().x, b->GetPosition().y, 0);
}


void CollisionComponent::postUpdate()
{
	while (!cqueue.empty()) cqueue.pop();
}