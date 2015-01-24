#include "InputManager.h"

std::unique_ptr<InputManager> InputManager::s_instance = nullptr;

InputManager* InputManager::instance()
{
	if (s_instance == nullptr)
		s_instance = std::unique_ptr<InputManager>(new InputManager());
	return s_instance.get();
}
