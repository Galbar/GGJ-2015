#ifndef HB_SOUND_COMPONENT_H
#define HB_SOUND_COMPONENT_H
#include <string>
#include <SFML/Audio.hpp>
#include "../Hummingbird-Base/GameObject.h"
#include "../Hummingbird-Base/Transform.h"
#include "SoundManager.h"

namespace hb
{
	class SoundComponent : public GameObject::Component, public Transform
	{
	public:
		SoundComponent();
		virtual ~SoundComponent();
		void setSound(const std::string& sound_path);
		sf::Sound& getSound();
		const sf::Sound& getSound() const;
		void update() override;

	private:
		sf::Sound m_sound;
		int m_sound_id;
	};
}
#endif