#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H
#include "Hummingbird-Base.h"
#include "Hummingbird-Box2D.h"
#include "InputManager.h"
#include <vector>
#include <iostream>

using namespace hb;

class PlayerComponent : public GameObject::Component
{
public:
	PlayerComponent(int player_number, int max_hp, int cur_hp, bool alive, int run_speed, int jump_speed);
	~PlayerComponent();

	void update() override;
	int getXDir() const;

	static int current_player;
	static GameObject* active_player;

	class FootListener : public b2ContactListener
	{
		void BeginContact(b2Contact* contact) {
			
			//check if fixture A was the foot sensor
			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if (fixtureUserData != NULL)
				if (*(int*)fixtureUserData == 3 )
				{
					std::cerr << "CONTACTA" << std::endl;
					numFootContacts++;
					return;
				}

			//check if fixture B was the foot sensor
			fixtureUserData = contact->GetFixtureB()->GetUserData();
			if (fixtureUserData != NULL)
				if ( *(int*)fixtureUserData == 3 )
				{
					std::cerr << "CONTACTA" << std::endl;
					numFootContacts++;
					return;
				}
			
      }
  
        void EndContact(b2Contact* contact) {
			//check if fixture A was the foot sensor
			
			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if (fixtureUserData != NULL)
				if ( *(int*)fixtureUserData == 3 )
				{
					std::cerr << "CONTACTAAAA" << std::endl;
             		numFootContacts--;
             		return;
				}
		    //check if fixture B was the foot sensor
		    fixtureUserData = contact->GetFixtureB()->GetUserData();
		    if (fixtureUserData != NULL) 
		    	if ( *(int*)fixtureUserData == 3 )
		    	{
		    		std::cerr << "CONTACTAAAA" << std::endl;
            		numFootContacts--;
            		return;
		    	}
        }
	};

	FootListener* fl;
	static int numFootContacts;

private:
	//Player attributes
	int cur_hp;
	int max_hp;
	bool alive;
	bool active;

	int player_number;
	int run_speed;
	int jump_speed;

	// State attributes
	int xDir;
	int yDir;
	bool jumping;
	bool clickedJump;
	bool grounded;
	sf::Keyboard::Key last_key;


	InputManager::ListenerId<KeyPressed> listen_key_pressed;
	InputManager::ListenerId<KeyReleased> listen_key_released;
	InputManager::ListenerId<MouseButtonWindow> listen_mouse_window;
	InputManager::ListenerId<MouseButtonWorld> listen_mouse_world;

};


#endif