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
	void takeFocus(ActionPanel* panel);
	void removeFocus(ActionPanel* panel);
	void setShortcutManager(Board* board, ControlsExpander* controls, PlayPanel* playPanel);
	
private:
	//Variables
	Mouse& mouse;
	Keyboard& keyboard;
	MasterUIPanel& basePanel;
	ShortcutManager* shortcuts = nullptr;
	ActionPanel* focusedPanel = nullptr;
	std::vector<DebugInfo> debugInfo;

private:
	//Variables
	bool leftHeld = false;
	bool rightHeld = false;

	//Functions
	InputHandler::Event translateEvent(const Mouse::Event e);
	bool handleFocus(const InputHandler::Event e);

	void handleLeftClick(const InputHandler::Event e);
	void handleRightClick(const InputHandler::Event e);
	void handleMouseWheel(const InputHandler::Event e, const Mouse::Event wheelE);
};
