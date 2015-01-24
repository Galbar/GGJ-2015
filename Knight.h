#ifndef KNIGHT_H
#define KNIGHT_H
#include "Player.h"
#include "KnightComponent.h"
#include "Hummingbird-SFML.h"
#include "Hummingbird-Box2D.h"

class Knight : public Player
{
public:
	Knight(Vector3d init_pos, int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed);
	void setAnimatedSprite(hb::AnimatedSpriteComponent* sc);

private:
	hb::AnimatedSpriteComponent* sc;
};

#endif