#include <iostream>

#include "Scene/Scene.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "StateManager/StateManager.hpp"
#include "CommonImGui.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		StateManager::addState(StateId::menuState);
		ImGui::SFML::Shutdown();
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}