#include <iostream>

#include "Scene/Scene.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "StateManager/StateManager.hpp"
#include "CommonImGui.hpp"
#include "Entity/Entity.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		Entity::init();
		StateManager::addState(StateId::menuState);
		ImGui::SFML::Shutdown();
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}