#ifndef HB_COLLISION_COMPONENT_H
#define HB_COLLISION_COMPONENT_H
#include <memory>
#include <Box2D/Box2D.h>
#include <queue>
#include "../Hummingbird-Base/DataComponent.h"
#include "../Hummingbird-Base/Transform.h"
#include "PhysicsWorld.h"

namespace hb
{
	class CollisionComponent : public DataComponent<b2Body*>, public Transform
	{
	public:
		CollisionComponent(b2Body* b);
		virtual ~CollisionComponent() override;
		
		void setBody(b2Body* b);
		const b2Body* getBody() const;

		std::queue<CollisionComponent*> getCollisionQueue();
		const Vector3d getPosition();

		void addCollision(CollisionComponent* b);

		void preUpdate() override;
		void postUpdate() override;

	private:
		Vector3d pos;
		std::queue<CollisionComponent*> cqueue;
	};
}
#endif