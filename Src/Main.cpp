#include <iostream>

#include "Scene/Scene.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "StateManager/StateManager.hpp"
#include "StateManager/MenuState/MenuState.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		StateManager::states.emplace(std::make_unique<MenuState>());
		StateManager::checkState();
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}