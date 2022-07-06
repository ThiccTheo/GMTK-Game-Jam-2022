#include "Scene.hpp"

sf::RenderWindow Scene::window;

void Scene::init()
{
	const sf::Vector2u& resolution{ determineResolution() };
	window.create(sf::VideoMode(resolution.x, resolution.y), "GMTK Game Jam 2022", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
}

const sf::Vector2u Scene::determineResolution()
{
	const sf::Vector2u desktopResolution{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };

	if (desktopResolution.x % 16 == 0 && desktopResolution.y % 9 == 0) //16:9
	{
		return sf::Vector2u(1280, 720);
	}
	else if (desktopResolution.x % 16 == 0 && desktopResolution.y % 10 == 0) //16:10
	{
		return sf::Vector2u(1280, 800);
	}
	else if (desktopResolution.x % 4 == 0 && desktopResolution.y % 3 == 0) //4:3
	{
		return sf::Vector2u(1280, 960);
	}
	else if (desktopResolution.x % 5 == 0 && desktopResolution.y % 4 == 0) //5:4
	{
		return sf::Vector2u(1280, 1024);
	}
	else
	{
		return sf::Vector2u();
	}
}
