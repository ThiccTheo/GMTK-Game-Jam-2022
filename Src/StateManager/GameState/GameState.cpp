#include <utility>
#include <cmath>

#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Tile/Tile.hpp"
#include "CommonImGui.hpp"

void GameState::init()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
	camera.zoom(0.5);

	loadLevel();
}

void GameState::run()
{
	float deltaTime;
	sf::Clock deltaClock;

	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };
		ImGui::SFML::ProcessEvent(e);

		deltaTime = deltaClock.restart().asSeconds();

		ImGui::SFML::Update(Scene::window, sf::seconds(deltaTime));

		Tile::update();
		Player::update(deltaTime, e);
		updateCamera(deltaTime);
		Scene::window.setView(camera);
		Scene::window.clear(sf::Color::White);
		Tile::draw();
		Player::draw();

		ImGui::SFML::Render(Scene::window);
		Scene::window.display();
	}
}

void GameState::updateCamera(const float deltaTime)
{
	const auto& [playerX, playerY] { Player::player.body.getPosition() };
	const auto& [cameraX, cameraY] { camera.getCenter() };

	//direct follow
	//camera.setCenter
	//(
	//	std::clamp(playerX, 0.f, 1000.f), //test values
	//	std::clamp(playerY, 0.f, 1000.f)  //test values
	//);

	//lerping
	camera.setCenter
	(
		std::clamp(std::lerp(cameraX, playerX, 10.f * deltaTime), 0.f, 10000.f), //test values
		std::clamp(std::lerp(cameraY, playerY, 10.f * deltaTime), 0.f, 10000.f)  //test values
	);
}

void GameState::loadLevel()
{
	Player player(sf::Vector2i(10, 10));
	Player::player = player;

	for (int y{ 0 }; y < 100; y++)
	{
		for (int x{ 0 }; x < 100; x++)
		{
			if (x != 1)
			{
				Tile::tiles.emplace_back(sf::Vector2i(x, y));
			}
		}
	}
}