#include <utility>

#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Tile/Tile.hpp"

void GameState::init()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
	camera.zoom(0.5);
	Player player(sf::Vector2i(10, 10));
	Player::player = player;

	for (int y{ 0 }; y < 100; y++)
	{
		for (int x{ 0 }; x < 100; x++)
		{
			Tile::tiles.emplace_back(sf::Vector2i(x, y));
		}
	}
}

void GameState::run()
{
	float deltaTime;
	sf::Clock dtClock;

	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		deltaTime = dtClock.restart().asSeconds();

		Tile::update();
		Player::update(deltaTime, e);
		centerCamera();
		Scene::window.setView(camera);
		Scene::window.clear(sf::Color::White);
		Tile::draw();
		Player::draw();
		Scene::window.display();
	}
}

void GameState::centerCamera()
{
	auto& [x, y] { Player::player.body.getPosition() };

	camera.setCenter(x, y);
}
