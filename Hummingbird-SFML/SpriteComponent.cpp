#include "SpriteComponent.h"
#include <iostream>
using namespace hb;


SpriteComponent::SpriteComponent(RenderWindowManager* render_manager):
GameObject::Component(),
m_visible(true),
m_texture_id(-1),
m_render_manager(render_manager)
{}


SpriteComponent::~SpriteComponent()
{
	TextureManager::instance()->release(m_texture_id);
}


void SpriteComponent::setRenderWindowManager(RenderWindowManager* render_manager)
{
	m_render_manager = render_manager;
}


RenderWindowManager* SpriteComponent::getRenderWindowManager()
{
	return m_render_manager;
}


const RenderWindowManager* SpriteComponent::getRenderWindowManager() const
{
	return m_render_manager;
}


void SpriteComponent::setTexture(const std::string& path, const sf::IntRect& area)
{
	m_texture_id = TextureManager::instance()->loadFromFile(path, area);
	m_sprite.setTexture(TextureManager::instance()->get(m_texture_id));
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
}


sf::Sprite& SpriteComponent::getSprite()
{
	return m_sprite;
}


const sf::Sprite& SpriteComponent::getSprite() const
{
	return m_sprite;
}


bool SpriteComponent::isVisible() const
{
	return m_visible;
}


void SpriteComponent::setVisible(bool visible)
{
	m_visible = visible;
}


void SpriteComponent::postUpdate()
{
	if (m_visible)
	{
		float x = getPosition().x + getGameObject()->getPosition().x;
		float y = getPosition().y + getGameObject()->getPosition().y;
		m_sprite.setPosition(x, y);
		x = getScale().x * getGameObject()->getScale().x;
		y = getScale().y * getGameObject()->getScale().y;
		m_sprite.setScale(x, y);
		x = getRotation().z + getGameObject()->getRotation().z;
		m_sprite.setRotation(x);
		double z_index = getPosition().z + getGameObject()->getPosition().z;
		m_render_manager->addDrawable(std::pair<double, sf::Drawable*>(z_index, &m_sprite));
	}
}
