#pragma once
#include <iostream>
#include <stack>
#include <memory>

#include "CommonSFML.hpp"

class StateManager
{
public:
	static std::stack<std::unique_ptr<StateManager>> states;
	sf::View camera;

	static void checkState();
	static const sf::Event eventHandler();
	virtual void init();
	virtual void run();
};

