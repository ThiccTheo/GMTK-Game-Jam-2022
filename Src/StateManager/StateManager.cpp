#include "StateManager.hpp"
#include "../Scene/Scene.hpp"
#include "GameState/GameState.hpp"
#include "MenuState/MenuState.hpp"

std::stack<std::unique_ptr<StateManager>> StateManager::states;

void StateManager::checkState()
{
	if (!states.empty())
	{
		states.top()->init();
		states.top()->run();
	}
}

void StateManager::addState(const StateId stateId)
{
	switch (stateId)
	{
		case StateId::menuState:
			states.emplace(std::make_unique<MenuState>());
			checkState();
			break;
		case StateId::gameState:
			states.emplace(std::make_unique<GameState>());
			checkState();
			break;
	}
}

const bool StateManager::removeState()
{
	if (!states.empty())
	{
		states.pop();
		return true;
	}
	else
	{
		return false;
	}
}

const sf::Event StateManager::eventHandler()
{
	sf::Event e;
	while (Scene::window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			Scene::window.close();
			break;
		}

		return e;
	}

	return sf::Event();
}

void StateManager::init()
{
}

void StateManager::run()
{
}
