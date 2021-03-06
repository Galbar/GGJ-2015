#ifndef HB_PHYSICS_WORLD_H
#define HB_PHYSICS_WORLD_H
#include <Box2D/Box2D.h>
#include "../Hummingbird-Base/Vector2d.h"
#include "../Hummingbird-Base/Time.h"
#include "CollisionComponent.h"

namespace hb
{
	class PhysicsWorld : public b2ContactListener
	{
	public:
		PhysicsWorld(b2Vec2 gravity);
		static PhysicsWorld* instance();
		static void clear();

		b2World* getWorld();
		const b2World* getWorld() const;

		void setGravity(Vector2d g);
		const Vector2d getGravity();

		b2Body* addBody(b2BodyDef* bd);

		void BeginContact(b2Contact *contact);

		void update();

		float GetRayCastDistance(b2Vec2 p1, b2Vec2 p2, b2Fixture *&fixt);

	private:
		static PhysicsWorld* s_instance;
		b2World* world;
	};
}
#endif