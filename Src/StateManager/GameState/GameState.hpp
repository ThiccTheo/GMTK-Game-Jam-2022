#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../StateManager.hpp"

class GameState : public StateManager
{
	void init() override;
	void run() override;
};	
