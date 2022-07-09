#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Player : public Entity
{
public:
	static Player player;

	Player();
	Player(const sf::Vector2i& indices);
	Player(const Player&) = delete;
	static void update(const float deltaTime, const sf::Event& e);
	static void draw();

private:
	//values should be const during project release:
	static sf::Vector2f terminalVelocity;
	static float gravity;
	static float friction;
	static float moveSpeed;
	static float jumpPower;

	sf::Vector2i normalizedDirection;

	bool isGrounded;

	sf::Vector2f velocity;

	void resolveTileCollisions(const char axis);
};

