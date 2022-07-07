#include <memory>

#include "MenuState.hpp"
#include "../../Scene/Scene.hpp"
#include "../GameState/GameState.hpp"

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
					states.emplace(std::make_unique<GameState>());
					checkState();
				}
				break;
		}

		Scene::window.setView(Scene::window.getDefaultView());
		Scene::window.clear();
		Scene::window.display();
	}
}
