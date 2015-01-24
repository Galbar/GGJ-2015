#ifndef KNIGHT_COMPONENT_H
#define KNIGHT_COMPONENT_H
#include "Hummingbird-Base.h"

using namespace hb;

class KnightComponent : public GameObject::Component
{
public:
	KnightComponent();

	void update() override;
};

#endif