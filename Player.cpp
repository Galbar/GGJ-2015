#include "Player.h"

Player::Player(Vector3d init_pos, int player_number, bool controller, int controllerId):
GameObject(init_pos),
player_number(player_number)
{
	PlayerComponent* pc = new PlayerComponent(player_number, controller, controllerId);
	addComponent(pc);
	player_controller = pc;

	const Vector3d& p = getPosition();


	// Adding physics component
	b2BodyDef bodyDef;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.type = b2_dynamicBody;
	b2Body* body = PhysicsWorld::instance()->addBody(&bodyDef);
	body->SetLinearDamping(1.0f);
	body->SetGravityScale(2.5);
	b2Vec2 vertices[4];
	vertices[0].Set(-0.5,  0.5);
	vertices[1].Set(-0.5, -0.5);
	vertices[2].Set( 0.5, -0.5);
	vertices[3].Set( 0.5,  0.5);

	b2PolygonShape box;
	box.Set(vertices, 4);
	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.friction = 0.0f;
	fixture.shape = &box;
	fixture.restitution = 0.0f;
	body->SetFixedRotation(true);
	body->CreateFixture(&fixture);

	CollisionComponent* cc = new CollisionComponent(body);
	addComponent(cc);
}