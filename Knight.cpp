#include "Knight.h"

Knight::Knight(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed):
Player(player_number, max_hp, cur_hp, alive, run_speed, jump_speed)
{
	Vector3d p = getPosition();

	// Adding logical component
	KnightComponent* kc = new KnightComponent();
	addComponent(kc);

	// Adding physics component
	b2BodyDef bodyDef;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.type = b2_dynamicBody;
	b2Body* body = PhysicsWorld::instance()->addBody(&bodyDef);
	body->SetLinearDamping(1.0f);
	body->SetGravityScale(2.5);
	b2Vec2 vertices[4];
	vertices[0].Set(-1,   1);
	vertices[1].Set(-1,  -1);
	vertices[2].Set( 1,  -1);
	vertices[3].Set( 1,   1);

	b2PolygonShape box;
	box.Set(vertices, 4);
	b2FixtureDef fixture;
	fixture.density = 2.0f;
	fixture.friction = 0.0f;
	fixture.shape = &box;
	fixture.restitution = 0.3f;
	body->SetFixedRotation(true);
	body->CreateFixture(&fixture);

	CollisionComponent* cc = new CollisionComponent(body);
	addComponent(cc);
}