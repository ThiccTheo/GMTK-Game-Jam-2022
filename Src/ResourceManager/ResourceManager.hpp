#pragma once
#include <iostream>
#include <unordered_map>

#include "CommonSFML.hpp"

enum class TextureId { player, tile, count };
enum class SoundBufferId {};
enum class FontId {};

class ResourceManager
{
public:
	static std::unordered_map<TextureId, sf::Texture> textureMap;
	static std::unordered_map<SoundBufferId, sf::SoundBuffer> soundBufferMap;
	static std::unordered_map<FontId, sf::Font> fontMap;

	static bool load();
};

