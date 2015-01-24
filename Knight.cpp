#include "Knight.h"

Knight::Knight(Vector3d init_pos, int player_number, bool controller, int controllerId):
Player(init_pos, player_number, controller, controllerId)
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

	box.SetAsBox(0.5, 0.3, b2Vec2(0,-0.4), 0);
	fixture.isSensor = true;
	b2Fixture* footSensorFixture = body->CreateFixture(&fixture);
	footSensorFixture->SetUserData( (void*)3 );

	CollisionComponent* cc = new CollisionComponent(body);
	addComponent(cc);

}
