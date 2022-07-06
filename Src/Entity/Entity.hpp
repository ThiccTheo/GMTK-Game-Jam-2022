#pragma once
#include <iostream>

#include "CommonSFML.hpp"

class Entity
{
public:
	sf::RectangleShape body;
	sf::Vector2f mesh[4];
};

