#include <utility>

#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"

Player Player::player;
const sf::Vector2f Player::bodySize{ 16.f, 16.f };
const sf::Vector2f Player::terminalVelocity{ 200.f, 200.f };
const float Player::gravity{ 10.f };
const float Player::friction{ 2.f };

Player::Player() = default;

Player::Player(const sf::Vector2i& indices) : Entity(indices, bodySize, OriginSpot::bottomCenter)
{
	velocity = sf::Vector2f(0.f, 0.f);
	jumpPower = 10000;
	normalizedDirection = sf::Vector2i(1, 1);
}

void Player::update(const float deltaTime, const sf::Event& e)
{
	if (!player.isGrounded)
	{
		player.velocity.y += gravity;
	}

	switch (e.type)
	{
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::W && player.isGrounded)
			{
				player.jump();
			}
			break;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.velocity.x -= 10.f;
		player.normalizedDirection.x = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.velocity.x += 10.f;
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

	player.body.setScale(sf::Vector2f(player.normalizedDirection));

	if (player.body.getPosition().y > Scene::window.getSize().y)
	{
		player.body.setPosition(player.body.getPosition().x, Scene::window.getSize().y + 1.f);
		player.velocity.y = 0.f;
		player.isGrounded = true;
	}
	else
	{
		player.isGrounded = false;
	}
}

void Player::draw()
{
	sf::RenderStates renderStates;
	renderStates.texture = &ResourceManager::textureMap[TextureId::player];

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

	vertexArray[0].texCoords = sf::Vector2f(0.f, 0.f);
	vertexArray[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
	vertexArray[2].texCoords = sf::Vector2f(bodySize);
	vertexArray[3].texCoords = sf::Vector2f(0.f, bodySize.y);

	Scene::window.draw(vertexArray, renderStates);
}


void Player::jump()
{
	velocity.y -= jumpPower;
}
