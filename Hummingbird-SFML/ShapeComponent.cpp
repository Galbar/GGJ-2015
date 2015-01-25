#include "ShapeComponent.h"

using namespace hb;

ShapeComponent::ShapeComponent(sf::Shape* s, RenderWindowManager* r):
GameObject::Component(),
m_shape(s),
m_visible(true),
m_render_manager(r)
{}


ShapeComponent::~ShapeComponent()
{
	delete m_shape;
}


sf::Shape& ShapeComponent::getShape()
{
	return *m_shape;
}


const sf::Shape& ShapeComponent::getShape() const
{
	return *m_shape;
}


void ShapeComponent::setShape(sf::Shape* s)
{
	m_shape = s;
}

void ShapeComponent::postUpdate()
{
	if (m_visible)
	{
		float x = getPosition().x + getGameObject()->getPosition().x;
		float y = getPosition().y + getGameObject()->getPosition().y;
		m_shape->setPosition(x, y);
		x = getScale().x * getGameObject()->getScale().x;
		y = getScale().y * getGameObject()->getScale().y;
		m_shape->setScale(x, y);
		x = getRotation().z + getGameObject()->getRotation().z;
		m_shape->setRotation(x);
		double z_index = getPosition().z + getGameObject()->getPosition().z;
		m_render_manager->addDrawable(std::pair<double, sf::Drawable*>(z_index, m_shape));
	}
}