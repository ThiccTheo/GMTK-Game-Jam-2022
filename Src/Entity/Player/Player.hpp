#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Player : public Entity
{
public:
	static Player player;
	static const sf::Vector2f bodySize;

	Player();
	Player(const sf::Vector2i& indices);
	Player(const Player&) = delete;
	static void update(const float deltaTime, const sf::Event& e);
	static void draw();

private:
	static const sf::Vector2f terminalVelocity;
	static const float gravity;
	static const float friction;

	sf::Vector2i normalizedDirection;

	bool isGrounded;
	int jumpPower;

	sf::Vector2f velocity;

	void jump();
};

