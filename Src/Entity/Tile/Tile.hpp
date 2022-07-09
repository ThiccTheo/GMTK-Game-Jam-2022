#pragma once
#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Tile : public Entity
{
public:
	static std::vector<Tile> tiles;

	Tile(const sf::Vector2i& indices);
	static void update();
	static void draw();
};

