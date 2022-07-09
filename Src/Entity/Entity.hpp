#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>

#include "CommonSFML.hpp"

enum class OriginSpot { topLeft, topCenter, topRight, middleLeft, middleCenter, middleRight, bottomLeft, bottomCenter, bottomRight, count };
enum class EntityType { player, tile, count };

class Entity
{
public:
	sf::RectangleShape body;
	sf::Vector2f mesh[4];
	static std::unordered_map<EntityType, sf::Vector2f> bodySizeMap;

	Entity();
	Entity(const sf::Vector2i& indices, const sf::Vector2f& bodySize, const OriginSpot originSpot);
	static void init();
	const Entity* collisionHandler(const EntityType entityType);
};

