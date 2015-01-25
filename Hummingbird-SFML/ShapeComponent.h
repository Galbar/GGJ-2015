#ifndef HB_SHAPE_COMPONENT_H
#define HB_SHAPE_COMPONENT_H
#include <SFML/Graphics.hpp>
#include "../Hummingbird-Base.h"
#include "RenderWindowManager.h"

namespace hb
{
	class ShapeComponent : public GameObject::Component, public Transform
	{
	public:
		ShapeComponent(sf::Shape* s, RenderWindowManager* r);
		virtual ~ShapeComponent();

		void postUpdate() override;

		sf::Shape& getShape();
		const sf::Shape& getShape() const;
		void setShape(sf::Shape* s);

	private:
		sf::Shape* m_shape;
		bool m_visible;
		RenderWindowManager* m_render_manager;
	};
}


#endif