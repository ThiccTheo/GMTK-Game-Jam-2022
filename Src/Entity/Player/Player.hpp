#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Player : public Entity
{
public:
	static Player player;

	Player();
	static void update(const float deltaTime, const sf::Event& e);
	static void draw();
};

