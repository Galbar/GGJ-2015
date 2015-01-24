#include "SoundManager.h"
using namespace hb;

std::unique_ptr<SoundManager> SoundManager::s_instance = nullptr;

SoundManager* SoundManager::instance()
{
	if (s_instance == nullptr)
		s_instance = std::unique_ptr<SoundManager>(new SoundManager());

	return s_instance.get();
}

int SoundManager::loadFromFile(const std::string& path)
{
	sf::SoundBuffer sb;
	if (!isLoaded(path))
		sb.loadFromFile(path);

	return this->addResource(path, sb);
}
