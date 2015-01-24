#ifndef HB_SPRITE_COMPONENT_H
#define HB_SPRITE_COMPONENT_H
#include <SFML/Graphics.hpp>
#include "RenderWindowManager.h"
#include "../Hummingbird-Base/GameObject.h"
#include "../Hummingbird-Base/Transform.h"
#include "TextureManager.h"

namespace hb
{
	class SpriteComponent : public GameObject::Component, public Transform
	{
	public:
		SpriteComponent(RenderWindowManager* render_manager);
		virtual ~SpriteComponent() override;
		void setRenderWindowManager(RenderWindowManager* render_manager);
		RenderWindowManager* getRenderWindowManager();
		const RenderWindowManager* getRenderWindowManager() const;
		virtual void setTexture(const std::string& path, const sf::IntRect& area = sf::IntRect());
		sf::Sprite& getSprite();
		const sf::Sprite& getSprite() const;
		bool isVisible() const;
		void setVisible(bool visible);
		virtual void postUpdate() override;

	protected:
		bool m_visible;
		sf::Sprite m_sprite;
		int m_texture_id;
		RenderWindowManager* m_render_manager;
	};
}
#endif