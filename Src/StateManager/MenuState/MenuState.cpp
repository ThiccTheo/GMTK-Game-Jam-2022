#include <memory>

#include "MenuState.hpp"
#include "../../Scene/Scene.hpp"
#include "../StateManager.hpp"

void MenuState::init()
{
}

void MenuState::run()
{
	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		switch (e.type)
		{
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Space)
				{
					addState(StateId::gameState);
				}
				break;
		}

		Scene::window.setView(Scene::window.getDefaultView());
		Scene::window.clear();
		Scene::window.display();
	}
}
