#include "InputManager.h"

InputManager::InputManager(Mouse& mouse, Keyboard& keyboard, MasterUIPanel& basePanel)
	:
	mouse(mouse),
	keyboard(keyboard),
	basePanel(basePanel)
{}

void InputManager::update()
{
	//maybe need to move where shortcuts are checked/handled
	assert(shortcuts != nullptr);
	shortcuts->checkKey(keyboard.ReadChar());

	Mouse::Event e = mouse.Read();
	while (e.IsValid())
	{
		//debug panel gets handled regardless of focus
		if (e.GetType() == Mouse::Event::Type::WheelUp
			|| e.GetType() == Mouse::Event::Type::WheelDown)
			handleMouseWheel(e);
		else
		{
			handleFocus(e);
			if (focusedPanel != nullptr)
				focusedPanel->handleEvent(e, LRHeld(leftHeld, rightHeld), this);
			else
				basePanel.handleEvent(e, LRHeld(leftHeld, rightHeld), this);
		}

		e = mouse.Read();
	}
	leftHeld = mouse.LeftIsPressed();
	rightHeld = mouse.RightIsPressed();
}

void InputManager::addDebugText(DebugInfo info)
{
	debugInfo.push_back(info);
}

void InputManager::setFocus(ActionPanel* panel)
{
	focusedPanel = panel;
}

void InputManager::setShortcutManager(Board* board, ControlsExpander* controls, PlayPanel* playPanel)
{
	shortcuts = &ShortcutManager(board, controls, playPanel);
}

void InputManager::handleFocus(const Mouse::Event e)
{
	if (focusedPanel == nullptr)
		return;

	//First check to see if the event is valid for the panel's current action
	bool stillFocused = focusedPanel->checkFocus(e, LRHeld(leftHeld, rightHeld));

	if (!stillFocused)
	{
		focusedPanel->loseFocus();
		focusedPanel = nullptr;
	}
}

void InputManager::handleMouseWheel(Mouse::Event e)
{
	if (e.GetType() == Mouse::Event::Type::WheelUp)
	{
		if (basePanel.getVisualRect().contains(Tuple(e.GetPos())))
		{
			//if (focusedPanel == nullptr)
			//	basePanel.updateDebugPanel("Null", true);
			//else
			//	basePanel.updateDebugPanel(focusedPanel->getDebugInfo().first, true);
			debugInfo.clear();
			basePanel.handleEvent(e, LRHeld(leftHeld,rightHeld), this);

			assert(!debugInfo.empty());

			std::string text;
			int count = 0;

			for (auto e : debugInfo)
			{
				for (int x = 0; x < count; x++)
					text += "-";

				text += e.first;
				text += e.second + "\n";
				count++;
			}

			basePanel.updateDebugPanel(text, true);
		}
	}
	else if (e.GetType() == Mouse::Event::Type::WheelDown)
	{
		debugInfo.clear();
		basePanel.updateDebugPanel("", false);
	}
}
