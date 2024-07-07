#pragma once
#include "Mouse.h"
#include "Keyboard.h"
#include "MasterUIPanel.h"

class InputManager
{
public:
	//Constructors
	InputManager(Mouse& mouse, Keyboard& keyboard, MasterUIPanel& basePanel);

	//Functions
	void update();
	void addDebugText(DebugInfo info);
	
private:
	//Variables
	Mouse& mouse;
	Keyboard& keyboard;
	MasterUIPanel &basePanel;
	ActionPanel* focusedPanel = nullptr;
	std::vector<DebugInfo> debugInfo;

	void handleLeftClick(const Mouse::Event e, const Tuple mousePos);
	void handleRightClick(const Mouse::Event e, const Tuple mousePos);
	void handleMouseWheel(const Mouse::Event e, const Tuple mousePos);
};
