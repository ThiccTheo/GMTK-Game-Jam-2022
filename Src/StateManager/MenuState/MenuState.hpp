#pragma once
#include <iostream>

#include "CommonSFML.hpp"
#include "../StateManager.hpp"

class MenuState : public StateManager
{
public:
	void init() override;
	void run() override;
};

