#include <iostream>

#include "Scene/Scene.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "StateManager/StateManager.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		StateManager::addState(StateId::menuState);
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}