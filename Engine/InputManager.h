#pragma once
#include "Mouse.h"
#include "Keyboard.h"
#include "Container.h"

class InputManager
{
public:
	//Constructors
	InputManager(Mouse& mouse, Keyboard& keyboard, Container& basePanel);

	//Functions
	void update();

private:
	//Variables
	Mouse& mouse;
	Keyboard& keyboard;
	Container& basePanel;
	ActionPanel* focusedPanel = nullptr;
};