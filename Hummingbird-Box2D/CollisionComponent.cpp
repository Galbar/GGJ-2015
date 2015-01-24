#include "CollisionComponent.h"

using namespace hb;

CollisionComponent::CollisionComponent(b2Body* b):
DataComponent<b2Body*>(b)
{
	b->SetUserData(this);
}


CollisionComponent::~CollisionComponent()
{
	PhysicsWorld::instance()->getWorld()->DestroyBody(getData());
}


void CollisionComponent::setBody(b2Body* b)
{
	setData(b);
}


std::queue<CollisionComponent*> CollisionComponent::getCollisionQueue()
{
	return cqueue;
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