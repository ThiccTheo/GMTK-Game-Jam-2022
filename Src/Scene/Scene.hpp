#pragma once
#include <iostream>

#include "CommonSFML.hpp"

class Scene
{
public:
	static sf::RenderWindow window;
	static bool isFocused;

	static void init();
private:
	static sf::Cursor cursor;

	static const sf::Vector2u determineResolution();
};

