#pragma once
#include <iostream>

#include "CommonSFML.hpp"

enum class OriginSpot { topLeft, topCenter, topRight, middleLeft, middleCenter, middleRight, bottomLeft, bottomCenter, bottomRight, count };

class Entity
{
public:
	sf::RectangleShape body;
	sf::Vector2f mesh[4];

	Entity();
	Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize, const OriginSpot originSpot);
};

