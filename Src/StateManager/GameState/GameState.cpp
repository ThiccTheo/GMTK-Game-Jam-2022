#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Entity/Player/Player.hpp"

void GameState::init()
{
	Player player(sf::Vector2i(10, 10));
	Player::player = player;
}

void GameState::run()
{
	float deltaTime;
	sf::Clock dtClock;

	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		deltaTime = dtClock.restart().asSeconds();

		Player::update(deltaTime, e);

		Scene::window.setView(Scene::window.getDefaultView());
		Scene::window.clear();
		Player::draw();
		Scene::window.display();
	}
}
