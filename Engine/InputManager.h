#pragma once
#include "Mouse.h"
#include "Keyboard.h"
#include "MasterUIPanel.h"
#include "ShortcutManager.h"

class InputManager
{
public:
	//Constructors
	InputManager(Mouse& mouse, Keyboard& keyboard, MasterUIPanel& basePanel);

	//Inherited via Panel
	void update();
	void addDebugText(DebugInfo info);

	//Functions
	void setFocus(ActionPanel* panel);
	void setShortcutManager(Board* board, ControlsExpander* controls, PlayPanel* playPanel);
	
private:
	//Variables
	Mouse& mouse;
	Keyboard& keyboard;
	MasterUIPanel& basePanel;
	ShortcutManager shortcuts;
	ActionPanel* focusedPanel = nullptr;
	std::vector<DebugInfo> debugInfo;

private:
	//Variables
	bool leftHeld = false;
	bool rightHeld = false;

	//Functions
	void handleFocus(const Mouse::Event e);

	void handleMouseWheel(const Mouse::Event e);
};
