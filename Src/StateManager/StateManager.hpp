#pragma once
#include <iostream>
#include <stack>
#include <memory>

#include "CommonSFML.hpp"

enum class StateId { gameState, menuState, count };

class StateManager
{
public:
	sf::View camera;

	static void addState(const StateId stateId);
	static const bool removeState();
	static const sf::Event eventHandler();
	virtual void init();
	virtual void run();
private:
	static std::stack<std::unique_ptr<StateManager>> states;

	static void checkState();
};

