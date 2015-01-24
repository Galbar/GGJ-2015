#ifndef KNIGHT_H
#define KNIGHT_H
#include "Player.h"
#include "KnightComponent.h"
#include "Hummingbird-SFML.h"
#include "Hummingbird-Box2D.h"

class Knight : public Player
{
public:
	Knight(Vector3d init_pos, int player_number, bool controller, int controllerId);


private:
	hb::AnimatedSpriteComponent* sc;
};

#endif