#include "Player.hpp"
#include "../../Scene/Scene.hpp"

Player Player::player;

Player::Player()
{
	body.setSize(sf::Vector2f(16.f, 16.f));
}

void Player::update(const float deltaTime, const sf::Event& e)
{
}

void Player::draw()
{
	sf::RenderStates renderStates;

	sf::VertexArray vertexArray;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	const sf::FloatRect& bodyBounds{ player.body.getGlobalBounds() };

	player.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
	player.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
	player.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
	player.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);

	for (int i{ 0 }; i < 4; i++)
	{
		vertexArray[i].position = player.mesh[i];
	}

	Scene::window.draw(vertexArray, renderStates);
}
