#include "ResourceManager.hpp"

std::unordered_map<TextureId, sf::Texture> ResourceManager::textureMap;
std::unordered_map<SoundBufferId, sf::SoundBuffer> ResourceManager::soundBufferMap;
std::unordered_map<FontId, sf::Font> ResourceManager::fontMap;

bool ResourceManager::load()
{
	return
		textureMap[TextureId::cursor].loadFromFile("Data/Textures/Cursor.png") &&
		textureMap[TextureId::player].loadFromFile("Data/Textures/Player.png") &&
		textureMap[TextureId::tile].loadFromFile("Data/Textures/Tile.png");
}
