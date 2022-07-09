#include <utility>

#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "CommonImGui.hpp"
#include "../Tile/Tile.hpp"

Player Player::player;
const sf::Vector2f Player::bodySize{ 16.f, 16.f };
sf::Vector2f Player::terminalVelocity{ 140.f, 350.f };
float Player::moveSpeed{ 25.f };
float Player::jumpPower{ 80.f };
float Player::gravity{ 100.f };
float Player::friction{ 10.f };

Player::Player() = default;

Player::Player(const sf::Vector2i& indices) : Entity(indices, bodySize, OriginSpot::middleCenter)
{
	isGrounded = false;
	velocity = sf::Vector2f(0.f, 0.f);
	normalizedDirection = sf::Vector2i(1, 0);
}

void Player::update(const float deltaTime, const sf::Event& e)
{
	ImGui::Begin("Player Settings");
	ImGui::SliderFloat("Gravity", &gravity, 0.f, 100.f);
	ImGui::SliderFloat("Friction", &friction, 0.f, 10.f);
	ImGui::SliderFloat("Terminal Velocity X", &terminalVelocity.x, 0.f, 10000.f);
	ImGui::SliderFloat("Terminal Velocity Y", &terminalVelocity.y, 0.f, 10000.f);
	ImGui::SliderFloat("Move Speed", &moveSpeed, 0.f, 1000.f);
	ImGui::SliderFloat("Jump Power", &jumpPower, 0.f, 1000.f);
	ImGui::End();

	if (player.velocity.y > 0.f)
	{
		player.normalizedDirection.y = 1;
	}
	else if (player.velocity.y < 0.f)
	{
		player.normalizedDirection.y = -1;
	}
	else
	{
		player.normalizedDirection.y = 0;
	}

	if (!player.isGrounded)
	{
		player.velocity.y += gravity * deltaTime;
	}

	switch (e.type)
	{
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::W && player.isGrounded)
			{
				player.velocity.y -= jumpPower;
				player.normalizedDirection.y = -1;
				player.isGrounded = false;
			}
			break;
	}

	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.velocity.x -= moveSpeed;
		player.normalizedDirection.x = -1;
	}

	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.velocity.x += moveSpeed;
		player.normalizedDirection.x = 1;
	}

	if (player.velocity.x > 0.f)
	{
		player.velocity.x -= friction;

		if (player.velocity.x < 0.f)
		{
			player.velocity.x = 0.f;
		}
	}
	else if (player.velocity.x < 0.f)
	{
		player.velocity.x += friction;

		if (player.velocity.x > 0.f)
		{
			player.velocity.x = 0.f;
		}
	}
	
	player.velocity.x = std::clamp(player.velocity.x, -terminalVelocity.x, terminalVelocity.x);
	player.velocity.y = std::clamp(player.velocity.y, -terminalVelocity.y, terminalVelocity.y);

	player.body.move(player.velocity * deltaTime);
	player.handleCollisions(EntityType::tile);
}

void Player::draw()
{
	sf::VertexArray vertexArray;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	const sf::FloatRect& bodyBounds{ player.body.getGlobalBounds() };

	player.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
	player.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
	player.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
	player.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);

	vertexArray[0].position = player.mesh[0];
	vertexArray[1].position = player.mesh[1];
	vertexArray[2].position = player.mesh[2];
	vertexArray[3].position = player.mesh[3];

	switch (player.normalizedDirection.x)
	{
		case 1:
			vertexArray[0].texCoords = sf::Vector2f(0.f, 0.f);
			vertexArray[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
			vertexArray[2].texCoords = sf::Vector2f(bodySize);
			vertexArray[3].texCoords = sf::Vector2f(0.f, bodySize.y);
			break;
		case -1:
			vertexArray[0].texCoords = sf::Vector2f(bodySize.x, 0.f);
			vertexArray[1].texCoords = sf::Vector2f(0.f, 0.f);
			vertexArray[2].texCoords = sf::Vector2f(0.f, bodySize.y);
			vertexArray[3].texCoords = sf::Vector2f(bodySize);
			break;
	}

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::player]);
}

void Player::handleCollisions(const EntityType entityType)
{
	const auto& [playerX, playerY] {body.getPosition()};

	switch (entityType)
	{
		case EntityType::tile:
			for (auto& tile : Tile::tiles)
			{	
				const auto& [tileX, tileY] {tile.body.getPosition()};

				if (tile.body.getGlobalBounds().intersects(body.getGlobalBounds()))
				{
					if (normalizedDirection.y == 1) //falling
					{
						body.setPosition(playerX, tileY - (0.5f * Tile::bodySize.y + 0.5f * bodySize.y));
						isGrounded = true;
						velocity.y = 0.f;
					}
					else if (normalizedDirection.y == -1) //jumping
					{
						body.setPosition(playerX, tileY + (0.5f * Tile::bodySize.y + 0.5f * bodySize.y) + 1.f);
					}

					if (normalizedDirection.x == 1) //moving right
					{
						body.setPosition(tileX - (0.5f * Tile::bodySize.x + 0.5f * bodySize.x), playerY);
					}
					else if (normalizedDirection.x == -1) //moving left
					{
						body.setPosition(tileX + (0.5f * Tile::bodySize.x + 0.5f * bodySize.x), playerY);
					}

					break;
				}
			}
			break;
	}
}