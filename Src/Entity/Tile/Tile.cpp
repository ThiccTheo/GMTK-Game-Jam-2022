#include "Tile.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../Scene/Scene.hpp"

std::vector<Tile> Tile::tiles;
const sf::Vector2f Tile::bodySize{ 16.f, 16.f };

Tile::Tile(const sf::Vector2i& indices): Entity(indices, bodySize, OriginSpot::middleCenter)
{
}

void Tile::update()
{
}

void Tile::draw()
{
	sf::VertexArray vertexArray;
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(tiles.size() * 4);

	int vertexPointer{ 0 };

	for (auto& tile : tiles)
	{
		const sf::FloatRect& bodyBounds{ tile.body.getGlobalBounds() };

		tile.mesh[0] = sf::Vector2f(bodyBounds.left, bodyBounds.top);
		tile.mesh[1] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top);
		tile.mesh[2] = sf::Vector2f(bodyBounds.left + bodyBounds.width, bodyBounds.top + bodyBounds.height);
		tile.mesh[3] = sf::Vector2f(bodyBounds.left, bodyBounds.top + bodyBounds.height);
		
		sf::Vertex* currentVertices{ &vertexArray[vertexPointer]};

		currentVertices[0].position = tile.mesh[0];
		currentVertices[1].position = tile.mesh[1];
		currentVertices[2].position = tile.mesh[2];
		currentVertices[3].position = tile.mesh[3];

		currentVertices[0].texCoords = sf::Vector2f(0.f, 0.f);
		currentVertices[1].texCoords = sf::Vector2f(bodySize.x, 0.f);
		currentVertices[2].texCoords = sf::Vector2f(bodySize);
		currentVertices[3].texCoords = sf::Vector2f(0.f, bodySize.y);

		vertexPointer += 4;
	}

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::tile]);
}
