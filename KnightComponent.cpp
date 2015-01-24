#include "KnightComponent.h"

KnightComponent::KnightComponent():
GameObject::Component(),
m_player_component(nullptr)
{
	m_listener_id = InputManager::instance()->listen([this](const KeyPressed& e)
	{
		if (e.code == sf::Keyboard::Key::Space)
		{
			if (m_player_component == nullptr)
			{
				m_player_component = getGameObject()->getComponents<PlayerComponent>()[0];
			}
			b2RayCastInput input;
			hb::Vector3d to = getGameObject()->getPosition() + hb::Vector3d(0, m_player_component->getXDir(), 0);
			input.p1 = b2Vec2(getGameObject()->getPosition().x, getGameObject()->getPosition().y);
			input.p2 = b2Vec2(to.x, to.y);
			input.maxFraction = 2;
			b2Fixture* fixt = NULL;
			float dist = PhysicsWorld::instance()->GetRayCastDistance(input.p1, input.p2, fixt);
			if (fixt != NULL)
			{
				fixt->GetBody()->SetLinearVelocity(b2Vec2(50, 0));
			}
		}
	});

}

void KnightComponent::update()
{

}

KnightComponent::~KnightComponent()
{
	InputManager::instance()->ignore(m_listener_id);
}