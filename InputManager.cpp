#include "InputManager.h"

InputManager* InputManager::s_instance = nullptr;

InputManager* InputManager::instance()
{
	if (s_instance == nullptr)
		s_instance = new InputManager();
	return s_instance;
}