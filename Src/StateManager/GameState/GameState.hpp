#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../StateManager.hpp"

class GameState : public StateManager
{
public:
	void init() override;
	void run() override;
private:
	void centerCamera();
};	
