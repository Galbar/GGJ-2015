#ifndef HB_SOUND_MANAGER
#define HB_SOUND_MANAGER
#include <string>
#include <memory>
#include <SFML/Audio.hpp>
#include "../Hummingbird-Base/ResourceManager.h"

namespace hb
{
	class SoundManager : public ResourceManager<sf::SoundBuffer, std::string>
	{
	public:
		static SoundManager* instance();
		int loadFromFile(const std::string& path);

	private:
		static std::unique_ptr<SoundManager> s_instance;
	};
}
#endif