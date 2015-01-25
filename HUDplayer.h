#ifndef HUDPLAYER_H
#define HUDPLAYER_H
#include "HUD.h"
#include "HUDplayerComponent.h"
#include "Player.h"

using namespace hb;

class HUDplayer : public HUD
{
public:
	HUDplayer(Player* p, RenderWindowManager* r);

private:
	Player* player;
};

#endif